#include "send_socket.h"
#include "send_controller.h"
#include <QDebug>
#include <QMessageBox>


Send_Socket::Send_Socket(QWidget *parent) :
    QWidget(parent)
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(Send_Connect_Success()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Send_Connect_Error(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(disconnected()),this,SLOT(Send_Connect_Dis()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(Send_Write_Complete()));
}

bool Send_Socket::Send_Connect(const QString &hostName, quint16 port)
{

    socket->connectToHost(hostName,port);
    return true;
}

bool Send_Socket::Send_Write(QStringList &pictures)
{
    foreach (QString picture, pictures) {
        this->pictures.push_back(picture);
    }
    Send_Write_Complete();
    return true;
}

bool Send_Socket::Send_Disconnect()
{
    socket->disconnectFromHost();
    socket->close();
    //QMessageBox::warning(this,"disconnected","dis",QMessageBox::Yes);
    return true;
}

void Send_Socket::Send_Connect_Success()
{
    QMessageBox::warning(this,"success","seccess",QMessageBox::Yes);
    emit Send_state("connected");
}

void Send_Socket::Send_Connect_Error(QAbstractSocket::SocketError error)
{
    QString worng=socket->errorString();
    qDebug()<<error;
    QMessageBox::warning(this,"error",worng,QMessageBox::Yes);
}

void Send_Socket::Send_Connect_Dis()
{
    //QMessageBox::warning(this,"disconnect","dis",QMessageBox::Yes);
    emit Send_state("disconnected");
}

void Send_Socket::Send_Write_Complete()
{
    //QMessageBox::warning(this,"complete",QString::number(byte),QMessageBox::Yes);
    qDebug()<<pictures.count();
    if(!pictures.isEmpty()){
        QByteArray img = Send_Controller::Send_Image_to_Base64(
                    pictures.dequeue());
        socket->write(img);
    }
}



