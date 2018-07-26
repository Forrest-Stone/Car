#include "send_socket.h"
#include <QDebug>
#include <QMessageBox>

Send_Socket::Send_Socket(QWidget *parent) :
    QWidget(parent)
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(Send_Connect_Success()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Send_Connect_Error(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(disconnected()),this,SLOT(Send_Connect_Dis()));
}

bool Send_Socket::Send_Connect(const QString &hostName, quint16 port)
{

    socket->connectToHost(hostName,port);
    return true;
}

bool Send_Socket::Send_Write(QStringList &)
{
    return true;
}

bool Send_Socket::Send_Disconnect()
{
    socket->disconnectFromHost();
    socket->close();
    QMessageBox::warning(this,"disconnected","dis",QMessageBox::Yes);
    return true;
}

void Send_Socket::Send_Connect_Success()
{
    QMessageBox::warning(this,"success","seccess",QMessageBox::Yes);
    emit Send_state("success");
}

void Send_Socket::Send_Connect_Error(QAbstractSocket::SocketError error)
{
    QString worng=socket->errorString();
    QMessageBox::warning(this,"error",worng,QMessageBox::Yes);
}

void Send_Socket::Send_Connect_Dis()
{
    QMessageBox::warning(this,"disconnect","dis",QMessageBox::Yes);
    emit Send_state("disconnected");
}

