#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QTime>
#include <QHostAddress>
#include <QComboBox>
#include "tchar_var.h"

#define INVALID_VALUE8 ((quint8)-1)
#define INVALID_VALUE16 ((quint16)-1)
#define INVALID_VALUE32 ((quint32)-1)
#define INVALID_VALUE64 ((quint64)-1)
#define long2double(a) ((double)(long)(a)/0x80000000)
#define MAKEWORD(lo,hi)((hi&0xff)<<8)|(lo&0xff)
#define MAKEDWORD(lo,hi)((hi&0xffff)<<16)|(lo&0xffff)
#define LOWORD(dw) ( (dw)        & 0xFFFF)
#define HIWORD(dw) (((dw) >> 16) & 0xFFFF)
#define LOBYTE(w) ( (w)     & 0xFF)
#define HIBYTE(w) (((w)>>8) & 0xFF)

#define dim(arr)(sizeof(arr)/sizeof arr[0])
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)
#define DELTA(a,b) (MAX(a,b)-MIN(a,b))
#define IS_MULT(a,b) (a?((a/b)&&((a%b)==0)):1)
#define STR(s) QString(s)
#define NUM2STR(num) QString::number(num)
#define NUM2STR_HEX(num) (QString("0x")+((num)<16?"0":"")+QString::number((num),16).toUpper())
#define NUM2STR_WITH_SEPARATOR(num) (str_num_add_separator(NUM2STR(num)))
#define NUM2STR_WITH_ZEROS(num,valid_digits) (add_left_zeros(num,valid_digits))
#define CURR_DATE_TIME_STR QDateTime::currentDateTime().toString("dd_MM_yy__hh_mm_ss.txt")
#define CURR_TIME_IN_S  (qtime2s(QTime::currentTime()))
#define CURR_TIME_IN_MS  (qtime2ms(QTime::currentTime()))
#define CURR_TIME_STR QTime::currentTime().toString("hh:mm:ss")
#define CURR_TIME_STR_MS QTime::currentTime().toString("hh:mm:ss:zzz")
#define ADD_BUILD_TIME_TITLE {\
                                QString prev_title=this->windowTitle();\
                                QString new_title=prev_title+=" "+QString(__DATE__)+" "+QString(__TIME__);\
                                this->setWindowTitle(QString(new_title));\
                              }
#define SET_WINDOW_FIXED_SIZE {\
                                  this->setFixedHeight(this->height());\
                                  this->setFixedWidth(this->width());\
                              }

#define STR_FILE_POS QString(__FILE__)+":"+QString::number(__LINE__)
//#define OPEN_EXPLORER(path) {QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(path)));}
#define OPEN_EXPLORER(path) {QProcess::startDetached("explorer "+QString(path));}
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
//добавляет 16тибитное слово в байтовый массив. [х]=HI,[х+1]=LO
#define QB_APPEND_WORD(qb_1_,word)  (qb_1_.append(HIBYTE(word)));(qb_1_.append(LOBYTE(word)))
/*добавляет 32хбитное слово в байтовый массив.
[х]=HIBYTE of HIWORD,[х+1]=LO
[х+1]=LOBYTE of HIWORD,[х+1]=LO
[х+2]=HIBYTE of LOWORD,[х+1]=LO
[х+3]=LOBYTE of LOWORD,[х+1]=LO
*/
#define QB_APPEND_DWORD(qb_1_,dword) QB_APPEND_WORD(qb_1_,HIWORD(dword));QB_APPEND_WORD(qb_1_,LOWORD(dword));
//добавляет в байтовый массив указанное число повторений байта
#define QB_ADD_DATA(qb,data,len){for(int _t123t_=0;_t123t_<len;_t123t_++)qb.append(data);}
//возвращает массив с отброшенными числом элементов слева
#define QB_DISCARD_LEFT(qb_1_,num_bytes)qb_1_.right(qb_1_.size()-num_bytes)
//возвращает массив с отброшенными числом элементов справа
#define QB_DISCARD_RIGHT(qb_1_,num_bytes)qb_1_.left(qb_1_.size()-num_bytes)

#define CTRL_TEXT2NUM(ctrl)ctrl->text().toUInt()
#define BREAK_POINT {int d123___dbg__123;d123___dbg__123++;}
//------------------------------------------------------------------------------
enum LOG_MSG_TYPE
{
    LOG_MSG_TYPE_CRITICAL_ERROR,
    LOG_MSG_TYPE_WARNING,
    LOG_MSG_TYPE_REMARK,
    LOG_MSG_TYPE_REMARK_2,
    LOG_MSG_TYPE_REMARK_3,
    LOG_MSG_TYPE_REMARK_4,
    LOG_MSG_TYPE_REMARK_5,
    LOG_MSG_TYPE_CLOSE_LOG,
    LOG_MSG_TYPE_NUM
};
#ifdef WIN32
TCHAR* ms2format_tchar_str(quint32 time_in_ms);
#endif
QString str_num_add_separator(QString str_number,QString separator=" ");
void sync_delay(unsigned int msec);
double trunc_mantissa(double v,unsigned int num_after_point);
int get_rand(int min,int max);
quint32 qtime2s(QTime t);
quint32 qtime2ms(QTime t);
QTime ms2qtime(quint32 ms);
QTime qtime_delta(QTime t1,QTime t2);
quint64 get_file_size(QString full_file_name);
QHostAddress get_self_ip();
QHostAddress get_self_mask();
int get_item_text_indx(QComboBox *cmbox, QString item_text);
QString add_left_zeros(quint64 num,quint64 valid_digs_num);
void calc_bit_rate(int source_num, bool restart, quint32 bytes_num, double* bitrate_out, double* bitrate_avg_out);
quint64 calc_time_left_ms(quint64 data_size_in_bytes, double kbit_per_second);
void log_set_msg_limit(quint32 msg_count);
void log_run(bool run);
void log_colors_out();
void log_close();
void log_set_window_name(QString title);
void log_clr();
void log_msg(QString msg, LOG_MSG_TYPE msg_type=LOG_MSG_TYPE_REMARK, QWidget* parent=0);
//static inline void DebugLine(LPCTSTR szFormat, ...);

#endif // UTILS_H
