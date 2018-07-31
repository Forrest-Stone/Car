#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

class VertificationLabel;
class QString;
class QStringList;
class UserItemWidget;
class QListWidget;
class LoginSetDialog;

#include "loginsocketmanage.h"

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
    void saveName(const QString &name);                 // 保存用户名
    QStringList getNames();                             // 获取历史用户名
    void delName(const QString &name);                  // 删除已保存的历史用户名

signals:
    void loginOk(QString ip, int port);                 // 登录成功信号

private slots:
    void displayError(QString error);                   // 显示错误信息
    void loginOut();                                    // 登出
    void onShowName(int index, QString name);           // 显示历史用户名
    void onRemoveName(int index, QString name);         // 删除历史用户名
    void on_pushButton_login_clicked();                 // 登录按钮槽函数
    void on_pushButton_set_clicked();                   // 设置地址按钮槽函数
    void on_setAddr(QString ip, int port);              // 设置地址
    void on_checkBox_show_pass_stateChanged(int arg1);  // 显示密码checkbox槽函数
    void onLoginResult(LoginSocketManage::Result res);  // 接收到登录结果后进行相应操作

private:
    Ui::LoginWindow *ui;
    VertificationLabel *m_verLabel;       // 验证码控件
    QListWidget *m_nameList;             // 历史用户名列表
    LoginSetDialog *m_loginSet;           // 设置地址窗口
    LoginSocketManage *m_socketManage;    // 网络管理类
};

#endif // LOGINWINDOW_H
