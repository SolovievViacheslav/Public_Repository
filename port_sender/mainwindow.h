#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include "qextserialport.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_btn_connect_clicked();
    void on_timer_send();
    void on_timer_refresh_gui();
    void on_timer_processing();
    void on_data_recived();

    void on_m_btn_start_send_clicked();
    void on_m_btn_reset_stat_clicked();

    void on_m_btn_dbg_clicked();

    void on_m_radio_role_sender_clicked(bool checked);

    void on_m_radio_role_reciver_clicked(bool checked);

    void on_m_btn_dbg_2_clicked();

private:
    QTimer m_timer_refresh_gui;
    QTimer m_timer_processing;
    QByteArray m_qb_data_send;
    //QByteArray m_qb_data_recived;
    QByteArray m_qb_data_raw_recived;
    QTimer m_timer_send;
    quint32 m_send_cntr;
    quint32 m_send_cntr_save;
    quint32 m_rcv_cntr;
    quint32 m_rcv_cntr_save;
    quint32 m_err_cntr;
    quint32 m_err_cntr_save;
    quint32 m_shift;
    bool m_dbg_f1;
    QextSerialPort m_port;
    Ui::MainWindow *ui;
    enum FOCUS_ON
    {
        FOCUS_ON_SEND,
        FOCUS_ON_RCV,
        FOCUS_ON_NONE
    };
    void set_on_focus(enum FOCUS_ON focus);

    quint32 check_errors();
    //проверяет байт на совпадение с шаблоном. Если не совпал-сдвигает побитово и проверяет.
    //если совпал, тогда в shift - число битов сдвига.
    //shift_right - сдвигали вправо(true) сдвигали влево(false)
    bool pattern_match(quint8 pattern,quint8 byte,quint8* shift, bool* shift_right);
};

#endif // MAINWINDOW_H
