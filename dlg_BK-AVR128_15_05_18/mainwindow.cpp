#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "build_time.h"

#include <windows.h>
//---------------------------------------------------------------
#define KEY_WINDOW_MAIN_RECT "dlg/main_window_rect"
#define KEY_REG_0 "dlg/reg_0"
#define KEY_REG_1 "dlg/reg_1"
#define KEY_REG_2 "dlg/reg_2"
#define KEY_REG_3 "dlg/reg_3"
#define KEY_REG_4 "dlg/reg_4"
#define KEY_REG_5 "dlg/reg_5"
#define KEY_REG_6 "dlg/reg_6"
#define KEY_REG_7 "dlg/reg_7"
#define KEY_REG_8 "dlg/reg_8"
#define KEY_REG_9 "dlg/reg_9"
#define KEY_REG_10 "dlg/reg_10"
#define KEY_REG_11 "dlg/reg_11"
#define KEY_REG_12 "dlg/reg_12"

#define KEY_REG_0_2 "dlg/reg_0_2"
#define KEY_REG_1_2 "dlg/reg_1_2"
#define KEY_REG_2_2 "dlg/reg_2_2"
#define KEY_REG_6_2 "dlg/reg_6_2"

#define KEY_F1_WORK_TIME "dlg/reg_work_1_time"
#define KEY_F1_IDLE_TIME "dlg/reg_idle_1_time"
#define KEY_F2_WORK_TIME "dlg/reg_work_2_time"
#define KEY_F2_IDLE_TIME "dlg/reg_idle_2_time"

#define KEY_SYNC "dlg/reg_sync"

