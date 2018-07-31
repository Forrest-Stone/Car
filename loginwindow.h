#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QtNetwork>

class VertificationLabel;
class QString;
class QStringList;
class UserItemWidget;
class QListWidget;
class LoginSetDialog;

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
    void connectToServer();                             // 连接到服务器
    void saveName(const QString &name);                 // 保存用户名
    QStringList getNames();                             // 获取历史用户名
    void delName(const QString &name);                  // 删除已保存的历史用户名

signals:
    void loginOk(QString ip, int port);                 // 登录成功信号

private slots:
    void displayError(QAbstractSocket::SocketError);    // 显示错误信息
    void sendMsg();                                     // 发送数据
    void readMsg();                                     // 读取数据
    void loginOut();                                    // 登出
    void onShowName(int index, QString name);
    void onRemoveName(int index, QString name);
    void on_pushButton_login_clicked();
    void on_setAddr(QString ip, int port);
    void on_pushButton_set_clicked();
    void on_checkBox_show_pass_stateChanged(int arg1);

private:
    Ui::LoginWindow *ui;
    VertificationLabel *verLabel;   // 验证码控件
    QTcpSocket *socket;             // socket
    QListWidget *name_list;         // 历史用户名列表
    LoginSetDialog *loginSet;       // 设置地址窗口
    QString ip;                     // IP地址
    int port;                       // 端口号
    int flag;                       // 标识当前的操作类型
    enum {
        LOGIN,                      // 登录
        LOGOUT                      // 登出
    };
};

#endif // LOGINWINDOW_H
