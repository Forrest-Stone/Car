#ifndef SEND_CONTROLLER_H
#define SEND_CONTROLLER_H

#include <QStringList>
#include <QTcpSocket>
#include "send_list_item.h"

class Send_Client;

class Send_Controller
{
    friend class Send_Client;
public:
    Send_Controller();
    //更改图片样式
    //static void Send_Set_Item_Model(int type);
    //发送选中的图片
    //static bool Send_Pictures(const QStringList &);
    //生成item
    static Send_List_Item* Send_Create_Item(const QString &);
    //创建一条数据
    static QList<QByteArray> Send_Picture_to_Base64(const QString&,const int);
private:
    //编码文件名
    static QByteArray Send_Name_to_Base64(const QString&);
    //编码文件大小
    static QByteArray Send_Size_to_Base64(const QString&);
    //编码图片
    static QList<QByteArray> Send_Image_to_Base64(const QString&);
    //编码结束
    static QByteArray Send_End_to_Base64(const QString&);

};

#endif // SEND_CONTROLLER_H
