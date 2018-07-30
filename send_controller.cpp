#include "send_controller.h"
#include "send_filedialog.h"
#include <QBuffer>

Send_Controller::Send_Controller()
{
    //socket=new QTcpSocket(Send_Client);
}


Send_List_Item* Send_Controller::Send_Create_Item(const QString &picture)
{
    QIcon icon(picture);
    Send_List_Item * item=new Send_List_Item(icon,picture);
    return item;
}

QByteArray Send_Controller::Send_Name_to_Base64(const QString &path)
{

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);

    block.clear();
    out.device()->seek(0);

    int count=path.split('/').count()-1;
    out << 0x01 << path.section('/',count,count);

    return block;
}

QByteArray Send_Controller::Send_Size_to_Base64(const QString &path)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<path<<"open fail";
        return NULL;
    }

    block.clear();
    out.device()->seek(0);
    out << 0x02 << QString::number(file.size());

    file.close();
    return block;
}

QList<QByteArray> Send_Controller::Send_Image_to_Base64(const QString &path)
{
    QList<QByteArray> list;
    list.clear();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<path<<"open fail";
        return list;
    }

    do{
        block.clear();
        out.device()->seek(0);
        out << 0x03 << file.read(0xFFFF);
        list.push_back(block);
    }while(!file.atEnd());

    file.close();
    return list;
}

QByteArray Send_Controller::Send_End_to_Base64(const QString &path)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);

    block.clear();
    out.device()->seek(0);
    int count=path.split('/').count()-1;
    out << 0x04 << path.section('/',count,count);

    return block;
}

QList<QByteArray> Send_Controller::Send_Picture_to_Base64(const QString &path, const int option)
{
    QList<QByteArray> block;
    block.clear();
    switch (option) {
    case 1:
        block.append(Send_Name_to_Base64(path));
        break;
    case 2:
        block.append(Send_Size_to_Base64(path));
        break;
    case 3:
        block.append(Send_Image_to_Base64(path));
        break;
    case 4:
        block.append(Send_End_to_Base64(path));
        break;
    default:
        break;
    }
    return block;
}



