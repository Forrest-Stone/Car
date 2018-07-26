#include "send_controller.h"
#include "send_filedialog.h"


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


