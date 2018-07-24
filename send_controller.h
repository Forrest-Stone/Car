#ifndef SEND_CONTROLLER_H
#define SEND_CONTROLLER_H

#include <QStringList>

class Send_Controller
{
public:
    Send_Controller();
    //更改图片样式
    void Send_Set_Item_Model();
    //发送选中的图片
    bool Send_Pictures();
    //获取要发送的图片
    Send_get_Pictures(QStringList &);
private:
    QStringList pictures;

};

#endif // SEND_CONTROLLER_H
