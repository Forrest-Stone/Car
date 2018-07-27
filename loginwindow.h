#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QtNetwork>

class VertificationLabel;
class QString;
class QStringList;
class UserItemWidget;
class QListWidget;

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
    void connectToServer();         //连接到服务器
    void saveName(const QString &name);             // 保存用户名
    QStringList getNames();                         // 获取历史用户名
    void delName(const QString &name);              // 删除已保存的历史用户名

private slots:
    void displayError(QAbstractSocket::SocketError);
    void readMsg();
    void onShowName(int index, QString name);
    void onRemoveName(int index, QString name);
    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
    VertificationLabel *verLabel;
    QTcpSocket *socket;
    QListWidget *name_list;
};

#endif // LOGINWINDOW_H
