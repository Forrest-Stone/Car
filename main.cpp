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
    //login.show();

    Send_Client client;
    //QObject::connect(&login,SIGNAL(loginOk(QString,int)),&client,SLOT(Login_in(QString,int)));
    //QObject::connect(&client,SIGNAL(Send_login_out()),&login,SLOT(loginOut()));
    client.show();
    return a.exec();
}
