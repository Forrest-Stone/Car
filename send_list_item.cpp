#include "send_list_item.h"
#include <QSize>


/*Send_List_Item::Send_List_Item(QListWidget *view, int type):
    QListWidgetItem(view,type)
{

}*/
//显示
Send_List_Item::Send_List_Item(const QIcon &icon, const QString &name, const QString &time, QListWidget *view, int type):
    QListWidgetItem(view,type)
{
    Send_List_Item::setText(name,time);
    setIcon(icon);
    setSizeHint(QSize(100,200));
}

void Send_List_Item::setText(const QString &name, const QString &time)
{
    QListWidgetItem::setText(name+"\n"+time);
}


/*
Send_List_Item::Send_List_Item(const QString &text, QListWidget *view, int type):
    QListWidgetItem(view,type)
{

}

Send_List_Item::Send_List_Item(const QString &text, const QString &time, QListWidget *view, int type):
    QListWidgetItem(view,type)
{

}

Send_List_Item::Send_List_Item(const QIcon &icon, const QString &text, QListWidget *view, int type):
    QListWidgetItem(view,type)
{

}

Send_List_Item::Send_List_Item(const QIcon &icon, const QString &text, const QString &time, QListWidget *view, int type):
    QListWidgetItem(view,type)
{

}
*/
