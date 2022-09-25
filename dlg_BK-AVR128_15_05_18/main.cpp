#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("SOZVEZDIE");
    QCoreApplication::setApplicationName("dlg_BK-AVR128");

    MainWindow w;
    QByteArray q,q1;
    q.append(10);
    q.append(20);
    q.append(30);

    q1.append(10);
    q1.append(20);
    q1.append(31);
    //if(q==q1)
    {
       w.show();
    }
    return a.exec();
}
