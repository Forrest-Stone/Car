#ifndef SEND_CLIENT_H
#define SEND_CLIENT_H

#include <QWidget>

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

private:
    Ui::Send_Client *ui;
};

#endif // SEND_CLIENT_H
