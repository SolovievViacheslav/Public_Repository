#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>
#include <QTimer>
#include "QCryptographicHash"

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

    void on_m_btn_send_reg_0_clicked();

    void on_m_btn_send_reg_1_clicked();

    void on_m_btn_send_reg_2_clicked();

    void on_m_btn_send_reg_3_clicked();

    void on_m_btn_send_reg_4_clicked();

    void on_m_btn_send_reg_5_clicked();

    void on_m_btn_send_reg_6_clicked();

    void on_m_btn_send_reg_7_clicked();

    void on_m_btn_send_reg_8_clicked();

    void on_m_btn_send_reg_9_clicked();

    void on_m_btn_send_reg_10_clicked();

    void on_m_btn_send_reg_11_clicked();

    void on_m_btn_send_reg_12_clicked();

    void on_m_btn_send_reg_12_0_clicked();

    void on_m_btn_send_reg_0_2_clicked();

    void on_m_btn_send_reg_1_2_clicked();

    void on_m_btn_send_reg_2_2_clicked();

    void on_m_btn_copy_f1_to_f2_clicked();

    void on_m_btn_start_f_change_clicked();

private:
    enum SEND_INTERFACE
    {
        SEND_INTERFACE_COM_PORT,
        SEND_INTERFACE_DMR_DLG
    }m_send_interface;

    QSerialPort m_port;
    QString m_port_name;
    QSettings m_settings;
    bool m_connected;
    QTimer m_timer_f_change;
    QTimer m_timer_sync;
    quint32 m_f1_work_time_ms;
    quint32 m_f1_idle_time_ms;
    quint32 m_f2_work_time_ms;
    quint32 m_f2_idle_time_ms;
    quint32 m_state_cntr;

public:
    Ui::MainWindow *ui;
    enum SYNC_F
    {
        SYNC_F_1,
        SYNC_F_2,
        SYNC_F_NO
    };
    /*ключ - номер дочернего окна(текстовое
     *поле - значение регестра в заводоской программе);
     *значение-индекс регистра [0..12]*/
    QHash<quint32,quint32> m_reg_num;
    QString m_str_regs[13];
    quint32 m_child_enum_cntr_all;
    quint32 m_child_enum_cntr_regs_found;
    bool m_child_enum_complete;
    SYNC_F m_sync_f;
    QByteArray m_hash_f1_save;
    QByteArray m_hash_f2_save;
    HWND m_hwnd_dlg_dmr;
    HWND m_hwnd_dlg_dmr_synt_edit;
    HWND m_hwnd_dlg_dmr_synt_list_box_regs;
    HWND m_hwnd_dlg_dmr_synt_btn;
private:
    void closeEvent ( QCloseEvent * e );
    void on_connected();
    void save_settings();
    void restore_settings();
    void send_txt_reg(quint8 reg_num,QString str_reg);
public:
    void sync2f1();
    void sync2f2();
    QByteArray calc_hash_f1();
    QByteArray calc_hash_f2();
private slots:
    void on_m_timer_f_change();
    void on_m_timer_sync();
    void on_m_btn_send_reg_0_6_2_clicked();
    void on_m_radio_sync_f1_clicked(bool checked);
    void on_m_radio_sync_no_clicked(bool checked);
    void on_m_radio_sync_f2_clicked(bool checked);
    void on_m_btn_dbg_clicked();
    void on_m_btn_send_reg_0_6_clicked();

    void on_m_radio_dmr_mode_clicked(bool checked);
    void on_m_radio_avr_mode_clicked(bool checked);
};

#endif // MAINWINDOW_H
