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

QByteArray Send_Controller::Send_Image_to_Base64(const QString &path)
{
    QByteArray block;
    QBuffer buffer;
       // QString style;
    QDataStream out(&block,QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_8);
    //style = pictureString_list[picIndex].right(3);
    buffer.open(QIODevice::WriteOnly);
    QPixmap pix;
    pix.load(path);
    pix.save(&buffer,"JPG");

    //picturelist[picIndex].save(&buffer,style.toStdString().c_str());
    //picIndex++;
    qDebug()<<"buffer"<<buffer.data().size();
    out<<(quint64)buffer.data().size();
    //out<<style;
    block.append(buffer.data());
    return block;
}



