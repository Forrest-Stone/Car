#ifndef SEND_CLIENT_H
#define SEND_CLIENT_H

#include <QWidget>
#include "send_controller.h"


namespace Ui {
class Send_Client;
}

class Send_Client : public QWidget
{
    Q_OBJECT

public:
    explicit Send_Client(QWidget *parent = 0);
    ~Send_Client();

private slots:
    void on_choose_picture_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_reset_pushButton_clicked();

    void on_login_out_pushButton_clicked();

    void on_send_picture_pushButton_clicked();

private:
    Ui::Send_Client *ui;
    Send_Controller controller;
    //选择图片
    QStringList Send_Choose_Pictures();
};

#endif // SEND_CLIENT_H
