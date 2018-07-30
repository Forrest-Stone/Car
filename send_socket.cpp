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
    //connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(Send_Write_Complete()));
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
    QString picture;
    while(!pictures.isEmpty()){
        picture=pictures.dequeue();
        for(int i=1;i<5;++i){
            if(!Send_Write_Process(picture,i)){
                qDebug()<<i<<picture;
                return;
            }
        }
    }
}

bool Send_Socket::Send_Write_Process(const QString &path,const int option)
{
    QList<QByteArray> list;
    qint64 size;
    list.append(Send_Controller::Send_Picture_to_Base64(path,option));
    for(QList<QByteArray>::iterator iter=list.begin();iter!=list.end();++iter){
        size = iter->size();
        socket->write((char *)&size, sizeof(qint64));
        socket->write(iter->data(), size);
        if(socket->waitForBytesWritten(-1)) {
            qDebug()<<socket->errorString();
            return false;
        }else{
            return true;
        }
    }



}



