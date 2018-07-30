#include "mainwindow.h"
#include "send_client.h"
//#include "send_test_server.h"
#include <QApplication>
#include "loginwindow.h"
#include <QNetworkInterface>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login;
    login.show();

    Send_Client c;
    // c.show();

    return a.exec();
}
