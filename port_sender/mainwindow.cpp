#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include "utils.h"

//общий размер посылки
#define DATA_SEND_SIZE 100
//константа - данные пакета
#define DATA_SEND 0x1
//размер преамбулы (маркер)
#define DATA_SEND_MARKER_SIZE 2
//размер тела пакета
#define DATA_SEND_BODY_SIZE (DATA_SEND_SIZE-DATA_SEND_MARKER_SIZE)
#define DATA_SEND_MARKER_1 0x18
#define DATA_SEND_MARKER_2 0x28
#define DATA_SEND_MARKER_1_INDX 0
#define DATA_SEND_MARKER_2_INDX 1
#define DATA_SEND_BODY_INDX (DATA_SEND_MARKER_2_INDX+1)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    connect(&m_timer_send,SIGNAL(timeout()),this,SLOT(on_timer_send()));
    connect(&m_timer_refresh_gui,SIGNAL(timeout()),this,SLOT(on_timer_refresh_gui()));
    connect(&m_timer_processing,SIGNAL(timeout()),this,SLOT(on_timer_processing()));
    connect(&m_port, SIGNAL(readyRead()),this, SLOT(on_data_recived()));


    Qt::WindowFlags f;
    f=Qt::WindowStaysOnTopHint;
    this->setWindowFlags(f);
    ui->setupUi(this);
    SET_WINDOW_FIXED_SIZE;
    ADD_BUILD_TIME_TITLE;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            ui->m_cmbox_port->addItem(info.portName());

    ui->m_cmbox_port_speed->addItem("115200");

    ui->m_grp_rcv->setParent(ui->m_grp_process);
    ui->m_grp_send->setParent(ui->m_grp_process);
    ui->m_line_marker->setParent(ui->m_grp_process);

    emit ui->m_radio_role_sender->clicked(true);
    ui->m_radio_role_sender->setChecked(true);
    ui->m_grp_process->setEnabled(false);
    ui->m_line_marker->setVisible(false);

    for(int i=0;i<DATA_SEND_SIZE;i++)
    {
        m_qb_data_send.append((char)DATA_SEND);
    }

    m_qb_data_send[DATA_SEND_MARKER_1_INDX]=DATA_SEND_MARKER_1;
    m_qb_data_send[DATA_SEND_MARKER_2_INDX]=DATA_SEND_MARKER_2;

    m_send_cntr=
    m_send_cntr_save=
    m_rcv_cntr=
    m_rcv_cntr_save=
    m_err_cntr=
    m_err_cntr_save=
    m_shift=0;

    m_dbg_f1=0;
    m_timer_refresh_gui.start(1000);
    m_timer_processing.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_btn_connect_clicked()
{
    static bool opened=false;
    QString port_name=ui->m_cmbox_port->currentText();
    bool res;
    //Для   QextSerialPort
    m_port.close();
    m_port.setPortName(port_name);
    m_port.close();
    #ifdef Q_OS_WIN
    m_port.setBaudRate(BAUD115200);
    #elif   defined(Q_OS_LINUX)
       // m_port.setBaudRate(BAUD460800);
    m_port.setBaudRate(BAUD115200);
    #else
        #error "OS not supported"
    #endif
    m_port.setFlowControl(FLOW_OFF);
    m_port.setParity(PAR_NONE);
    m_port.setDataBits(DATA_8);
    m_port.setStopBits(STOP_1);
    res=m_port.open(QIODevice::ReadWrite);
    m_port.setRts(false);

    quint32 speed=ui->m_cmbox_port_speed->currentText().toUInt();
    m_port.setBaudRate((BaudRateType)speed);
    opened=!opened;

    ui->m_grp_port->setEnabled(!opened);
    ui->m_grp_process->setEnabled(opened);
    if(opened)
    {
        ui->m_btn_connect->setText("Закрыть порт");
    }
    else
    {
        ui->m_btn_connect->setText("Открыть порт");
    }
}
//---------------------------------------------
void MainWindow::on_timer_send()
{
    if(m_port.isOpen())
    {
        m_port.write(m_qb_data_send);
        m_port.flush();
        m_send_cntr++;
    }
}
//---------------------------------------------
void MainWindow::on_timer_refresh_gui()
{
    quint32 send=m_send_cntr-m_send_cntr_save;
    quint32 rcv=m_rcv_cntr-m_rcv_cntr_save;
    quint32 err=m_err_cntr-m_err_cntr_save;
    quint32 shift=m_shift;
    ui->m_lbl_send->setText(NUM2STR(send));
    ui->m_lbl_rcv->setText(NUM2STR(rcv));
    ui->m_lbl_err->setText(NUM2STR(err));
    ui->m_lbl_shift->setText(NUM2STR(shift));
}
//---------------------------------------------
bool MainWindow::pattern_match(quint8 pattern, quint8 byte, quint8* shift, bool *shift_right)
{
    bool match=false;
    *shift=0;
    //данные могут быть сдвинуты - переберем все варианты
    for(int i=0;i<8;i++)
    {
        quint8 gen_byte=byte;
        match=((gen_byte>>(*shift))==pattern);
        if(match)
        {
          *shift_right=true;
           break;
        }
        else
            (*shift)++;
    }
    //сдвигом вправо не нашли - подвигаем влево
    if(!match)
    {
        (*shift)=0;
        for(int i=0;i<8;i++)
        {
            quint8 gen_byte=byte;
            match=((gen_byte<<(*shift))==pattern);
            if(match)
            {
              *shift_right=false;
               break;
            }
            else
                (*shift)++;
        }
    }

    return match;
}
//---------------------------------------------
void MainWindow::on_timer_processing()
{
    quint8 bit_shift=0;
    bool shift_right;
    //набираем данных для поиска маркеров
    if(m_qb_data_raw_recived.size()>=DATA_SEND_MARKER_SIZE)
    {
        bool marker_1_match=false;
        bool marker_2_match=false;
        //поищем маркеры и если найдем будем знать битовый сдвиг данных
        marker_1_match=pattern_match(DATA_SEND_MARKER_1,
                                     (m_qb_data_raw_recived[DATA_SEND_MARKER_1_INDX]&0xff),
                                     &bit_shift,&shift_right);

        if(marker_1_match)
        {
            quint8 marker2=(shift_right)?(m_qb_data_raw_recived[DATA_SEND_MARKER_2_INDX]&0xff)>>bit_shift:
                                         (m_qb_data_raw_recived[DATA_SEND_MARKER_2_INDX]&0xff)<<bit_shift;
            marker_2_match=marker2==DATA_SEND_MARKER_2;
        }
        m_shift=bit_shift;
        if(bit_shift)
        {
            BREAK_POINT;
        }
        //маркеры обнаружены
        if(marker_1_match&&marker_1_match)
        {
            //ждем пока тело пакета наберется
            quint32 rem=m_qb_data_raw_recived.size()-DATA_SEND_MARKER_SIZE;
            if(rem>=DATA_SEND_BODY_SIZE)
            {
                m_rcv_cntr++;
                //проверим тело пакета на ошибки
                for(int i=DATA_SEND_BODY_INDX;i<DATA_SEND_BODY_SIZE;i++)
                {
                    //скорректируем данные с учетом сдвига.
                    quint8 corrected_byte=(shift_right)?(m_qb_data_raw_recived[i]&0xff)>>bit_shift:
                                                        (m_qb_data_raw_recived[i]&0xff)<<bit_shift;

                    if(corrected_byte!=(m_qb_data_send[i]&0xff))
                    {
                        m_err_cntr++;
                    }
                }
                //удалим пакет из принятых
                m_qb_data_raw_recived.remove(DATA_SEND_MARKER_1_INDX,DATA_SEND_SIZE);
            }
        }
        //то что не маркер - удаляем
        else
        {
            qDebug()<<"Garbage deleted: "<<NUM2STR(m_qb_data_raw_recived[DATA_SEND_MARKER_1_INDX]);
            qDebug()<<"Garbage deleted: "<<NUM2STR(m_qb_data_raw_recived[DATA_SEND_MARKER_2_INDX]);
            m_qb_data_raw_recived.remove(DATA_SEND_MARKER_1_INDX,2);
        }

    }

}
//---------------------------------------------
void MainWindow::on_m_btn_start_send_clicked()
{
    static bool start=true;
    quint32 timeout=ui->m_edit_send_ms->text().toUInt();

    if(start)
    {
        ui->m_btn_start_send->setText("Остановить передачу");
        m_timer_send.start(timeout);
    }
    else
    {
        m_timer_send.stop();
        ui->m_btn_start_send->setText("Начать передачу с интервалом");
    }

    start=!start;
}
//---------------------------------------------
void MainWindow::on_data_recived()
{
    m_qb_data_raw_recived.append(m_port.readAll());
}
//---------------------------------------------
void MainWindow::on_m_btn_reset_stat_clicked()
{
    m_send_cntr_save=m_send_cntr;
    m_rcv_cntr_save=m_rcv_cntr;
    m_err_cntr=m_err_cntr_save;
    m_shift=0;
}
//---------------------------------------------
quint32 MainWindow::check_errors()
{
    for(int i=0;i<DATA_SEND_SIZE;i++)
    {
        m_qb_data_send.append((char)0);
    }
}
//---------------------------------------------
void MainWindow::on_m_btn_dbg_clicked()
{
    static int f=1;
    m_dbg_f1=1;

    quint8 pattern =0x1<<7;
    quint8 byte = pattern>>7;
    quint8 shift;
    bool right;
/*
    if(pattern_match(pattern,byte,&shift,&right))
    {
        BREAK_POINT;
    }
    else
    {
        BREAK_POINT;
    }
*/
    for(int i=0;i<DATA_SEND_SIZE;i++)
    {
        m_qb_data_send[i]=(m_qb_data_send[i]&0xff)<<1;
    }


}
//---------------------------------------------
void MainWindow::set_on_focus(enum FOCUS_ON focus)
{
    QRect tmp_rect;
    ui->m_grp_send->setGeometry(this->width()+this->x(),0,ui->m_grp_send->width(),ui->m_grp_send->height());
    ui->m_grp_rcv->setGeometry(this->width()+this->x(),0,ui->m_grp_rcv->width(),ui->m_grp_rcv->height());
    ui->m_grp_send->setVisible(false);
    ui->m_grp_rcv->setVisible(false);

    switch(focus)
    {
        case FOCUS_ON_NONE:
        {
            ui->m_grp_send->setGeometry(this->width()+this->x(),0,ui->m_grp_send->width(),ui->m_grp_send->height());
            ui->m_grp_rcv->setGeometry(this->width()+this->x(),0,ui->m_grp_rcv->width(),ui->m_grp_rcv->height());
            ui->m_grp_send->setVisible(false);
            ui->m_grp_rcv->setVisible(false);
        }break;
        case FOCUS_ON_RCV:
        {
            tmp_rect=ui->m_grp_process->geometry();
            tmp_rect.setX(ui->m_line_marker->x());
            tmp_rect.setY(ui->m_line_marker->y());
            ui->m_grp_rcv->setGeometry(tmp_rect);
            ui->m_grp_rcv->setVisible(true);

        }break;
        case FOCUS_ON_SEND:
        {
            tmp_rect=ui->m_grp_process->geometry();
            tmp_rect.setX(ui->m_line_marker->x());
            tmp_rect.setY(ui->m_line_marker->y());
            ui->m_grp_send->setGeometry(tmp_rect);
            ui->m_grp_send->setVisible(true);
        }break;
    }
}
//---------------------------------------------
void MainWindow::on_m_radio_role_sender_clicked(bool checked)
{
  set_on_focus(FOCUS_ON_SEND);
}
//---------------------------------------------
void MainWindow::on_m_radio_role_reciver_clicked(bool checked)
{
  set_on_focus(FOCUS_ON_RCV);
}
//---------------------------------------------
void MainWindow::on_m_btn_dbg_2_clicked()
{
    m_qb_data_send.clear();
    for(int i=0;i<DATA_SEND_SIZE;i++)
    {
        m_qb_data_send.append((char)DATA_SEND);
    }
    m_qb_data_send[DATA_SEND_MARKER_1_INDX]=DATA_SEND_MARKER_1;
    m_qb_data_send[DATA_SEND_MARKER_2_INDX]=DATA_SEND_MARKER_2;

}
