#ifndef SEND_CLIENT_H
#define SEND_CLIENT_H

#include <QWidget>
#include "send_controller.h"
#include "send_socket.h"


namespace Ui {
class Send_Client;
}

class Send_Client : public QWidget
{
    Q_OBJECT
    friend class Send_Controller;
public:
    explicit Send_Client(QWidget *parent = 0);
    ~Send_Client();

private slots:
    void on_choose_picture_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_reset_pushButton_clicked();

    void on_login_out_pushButton_clicked();

    void on_send_picture_pushButton_clicked();

    void connect_state_change(const QString&);
private:
    Ui::Send_Client *ui;
    QStringList pictures;
    //QTcpSocket *socket;
    Send_Socket *socket;
    //选择图片
    bool Send_Choose_Pictures();
};

#endif // SEND_CLIENT_H
