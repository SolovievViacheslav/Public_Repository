#include "utils.h"
#include "tchar_var.h"
#include <math.h>
#include <assert.h>
#include <queue>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QNetworkInterface>
#include <QTextEdit>
#include <QMessageBox>
//--------------------------------------------------------
#ifdef WIN32
TCHAR* ms2format_tchar_str(quint32 time_in_ms)
{
    static TCHAR out_buff[100];
    out_buff[0]=0;
    quint32 src_t=time_in_ms;
    quint32 h=(src_t)/(60*60*1000);
    quint32 m=(src_t-h*60*60*1000)/(60*1000);
    quint32 s=(src_t-h*60*60*1000-m*60*1000)/1000;
    quint32 ms=(src_t-h*60*60*1000-m*60*1000-s*1000);

    TCHAR tmp_str[100];
    TCHAR zero_str[100];
    zero_str[0]=zero_str[1]=zero_str[2]='0';
    //---------------------------------
    _itot(h,tmp_str,10);
    if(_tcslen(tmp_str)==1)
    {
        _tcscpy(&zero_str[1],tmp_str);
        _tcscat(out_buff,&zero_str[0]);
        zero_str[0]=zero_str[1]=zero_str[2]='0';
    }
    else
    {
        _tcscat(out_buff,tmp_str);
    }
    _tcscat(out_buff,_T(":"));
    //---------------------------------

    _itot(m,tmp_str,10);
    if(_tcslen(tmp_str)==1)
    {
        _tcscpy(&zero_str[1],tmp_str);
        _tcscat(out_buff,&zero_str[0]);
        zero_str[0]=zero_str[1]=zero_str[2]='0';
    }
    else
    {
        _tcscat(out_buff,tmp_str);
    }
    _tcscat(out_buff,_T(":"));
    //---------------------------------

    _itot(s,tmp_str,10);
    if(_tcslen(tmp_str)==1)
    {
        _tcscpy(&zero_str[1],tmp_str);
        _tcscat(out_buff,&zero_str[0]);
        zero_str[0]=zero_str[1]=zero_str[2]='0';
    }
    else
    {
        _tcscat(out_buff,tmp_str);
    }
    _tcscat(out_buff,_T(":"));
    //---------------------------------

    _itot(ms,tmp_str,10);
    if(_tcslen(tmp_str)==1)
    {
        _tcscpy(&zero_str[2],tmp_str);
        _tcscat(out_buff,&zero_str[0]);
        zero_str[0]=zero_str[1]=zero_str[2]='0';
    }
    else if(_tcslen(tmp_str)==2)
    {
        _tcscpy(&zero_str[1],tmp_str);
        _tcscat(out_buff,&zero_str[0]);
        zero_str[0]=zero_str[1]=zero_str[2]='0';
    }
    else
        _tcscat(out_buff,tmp_str);

    return out_buff;
}
#endif
//--------------------------------------------------------
//разделение строкового представления числа на группы по 3 цифры
QString str_num_add_separator(QString str_number,QString separator)
{
    QString str_tmp_freq=str_number;
    for(int i=str_tmp_freq.length()-3;i>0;i-=3)
    {
        str_tmp_freq.insert(i,separator);
    }
    return str_tmp_freq;
}
//--------------------------------------------------------
//[min..max]
int get_rand(int min,int max)
{
    int retval=max+1;
    static int v=((CURR_TIME_IN_MS)&0xffff);
    v++;
    srand(v);
    qDebug()<<"$$$$$$$$$$$$$v%%%%%%%%%"<<v;
    while(retval>max)
    {
        retval=min;
        retval+=(rand()%max);
    }

    return retval;
}
//--------------------------------------------------------
QString add_left_zeros(quint64 num,quint64 valid_digs_num)
{
    int digs_in_num=NUM2STR(num).length();
    int zeros_num=valid_digs_num-digs_in_num;
    QString retval;
    for(int i=0;i<zeros_num;i++)
        retval.append("0");

    retval+=NUM2STR(num);

    return retval;
}
//--------------------------------------------------------
void sync_delay_up_to1000(unsigned int msec)
{
    unsigned int p=QTime::currentTime().msec();
    unsigned int t=QTime::currentTime().msec();

    unsigned int t_wait=msec;
    unsigned int t_to_ovf=1000-t;
    unsigned int t_wait_after_ovf=0;

    if(t_wait>t_to_ovf)
    {
        t_wait_after_ovf=msec-t_to_ovf;
    }
    while((t-p)<t_wait)
    {
        t=QTime::currentTime().msec();
        if(t<p)
        {
            t_wait=t_wait_after_ovf;
            p=0;
        }
    }

}
//--------------------------------------------------------
void sync_delay(unsigned int msec)
{
    unsigned int p=QTime::currentTime().msec();
    unsigned int t=QTime::currentTime().msec();
    unsigned int sec_cntr=msec/1000;
    unsigned int rem_msec=msec-(sec_cntr*1000);
    unsigned int t_wait=msec;
    unsigned int t_to_ovf=1000-t;
    unsigned int t_wait_after_ovf=0;

    for(int i=0;i<sec_cntr;i++)
    {
       sync_delay_up_to1000(1000);
    }
    sync_delay_up_to1000(rem_msec);
}
//--------------------------------------------------------
quint32 qtime2s(QTime t)
{
    QTime tmp;
    tmp.setHMS(0,0,0);
    return tmp.secsTo(t);
}
//--------------------------------------------------------
quint32 qtime2ms(QTime t)
{
    QTime tmp;
    tmp.setHMS(0,0,0);
    return tmp.msecsTo(t);
}
//--------------------------------------------------------
QTime ms2qtime(quint32 ms)
{
    QTime t;
    quint16 h,m,s,ms_out;

    h=(ms/1000)/(60*60);
    m=(ms/1000-h*60*60)/(60);
    s=(ms/1000-(h*60*60+m*60));
    ms_out=(ms-(h*60*60+m*60+s)*1000);
    t.setHMS(h,m,s,ms_out);

    return t;
}
//--------------------------------------------------------
QTime qtime_delta(QTime t1,QTime t2)
{
    QTime retval;

    retval.setHMS(0,0,0);

    if(t1<t2)
        retval=retval.addMSecs(t1.msecsTo(t2));
    else
        retval=retval.addMSecs(t2.msecsTo(t1));

    return retval;

}
//--------------------------------------------------------
double trunc_mantissa(double v,unsigned int num_after_point)
{
    bool add1=false;
    bool minus=false;
    if(v<0){minus=true;v=-1*v;}
    int c=v;

    //разобьем мантиссу на целую и дробную часть
    //целая часть==число знаков после запятой от исходного числа
    double mant2double=(v-c)*pow(10,num_after_point);
    unsigned int int_from_mantissa=mant2double;
    double d=(mant2double-int_from_mantissa)*pow(10,1);
    //следующая цифра за теми, которые хотел видеть пользователь
    unsigned int next_num=d;
    add1=(next_num>=5)?true:false;
    int m=(v-c)*pow(10,num_after_point);
    m=add1?(m+1):m;
    double t=(double)m/pow(10,num_after_point);
    double r=c+t;
    if(minus)r=r*-1;
    return r;
}
//--------------------------------------------------------
void calc_bit_rate(int source_num,
                   bool restart,
                   quint32 bytes_num=0,
                   double* bitrate_out=0, double* bitrate_avg_out=0)
{
   static struct
    {
        double rate_arr[100];
        const int arr_elements_num=dim(rate_arr);
        int rate_arr_indx;
        double rate_arr_sum;
        quint32 ms_prev;
        quint32 prev_size;
        quint32 ms_curr;
        quint32 ms_delta;
        quint32 bytes_cntr;
        quint32 ms_cntr;
        double avg_bit_rate;

    }sources[10];

   if(source_num<dim(sources))
   {
       sources[source_num].ms_curr=qtime2ms(QTime::currentTime());
       if(sources[source_num].ms_prev==0)sources[source_num].ms_prev=sources[source_num].ms_curr;
       sources[source_num].ms_delta=sources[source_num].ms_curr-sources[source_num].ms_prev;

       if(restart)
        {
            for(int i=0;i<sources[source_num].arr_elements_num;i++)
             sources[source_num].rate_arr[i]=0;

            sources[source_num].rate_arr_indx=0;
            sources[source_num].ms_prev=0;
            sources[source_num].prev_size;
            sources[source_num].ms_curr=qtime2ms(QTime::currentTime());
            sources[source_num].ms_prev=sources[source_num].ms_curr;
            sources[source_num].ms_delta=sources[source_num].ms_curr-sources[source_num].ms_prev;
            sources[source_num].bytes_cntr=0;
            sources[source_num].ms_cntr=0;
            sources[source_num].avg_bit_rate=0;
            sources[source_num].rate_arr_sum=0;
            sources[source_num].rate_arr_indx=0;
            return;
        }

        sources[source_num].ms_cntr+=sources[source_num].ms_delta;
        sources[source_num].bytes_cntr+=bytes_num;

        sources[source_num].avg_bit_rate=0;

        /*if(ms_cntr/1000)avg_bit_rate=(bytes_cntr*8)/(ms_cntr/1000);
        else avg_bit_rate=avg_bit_rate/1000;
        */
        double bit_rate=0;
        bit_rate=0;
        if(sources[source_num].ms_delta)
        {
            bit_rate=(bytes_num*8)/((double)sources[source_num].ms_delta/1000);
            bit_rate=bit_rate/1000;
            sources[source_num].rate_arr_sum+=bit_rate;
            sources[source_num].rate_arr[sources[source_num].rate_arr_indx++]=bit_rate;
            sources[source_num].avg_bit_rate=(sources[source_num].rate_arr_sum/sources[source_num].rate_arr_indx);
            if(sources[source_num].rate_arr_indx==sources[source_num].arr_elements_num)
            {
               sources[source_num].rate_arr_indx=0;
               sources[source_num].rate_arr_sum=0;
            }
        }

        if(bitrate_out)
            *bitrate_out=trunc_mantissa(bit_rate,2);

        if(bitrate_avg_out)
            *bitrate_avg_out=trunc_mantissa(sources[source_num].avg_bit_rate,2);

        sources[source_num].ms_prev=sources[source_num].ms_curr;
   }
}
//--------------------------------------------------------
quint64 calc_time_left_ms(quint64 data_size_in_bytes, double kbit_per_second)
{
    QTime retval;
    quint64 sec_left;
    sec_left=(data_size_in_bytes*8)/(kbit_per_second*1000);
    return sec_left*1000;
}
//--------------------------------------------------------
quint64 get_file_size(QString full_file_name)
{
    quint64 sz=0;
    QFile* file=new QFile(full_file_name);

    if(file)
    {
       sz=file->size();
       delete file;
    }

    return sz;
}
//--------------------------------------------------------
int get_item_text_indx(QComboBox* cmbox, QString item_text)
{
    int retval=-1;
    for(int i=0;i<cmbox->count();i++)
    {
        if (item_text.toUpper()==cmbox->itemText(i).toUpper())
        {
            retval=i;
            break;
        }
    }
    return retval;
}
//--------------------------------------------------------
QHostAddress get_self_ip()
{
    QHostAddress self_ip;

    foreach (const QHostAddress &ip_addr, QNetworkInterface::allAddresses() )
    {
        if((ip_addr.protocol()==QAbstractSocket::IPv4Protocol) &&
           (ip_addr!=QHostAddress(QHostAddress::LocalHost)))
        {
            self_ip=ip_addr;
            break;
        }
    }
    return self_ip;
}
//--------------------------------------------------------
QHostAddress get_self_mask()
{
    QHostAddress self_mask;
    QHostAddress self_ip;

    self_ip=get_self_ip();

    foreach (const QNetworkInterface &net_interface, QNetworkInterface::allInterfaces())
    {
        foreach (const QNetworkAddressEntry &addr_entry, net_interface.addressEntries())
        {
            /*if((ip_addr.protocol()==QAbstractSocket::IPv4Protocol) &&
               (ip_addr!=QHostAddress(QHostAddress::LocalHost)))
            */
            if(self_ip==addr_entry.ip())
            {
                self_mask=addr_entry.netmask();
                break;
            }
        }
    }
    return self_mask;
}
//--------------------------------------------------------
QTextEdit* g_edit_log=0;
QString g_str_window_title="";
QTextCursor g_cursor;
QWidget *g_parent=0;
bool g_log_on=false;
quint32 g_log_msg_limit=4;
quint32 g_log_msg_count=0;
quint32 g_log_window_num=1;
//--------------------------------------------------------
void log_set_msg_limit(quint32 msg_count)
{
    g_log_msg_limit=msg_count;
}
//--------------------------------------------------------
void log_run(bool run)
{
    g_log_on=run;
}
//--------------------------------------------------------
void log_close()
{
    if(g_edit_log)
    {
        g_edit_log->close();
        g_edit_log=0;
    }
}
//--------------------------------------------------------
void log_set_window_name(QString title)
{
    g_str_window_title=title;
}
//--------------------------------------------------------
void log_clr()
{
    if(g_edit_log)
        g_edit_log->setText("");
}
//--------------------------------------------------------
void log_colors_out()
{
    log_msg("LOG_MSG_TYPE_CRITICAL_ERROR",LOG_MSG_TYPE_CRITICAL_ERROR);
    log_msg("LOG_MSG_TYPE_WARNING",LOG_MSG_TYPE_WARNING);
    log_msg("LOG_MSG_TYPE_REMARK",LOG_MSG_TYPE_REMARK);
    log_msg("LOG_MSG_TYPE_REMARK_2",LOG_MSG_TYPE_REMARK_2);
    log_msg("LOG_MSG_TYPE_REMARK_3",LOG_MSG_TYPE_REMARK_3);
    log_msg("LOG_MSG_TYPE_REMARK_4",LOG_MSG_TYPE_REMARK_4);
    log_msg("LOG_MSG_TYPE_REMARK_5",LOG_MSG_TYPE_REMARK_5);
}
//--------------------------------------------------------
void log_msg(QString msg, LOG_MSG_TYPE msg_type, QWidget *parent)
{
    QColor log_text_color[LOG_MSG_TYPE_NUM];
    if(!g_log_on)return;
    log_text_color[LOG_MSG_TYPE_CRITICAL_ERROR]="Red";
    log_text_color[LOG_MSG_TYPE_WARNING]="Yellow";
    log_text_color[LOG_MSG_TYPE_REMARK]="Green";
    log_text_color[LOG_MSG_TYPE_REMARK_2]="Blue";
    log_text_color[LOG_MSG_TYPE_REMARK_3]="Cyan";
    log_text_color[LOG_MSG_TYPE_REMARK_4]="Light gray";
    log_text_color[LOG_MSG_TYPE_REMARK_5]="White";


    if(msg_type!=LOG_MSG_TYPE_CLOSE_LOG)
    {
        if(!g_edit_log)
        {

            QFont font;
            font.fromString("MS Shell Dlg 2,14,-1,5,50,0,0,0,0,0");
            g_edit_log=new QTextEdit();
            g_edit_log->setFont(font);
            g_edit_log->setStyleSheet("background-color: rgb(0, 0, 0)");
            g_edit_log->setTextColor(log_text_color[msg_type]);
            g_edit_log->setText(CURR_TIME_STR+" Window num: "+NUM2STR(g_log_window_num));
        }

        if(parent)
        {
            g_parent=parent;
        }

        if(g_parent)
        {
            g_edit_log->setWindowTitle("L "+g_parent->windowTitle());
        }
        else
        {
            if(g_str_window_title!=g_edit_log->windowTitle())
            {
                g_edit_log->setWindowTitle(g_str_window_title);
            }
        }

        g_edit_log->setTextColor(log_text_color[msg_type]);
        //если в окне уже лежит максимум строк, а мы хотим добавить еще - сотрем
        if(g_log_msg_count==g_log_msg_limit)
        {
            /*g_cursor=g_edit_log->textCursor();
            g_cursor.movePosition(QTextCursor::Start);
            g_cursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,0);
            g_cursor.select(QTextCursor::LineUnderCursor);
            g_cursor.removeSelectedText();
            g_edit_log->setTextCursor(g_cursor);*/
            g_edit_log->setText("");
            g_log_window_num++;
            g_edit_log->setText(CURR_TIME_STR+" Window num: "+NUM2STR(g_log_window_num));
            g_log_msg_count=0;

        }

        g_edit_log->append(msg);
        g_log_msg_count++;
        //quint32 lines_num=g_edit_log->co
        g_edit_log->show();
        //QMessageBox::information(0,"Логирование",msg);
        //assert(!stop);
    }
    else
    {
        if(g_edit_log)
        {
            g_edit_log->setVisible(false);
            delete g_edit_log;
            g_edit_log=0;
        }
    }
}
//--------------------------------------------------------
