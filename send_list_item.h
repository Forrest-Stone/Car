#ifndef SEND_LIST_ITEM_H
#define SEND_LIST_ITEM_H

#include <QListWidgetItem>
#include <QDateTime>

class Send_List_Item : public QListWidgetItem
{
public:
    //explicit Send_List_Item(QListWidget *view = nullptr, int type = Type);
    /*explicit Send_List_Item(const QString &text, QListWidget *view = nullptr,
                             int type = Type);
    explicit Send_List_Item(const QString &text, const QString &time,
                             QListWidget *view = nullptr, int type = Type);
    explicit Send_List_Item(const QIcon &icon, const QString &text,
                             QListWidget *view = nullptr, int type = Type);*/
    explicit Send_List_Item(const QIcon &icon, const QString &name,const QString &time =
                             QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"),
                             QListWidget *view = nullptr,
                             int type = Type);

    //接口函数，显示图片名，拍摄时间
    void setText(const QString &,const QString &);
    //void setIcon(const QIcon &icon);
    //static void Send_set_item_Model(int tpye);

};

#endif // SEND_LIST_ITEM_H