#define KEY_REG_x "dlg/main_x"
//---------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_cmbox_port_speed->addItem("115200");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            ui->m_cmbox_port->addItem(info.portName());


    this->setWindowTitle(this->windowTitle()+get_build_dt());
    SET_WINDOW_FIXED_SIZE;
    Qt::WindowFlags f;
    f=Qt::WindowStaysOnTopHint;
    this->setWindowFlags(f);
    connect(&m_timer_f_change,SIGNAL(timeout()),this,SLOT(on_m_timer_f_change()));
    connect(&m_timer_sync,SIGNAL(timeout()),this,SLOT(on_m_timer_sync()));

    restore_settings();

    m_reg_num[25]=0;
    m_reg_num[46]=1;m_reg_num[45]=2;m_reg_num[22]=3;
    m_reg_num[44]=4;m_reg_num[40]=5;m_reg_num[20]=6;
    m_reg_num[41]=7;m_reg_num[37]=8;m_reg_num[19]=9;
    m_reg_num[39]=10;m_reg_num[35]=11;m_reg_num[34]=12;

    m_connected=false;
    m_child_enum_complete=true;
    m_state_cntr=0;
    m_child_enum_cntr_regs_found=0;
    m_child_enum_cntr_all=0;

}
//---------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//---------------------------------------------------------------
void MainWindow::on_m_btn_connect_clicked()
{
    if(m_connected)
    {
        m_connected=false;
        ui->m_btn_connect->setText("Открыть порт");
        m_port.close();
    }
    else
    {
        bool res=false;

        m_port_name=ui->m_cmbox_port->currentText();
        m_port.close();
        m_port.setPortName(m_port_name);
        if(m_port.open(QIODevice::ReadWrite) &&
        m_port.setBaudRate(QSerialPort::Baud115200)&&
        m_port.setDataBits(QSerialPort::Data8)&&
        m_port.setParity(QSerialPort::NoParity)&&
        m_port.setStopBits(QSerialPort::OneStop)&&
        m_port.setRequestToSend(false)&&
        m_port.setFlowControl(QSerialPort::NoFlowControl))res=true;
        m_port.setRequestToSend(false);

        //if(res)!!!!!!!!!!!!!!!!!!!!!!!!
        {
            on_connected();

            ui->m_btn_connect->setText("Закрыть порт");
            m_timer_sync.start(500);
            m_connected=true;
        }
    }

    ui->m_grp_regs->setEnabled(m_connected);
    ui->m_grp_regs_2->setEnabled(m_connected);
    ui->m_grp_regs_1->setEnabled(m_connected);
    ui->m_grp_f_change->setEnabled(m_connected);

}
//----------------------------------------------------
void MainWindow::on_connected()
{

}
//----------------------------------------------------
void MainWindow::save_settings()
{
    m_settings.setValue(KEY_WINDOW_MAIN_RECT,this->geometry());
    //freq 1
    m_settings.setValue(KEY_REG_0,this->ui->m_edit_reg_0->text());
    m_settings.setValue(KEY_REG_1,this->ui->m_edit_reg_1->text());
    m_settings.setValue(KEY_REG_2,this->ui->m_edit_reg_2->text());
    m_settings.setValue(KEY_REG_3,this->ui->m_edit_reg_3->text());
    m_settings.setValue(KEY_REG_4,this->ui->m_edit_reg_4->text());
    m_settings.setValue(KEY_REG_5,this->ui->m_edit_reg_5->text());
    m_settings.setValue(KEY_REG_6,this->ui->m_edit_reg_6->text());
    m_settings.setValue(KEY_REG_7,this->ui->m_edit_reg_7->text());
    m_settings.setValue(KEY_REG_8,this->ui->m_edit_reg_8->text());
    m_settings.setValue(KEY_REG_9,this->ui->m_edit_reg_9->text());
    m_settings.setValue(KEY_REG_10,this->ui->m_edit_reg_10->text());
    m_settings.setValue(KEY_REG_11,this->ui->m_edit_reg_11->text());
    m_settings.setValue(KEY_REG_12,this->ui->m_edit_reg_12->text());
    //freq 2
    m_settings.setValue(KEY_REG_0_2,this->ui->m_edit_reg_0_2->text());
    m_settings.setValue(KEY_REG_1_2,this->ui->m_edit_reg_1_2->text());
    m_settings.setValue(KEY_REG_2_2,this->ui->m_edit_reg_2_2->text());

    //timings
    m_settings.setValue(KEY_F1_WORK_TIME,this->ui->m_edit_f1_work->text());
    m_settings.setValue(KEY_F1_IDLE_TIME,this->ui->m_edit_f1_idle->text());
    m_settings.setValue(KEY_F2_WORK_TIME,this->ui->m_edit_f2_work->text());
    m_settings.setValue(KEY_F2_IDLE_TIME,this->ui->m_edit_f2_idle->text());
    //sync
    m_settings.setValue(KEY_SYNC,m_sync_f);
    m_settings.sync();
}
//----------------------------------------------------
void MainWindow::restore_settings()
{
    QRect rect;
    bool tmp_bool;
    QString tmp_str;
    //---положение на экране------------------------
    rect=this->geometry();
    rect.setTop(20);
    rect.setLeft(20);
    rect=m_settings.value(KEY_WINDOW_MAIN_RECT,rect).toRect();
    this->setGeometry(rect);

    //freq 1
    this->ui->m_edit_reg_0->setText(m_settings.value(KEY_REG_0,"00205CF0").toString());
    this->ui->m_edit_reg_1->setText(m_settings.value(KEY_REG_1,"03555551").toString());
    this->ui->m_edit_reg_2->setText(m_settings.value(KEY_REG_2,"00040032").toString());
    this->ui->m_edit_reg_3->setText(m_settings.value(KEY_REG_3,"20000003").toString());
    this->ui->m_edit_reg_4->setText(m_settings.value(KEY_REG_4,"32020984").toString());
    this->ui->m_edit_reg_5->setText(m_settings.value(KEY_REG_5,"00800025").toString());
    this->ui->m_edit_reg_6->setText(m_settings.value(KEY_REG_6,"356020E6").toString());
    this->ui->m_edit_reg_7->setText(m_settings.value(KEY_REG_7,"12000007").toString());
    this->ui->m_edit_reg_8->setText(m_settings.value(KEY_REG_8,"102D0428").toString());
    this->ui->m_edit_reg_9->setText(m_settings.value(KEY_REG_9,"02013CC9").toString());
    this->ui->m_edit_reg_10->setText(m_settings.value(KEY_REG_10,"00C0019A").toString());
    this->ui->m_edit_reg_11->setText(m_settings.value(KEY_REG_11,"0061300B").toString());
    this->ui->m_edit_reg_12->setText(m_settings.value(KEY_REG_12,"0001041C").toString());

    //freq 2
    this->ui->m_edit_reg_0_2->setText(m_settings.value(KEY_REG_0_2,"00205CF0").toString());
    this->ui->m_edit_reg_1_2->setText(m_settings.value(KEY_REG_1_2,"03555551").toString());
    this->ui->m_edit_reg_2_2->setText(m_settings.value(KEY_REG_2_2,"00040032").toString());

    //timings
    this->ui->m_edit_f1_work->setText(m_settings.value(KEY_F1_WORK_TIME,"500").toString());
    this->ui->m_edit_f1_idle->setText(m_settings.value(KEY_F1_IDLE_TIME,"500").toString());
    this->ui->m_edit_f2_work->setText(m_settings.value(KEY_F2_WORK_TIME,"500").toString());
    this->ui->m_edit_f2_idle->setText(m_settings.value(KEY_F2_IDLE_TIME,"500").toString());
    //sync
    m_sync_f=(SYNC_F)m_settings.value(KEY_SYNC,0).toUInt();
    if(m_sync_f==SYNC_F_1)
    {
        emit ui->m_radio_sync_f1->clicked(true);
        ui->m_radio_sync_f1->setChecked(true);
    }
    if(m_sync_f==SYNC_F_2)
    {
        emit ui->m_radio_sync_f2->clicked(true);
        ui->m_radio_sync_f2->setChecked(true);
    }
    if(m_sync_f==SYNC_F_NO)
    {
        emit ui->m_radio_sync_no->clicked(true);
        ui->m_radio_sync_no->setChecked(true);
    }

}
//----------------------------------------------------
void MainWindow::closeEvent ( QCloseEvent * e )
{
    save_settings();
}
//----------------------------------------------------
void MainWindow::send_txt_reg(quint8 reg_num,QString str_reg)
{
    if(m_send_interface==SEND_INTERFACE_COM_PORT)
    {
        bool ok;
        quint32 reg;
        reg=str_reg.toUInt(&ok,16);
        QByteArray qb;

        qb.append((reg>>24)&0xFF);
        qb.append((reg>>16)&0xFF);
        qb.append((reg>>8)&0xFF);
        qb.append((reg)&0xFF);
        m_port.write(qb);
    }
    else if(m_send_interface==SEND_INTERFACE_DMR_DLG)
    {
        if(this->m_hwnd_dlg_dmr)
        {
            //WPARAM reg_num=reg_num;
            SendMessage(this->m_hwnd_dlg_dmr_synt_list_box_regs,CB_SETCURSEL,reg_num,0);
            wchar_t w_str[200];
            memset(w_str,0,dim(w_str));
            w_str[0]='0';w_str[1]='x';
            str_reg.toWCharArray(&w_str[2]);
            SendMessage(this->m_hwnd_dlg_dmr_synt_edit,WM_SETTEXT,100,(LPARAM)w_str);
            SendMessage(this->m_hwnd_dlg_dmr_synt_btn,BM_CLICK,0,0);
        }
    }

}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_0_clicked()
{
    send_txt_reg(0,ui->m_edit_reg_0->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_1_clicked()
{
    send_txt_reg(1,ui->m_edit_reg_1->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_2_clicked()
{
    send_txt_reg(2,ui->m_edit_reg_2->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_3_clicked()
{
    send_txt_reg(3,ui->m_edit_reg_3->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_4_clicked()
{
    send_txt_reg(4,ui->m_edit_reg_4->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_5_clicked()
{
    send_txt_reg(5,ui->m_edit_reg_5->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_6_clicked()
{
    send_txt_reg(6,ui->m_edit_reg_6->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_7_clicked()
{
    send_txt_reg(7,ui->m_edit_reg_7->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_8_clicked()
{
    send_txt_reg(8,ui->m_edit_reg_8->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_9_clicked()
{
    send_txt_reg(9,ui->m_edit_reg_9->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_10_clicked()
{
    send_txt_reg(10,ui->m_edit_reg_10->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_11_clicked()
{
    send_txt_reg(11,ui->m_edit_reg_11->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_12_clicked()
{
    send_txt_reg(12,ui->m_edit_reg_12->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_12_0_clicked()
{
    bool sync_f1=ui->m_radio_sync_f1->isChecked();

    emit ui->m_btn_send_reg_12->click();
    emit ui->m_btn_send_reg_11->click();
    emit ui->m_btn_send_reg_10->click();
    emit ui->m_btn_send_reg_9->click();
    emit ui->m_btn_send_reg_8->click();
    emit ui->m_btn_send_reg_7->click();
    emit ui->m_btn_send_reg_6->click();
    emit ui->m_btn_send_reg_5->click();
    emit ui->m_btn_send_reg_4->click();
    emit ui->m_btn_send_reg_3->click();

    if(sync_f1)
    {
        emit ui->m_btn_send_reg_2->click();
        emit ui->m_btn_send_reg_1->click();
        emit ui->m_btn_send_reg_0->click();
    }
    else
    {
        emit ui->m_btn_send_reg_2_2->click();
        emit ui->m_btn_send_reg_1_2->click();
        emit ui->m_btn_send_reg_0_2->click();
    }
    qDebug()<<CURR_TIME_STR<<"INIT send";
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_0_6_clicked()
{
    emit ui->m_btn_send_reg_2->click();
    emit ui->m_btn_send_reg_1->click();
    emit ui->m_btn_send_reg_0->click();
    qDebug()<<CURR_TIME_STR<<"F1 send";
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_0_6_2_clicked()
{
    emit ui->m_btn_send_reg_2_2 ->click();
    emit ui->m_btn_send_reg_1_2->click();
    emit ui->m_btn_send_reg_0_2->click();
    qDebug()<<CURR_TIME_STR<<"F2 send";
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_0_2_clicked()
{
    send_txt_reg(0,ui->m_edit_reg_0_2->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_1_2_clicked()
{
    send_txt_reg(1,ui->m_edit_reg_1_2->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_send_reg_2_2_clicked()
{
    send_txt_reg(2,ui->m_edit_reg_2_2->text());
}
//----------------------------------------------------
void MainWindow::on_m_btn_copy_f1_to_f2_clicked()
{
    ui->m_edit_reg_0_2->setText(ui->m_edit_reg_0->text());
    ui->m_edit_reg_1_2->setText(ui->m_edit_reg_1->text());
    ui->m_edit_reg_2_2->setText(ui->m_edit_reg_2->text());

}
//----------------------------------------------------
void MainWindow::on_m_btn_start_f_change_clicked()
{

    //если работаем - остановимся
    if(m_state_cntr)
    {
        m_state_cntr=0;
        m_timer_f_change.stop();
        ui->m_btn_start_f_change->setText("START");
    }//если не работали - запустимся
    else
    {
        ui->m_btn_start_f_change->setText("STOP");
        m_f1_work_time_ms=ui->m_edit_f1_work->text().toUInt();
        m_f1_idle_time_ms=ui->m_edit_f1_idle->text().toUInt();
        m_f2_work_time_ms=ui->m_edit_f2_work->text().toUInt();
        m_f2_idle_time_ms=ui->m_edit_f2_idle->text().toUInt();

        //запустим работу на первой частоте
        m_timer_f_change.start(1);
        m_state_cntr=1;
    }
}
//----------------------------------------------------
void MainWindow::on_m_timer_f_change()
{
    //если значения обновлись в процессе работы - актуализируем
    m_f1_work_time_ms=ui->m_edit_f1_work->text().toUInt();
    m_f1_idle_time_ms=ui->m_edit_f1_idle->text().toUInt();
    m_f2_work_time_ms=ui->m_edit_f2_work->text().toUInt();
    m_f2_idle_time_ms=ui->m_edit_f2_idle->text().toUInt();

    switch(m_state_cntr)
    {
        /*запустим работу на первой частоте */
        case 1:
            ui->m_btn_send_reg_0_6->clicked();
            m_timer_f_change.start(m_f1_work_time_ms);
            m_state_cntr=2;
            qDebug()<<"F1 WORK START..."<<CURR_TIME_STR_MS;
        break;
        /*отработали на первой частоте-отдохнем */
        case 2:
            m_timer_f_change.start(m_f1_idle_time_ms);
            m_state_cntr=3;
            qDebug()<<"F1 IDLE START..."<<CURR_TIME_STR_MS;
        break;
        /*отдохнули от первой частоты - поработаем на 2й */
        case 3:
            ui->m_btn_send_reg_0_6_2->clicked();
            m_timer_f_change.start(m_f2_work_time_ms);
            m_state_cntr=4;
            qDebug()<<"F2 WORK START..."<<CURR_TIME_STR_MS;
        break;
        /*отработали на второй частоте-отдохнем,
          а потом снова на первую*/
        case 4:
            m_timer_f_change.start(m_f2_idle_time_ms);
            qDebug()<<"F2 IDLE START..."<<CURR_TIME_STR_MS;
            m_state_cntr=1;
        break;

    }
}
//----------------------------------------------------
WINBOOL CALLBACK on_child_window(HWND hwnd_child,LPARAM p)
{
    MainWindow* p_main_window=0;
    quint32 reg_indx=0;
    quint32 cntr;
    p_main_window=(MainWindow*)p;

    p_main_window->m_child_enum_cntr_all++;
    cntr=p_main_window->m_child_enum_cntr_all;
    //qDebug()<<"cntr:"<<cntr;
    if(p_main_window->m_reg_num.contains(cntr))
    {
        //qDebug()<<"Key: "<<cntr;
        p_main_window->m_child_enum_cntr_regs_found++;
        reg_indx=p_main_window->m_reg_num[cntr];
        wchar_t reg_v[100];
        memset(reg_v,0,dim(reg_v));
        SendMessage(hwnd_child,WM_GETTEXT,100,(LPARAM)reg_v);
        QString str=QString::fromWCharArray(reg_v);
        //qDebug()<<"Want: "<<p_main_window->m_child_enum_cntr_regs_found;
        //qDebug()<<"Need: "<<p_main_window->m_reg_num.count();
        //qDebug()<<"reg "<<reg_indx<<":"<<str;
        p_main_window->m_str_regs[reg_indx]=str;

        if(p_main_window->m_child_enum_cntr_regs_found==p_main_window->m_reg_num.count())
        {
            p_main_window->m_child_enum_complete=true;
            p_main_window->m_child_enum_cntr_regs_found=0;
            p_main_window->m_child_enum_cntr_all=0;
            QByteArray new_hash_f1,new_hash_f2;
            bool auto_send;
            auto_send=p_main_window->ui->m_chkbox_auto_send->isChecked();
            if(p_main_window->m_sync_f==MainWindow::SYNC_F_1)
            {
                p_main_window->sync2f1();
                new_hash_f1= p_main_window->calc_hash_f1();

                if(new_hash_f1!=p_main_window->m_hash_f1_save)
                {
                    if(auto_send)
                    {
                        p_main_window->m_hash_f1_save=new_hash_f1;
                        emit p_main_window->ui->m_btn_send_reg_0_6->clicked();
                    }
                }
            }
            if(p_main_window->m_sync_f==MainWindow::SYNC_F_2)
            {
                p_main_window->sync2f2();
                new_hash_f2=p_main_window->calc_hash_f2();
                if(new_hash_f2!=p_main_window->m_hash_f2_save)
                {
                    if(auto_send)
                    {
                        p_main_window->m_hash_f2_save=new_hash_f2;
                        emit p_main_window->ui->m_btn_send_reg_0_6_2->clicked();
                    }
                }
            }

        }

    }


}
//----------------------------------------------------
WINBOOL CALLBACK on_child_window_dlg_dmr_tab_ctrls(HWND hwnd_child,LPARAM p);
//----------------------------------------------------
//будет вызвано для каждого дочернего окна-вклдаки
WINBOOL CALLBACK on_child_window_dlg_dmr_tab(HWND hwnd_tab,LPARAM p)
{
    EnumChildWindows(hwnd_tab,on_child_window_dlg_dmr_tab_ctrls,p);
    return TRUE;
}
//----------------------------------------------------
//перебор элементов на вкладке
WINBOOL CALLBACK on_child_window_dlg_dmr_tab_ctrls(HWND hwnd_child,LPARAM p)
{
    MainWindow* p_main_window=(MainWindow*)p;
    const quint32 str_size=256;
    static quint32 ctrl_cntr=0;
    static bool synt_grp_found=false;
    QString str_tmp;

    if((quint32)hwnd_child==0x2121E)
    {
        BREAK_POINT;
    }
    char str_caption[str_size];
    memset(str_caption,0,dim(str_caption));
    GetWindowTextA(hwnd_child,str_caption,str_size);
    str_tmp=QString::fromLocal8Bit(str_caption);
    /*
    после того как нашли гроупбокс "синтезатор" начинаем
    считать элементы управления.*/
    if(str_tmp==" Синтезатор ")
    {
        synt_grp_found=true;
        ctrl_cntr=0;
    }

    if(synt_grp_found)
    {
        ctrl_cntr++;
        //номер по порядку
        if(ctrl_cntr==16)
            p_main_window->m_hwnd_dlg_dmr_synt_btn=hwnd_child;
        if(ctrl_cntr==17)
            p_main_window->m_hwnd_dlg_dmr_synt_list_box_regs=hwnd_child;
        if(ctrl_cntr==18){
            p_main_window->m_hwnd_dlg_dmr_synt_edit=hwnd_child;
            synt_grp_found=false;
            int iCtrlId = GetDlgCtrlID(p_main_window->m_hwnd_dlg_dmr_synt_list_box_regs);
            //qDebug()<<"ID: "<<iCtrlId;
            SendMessage(p_main_window->m_hwnd_dlg_dmr_synt_btn,WM_SETTEXT,100,(LPARAM)L"Установить значение(BK_AVR128 mode)");


        }


    }

    return TRUE;
}
//----------------------------------------------------
void MainWindow::on_m_timer_sync()
{
    HWND hwnd_main=NULL;
    HWND hwnd_grp_Registers=NULL;
    HWND hwnd_dlg_dmr_tab=NULL;
    HWND hwnd_tmp=NULL;

    //m_hwnd_dlg_dmr=NULL;
    //-----------------------Analog devices Window----------------------
    if(m_child_enum_complete)
    {
        hwnd_main=FindWindowEx(0,0,0,L"Analog Devices ADF4355, ADF4355-2, ADF4355-3, ADF5355, and ADF4356 Evaluation Board Control Software");
        if(hwnd_main)
        {
            hwnd_grp_Registers=FindWindowEx(hwnd_main,0,0,L"Registers");

            if(hwnd_grp_Registers)
            {
                m_child_enum_complete=false;
                m_child_enum_cntr_regs_found=0;
                m_child_enum_cntr_all=0;
                EnumChildWindows(hwnd_grp_Registers,on_child_window,(LPARAM)this);
            }
        }
        //----------------------------DMR Control window--------------------------
        m_hwnd_dlg_dmr=FindWindowEx(0,0,0,L" ТПО DMR");
        if(m_hwnd_dlg_dmr)
        {
            hwnd_dlg_dmr_tab=FindWindowEx(m_hwnd_dlg_dmr,0,0,L"");

            if(hwnd_dlg_dmr_tab)
            {
                EnumChildWindows(hwnd_dlg_dmr_tab,on_child_window_dlg_dmr_tab,(LPARAM)this);
                /*hwnd_dlg_dmr_grp_synt=FindWindowEx(hwnd_dlg_dmr_tab,0,0,L" Синтезатор ");
                if(hwnd_dlg_dmr_grp_synt)
                {


                }*/
            }

        }


    }
}
//----------------------------------------------------
void MainWindow::on_m_radio_sync_f1_clicked(bool checked)
{
    m_sync_f=SYNC_F_1;
    m_child_enum_complete=true;
    ui->m_btn_send_reg_12_0->setText("INIT VCO\n (Freq 1)");
}
//----------------------------------------------------
void MainWindow::on_m_radio_sync_f2_clicked(bool checked)
{
    m_sync_f=SYNC_F_2;
    m_child_enum_complete=true;
    ui->m_btn_send_reg_12_0->setText("INIT VCO\n (Freq 2)");
}
//----------------------------------------------------
void MainWindow::on_m_radio_sync_no_clicked(bool checked)
{
    m_sync_f=SYNC_F_NO;
    m_child_enum_complete=true;
    ui->m_btn_send_reg_12_0->setText("INIT VCO\n (Freq 2)");
}
//----------------------------------------------------
void MainWindow::sync2f1()
{
    ui->m_edit_reg_0->setText(m_str_regs[0]);
    ui->m_edit_reg_1->setText(m_str_regs[1]);
    ui->m_edit_reg_2->setText(m_str_regs[2]);
    ui->m_edit_reg_3->setText(m_str_regs[3]);
    ui->m_edit_reg_4->setText(m_str_regs[4]);
    ui->m_edit_reg_5->setText(m_str_regs[5]);
    ui->m_edit_reg_6->setText(m_str_regs[6]);
    ui->m_edit_reg_7->setText(m_str_regs[7]);
    ui->m_edit_reg_8->setText(m_str_regs[8]);
    ui->m_edit_reg_9->setText(m_str_regs[9]);
    ui->m_edit_reg_10->setText(m_str_regs[10]);
    ui->m_edit_reg_11->setText(m_str_regs[11]);
    ui->m_edit_reg_12->setText(m_str_regs[12]);

}
//----------------------------------------------------
void MainWindow::sync2f2()
{
    ui->m_edit_reg_0_2->setText(m_str_regs[0]);
    ui->m_edit_reg_1_2->setText(m_str_regs[1]);
    ui->m_edit_reg_2_2->setText(m_str_regs[2]);

    ui->m_edit_reg_3->setText(m_str_regs[3]);
    ui->m_edit_reg_4->setText(m_str_regs[4]);
    ui->m_edit_reg_5->setText(m_str_regs[5]);
    ui->m_edit_reg_6->setText(m_str_regs[6]);
    ui->m_edit_reg_7->setText(m_str_regs[7]);
    ui->m_edit_reg_8->setText(m_str_regs[8]);
    ui->m_edit_reg_9->setText(m_str_regs[9]);
    ui->m_edit_reg_10->setText(m_str_regs[10]);
    ui->m_edit_reg_11->setText(m_str_regs[11]);
    ui->m_edit_reg_12->setText(m_str_regs[12]);


}
//----------------------------------------------------
QByteArray MainWindow::calc_hash_f1()
{
    QByteArray hash;
    QString str_sum_regs;

    str_sum_regs+=ui->m_edit_reg_0->text();
    str_sum_regs+=ui->m_edit_reg_1->text();
    str_sum_regs+=ui->m_edit_reg_2->text();
    str_sum_regs+=ui->m_edit_reg_3->text();
    str_sum_regs+=ui->m_edit_reg_4->text();
    str_sum_regs+=ui->m_edit_reg_5->text();
    str_sum_regs+=ui->m_edit_reg_6->text();
    str_sum_regs+=ui->m_edit_reg_7->text();
    str_sum_regs+=ui->m_edit_reg_8->text();
    str_sum_regs+=ui->m_edit_reg_9->text();
    str_sum_regs+=ui->m_edit_reg_10->text();
    str_sum_regs+=ui->m_edit_reg_11->text();
    str_sum_regs+=ui->m_edit_reg_12->text();

    hash=QCryptographicHash::hash(str_sum_regs.toLocal8Bit(),QCryptographicHash::Md5);

    return hash;
}
//----------------------------------------------------
QByteArray MainWindow::calc_hash_f2()
{
    QByteArray hash;
    QString str_sum_regs;

    str_sum_regs+=ui->m_edit_reg_0_2->text();
    str_sum_regs+=ui->m_edit_reg_1_2->text();
    str_sum_regs+=ui->m_edit_reg_2_2->text();


    hash=QCryptographicHash::hash(str_sum_regs.toLocal8Bit(),QCryptographicHash::Md5);

    return hash;
}
//----------------------------------------------------
void MainWindow::on_m_btn_dbg_clicked()
{
    /*HWND hwnd_main=NULL;
    HWND hwnd_grp_Registers=NULL;

    if(m_child_enum_complete)
    {
        hwnd_main=FindWindowEx(0,0,0,L"Analog Devices ADF4355, ADF4355-2, ADF4355-3, ADF5355, and ADF4356 Evaluation Board Control Software");

        if(hwnd_main)
        {
            hwnd_grp_Registers=FindWindowEx(hwnd_main,0,0,L"Registers");

            if(hwnd_grp_Registers)
            {
                m_child_enum_complete=false;
                m_child_enum_cntr_regs_found=0;
                m_child_enum_cntr_all=0;
                EnumChildWindows(hwnd_grp_Registers,on_child_window,(LPARAM)this);
            }
        }

    }*/
}

//--------------------------------------------------------------
void MainWindow::on_m_radio_dmr_mode_clicked(bool checked)
{
    m_send_interface=SEND_INTERFACE_DMR_DLG;
    m_port.close();
    ui->m_grp_com_settings->setEnabled(false);
    ui->m_grp_regs->setEnabled(true);
    ui->m_grp_regs_2->setEnabled(true);
    ui->m_grp_regs_1->setEnabled(true);
    ui->m_grp_f_change->setEnabled(true);

    m_timer_sync.start(500);
    m_connected=true;
}
//--------------------------------------------------------------
void MainWindow::on_m_radio_avr_mode_clicked(bool checked)
{
    m_send_interface=SEND_INTERFACE_COM_PORT;
    ui->m_grp_com_settings->setEnabled(true);
}
