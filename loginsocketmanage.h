#ifndef LOGINSOCKET_H
#define LOGINSOCKET_H

#include <QObject>
#include <QtNetwork>

class LoginSocketManage : public QObject
{
    Q_OBJECT

public:
    enum Flag {                         // 操作类型
        LOGIN,                          // 登录
        LOGOUT                          // 登出
    };
    enum Result {                       // 登录结果
        SUCCESSFUL = 0,                 // 成功
        NOUSERNAME,                     // 用户名不存在
        INVALIDPASSWD                   // 密码错误
    };

    LoginSocketManage();
    ~LoginSocketManage();

    void setAddr(QString ip, int port);                     // 设置连接地址
    void setUserInfo(QString username, QByteArray passwd);  // 设置用户信息
    void connectToServer();                                 // 连接至服务器
    void waitForConn();                                     // 等待连接成功
    void setOperation(Flag flag);                           // 设置操作类型
    void closeSocket();                                     // 关闭Socket
    QString getIP();                                        // 获取IP地址
    int getPort();                                          // 获取端口号

signals:
    void loginResult(LoginSocketManage::Result result);     // 登录结果信号
    void error(QString error);                              // 错误信息信号

public slots:
    void getError(QAbstractSocket::SocketError);            // 获取错误信息
    void sendMsg();                                         // 发送数据
    void readMsg();                                         // 读取数据

private:
    void connSignalSlot();            // 连接信号与槽

    QTcpSocket *m_socket;             // socket
    QString m_ip;                     // IP地址
    int m_port;                       // 端口号

    QString m_username;               // 用户名
    QByteArray m_passwd;                 // 密码

    Flag m_flag;                      // 标识当前的操作类型
};

#endif // LOGINSOCKET_H
