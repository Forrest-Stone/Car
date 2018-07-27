#include "mainwindow.h"
#include "send_client.h"
//#include "send_test_server.h"
#include <QApplication>
//#include <opencv2/opencv.hpp>

#include <QNetworkInterface>

//using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Send_test_Server server;
    Send_Client c;
    c.show();


    /*QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address())
            {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        qDebug()<<ipAddress;*/
    return a.exec();
}
