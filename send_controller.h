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
    //编码图片
    static QByteArray Send_Image_to_Base64(const QString&);
private:
};

#endif // SEND_CONTROLLER_H
