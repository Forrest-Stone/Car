#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QtNetwork>
//#include <QAbstractSocket>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

protected:
    void init();
    void connectToServer();

private slots:
    void displayError(QAbstractSocket::SocketError);
    void readMsg();
    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
    QTcpSocket *socket;
};

#endif // LOGINWINDOW_H
