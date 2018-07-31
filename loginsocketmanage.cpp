#include "loginsocketmanage.h"
#include <QByteArray>
#include <QDebug>

LoginSocketManage::LoginSocketManage()
{
    m_socket = new QTcpSocket();
    connSignalSlot();
}

LoginSocketManage::~LoginSocketManage()
{
    if (NULL != m_socket) {
        delete m_socket;
    }
}

// 连接信号与槽
void LoginSocketManage::connSignalSlot() {
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(getError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()),this, SLOT(readMsg()));
    connect(m_socket, SIGNAL(connected()),this, SLOT(sendMsg()));
}

// 设置连接地址
void LoginSocketManage::setAddr(QString ip, int port)
{
    m_ip = ip;
    m_port = port;
}

// 设置用户信息
void LoginSocketManage::setUserInfo(QString username, QByteArray passwd)
{
    m_username = username;
    m_passwd = passwd;
}

// 连接至服务器
void LoginSocketManage::connectToServer()
{
    m_socket->abort();
    m_socket->connectToHost(m_ip, m_port);
}

// 设置操作类型
void LoginSocketManage::setOperation(Flag flag)
{
    m_flag = flag;
}

// 关闭Socket
void LoginSocketManage::closeSocket()
{
    m_socket->close();
}

// 错误信息
void LoginSocketManage::getError(QAbstractSocket::SocketError)
{
    emit error(m_socket->errorString());
}

// 发送数据
void LoginSocketManage::sendMsg()
{
    if (!m_socket->isValid()) {
        return;
    }
    QByteArray data;
    if (LOGIN == m_flag) {            // 发送登录数据
        data.append(m_username);
        data.append('#');
        data.append(m_passwd);
        data.append('$');
        // qDebug() << data;
    } else if (LOGOUT == m_flag) {    // 发送登出数据
        data.append('!');
    }
    m_socket->write(data);
}

// 读取数据
void LoginSocketManage::readMsg()
{
    QString data = m_socket->readAll();
    bool ok;
    int res = data.toInt(&ok);
    if (false == ok) {
        qDebug() << QStringLiteral("接收数据格式错误：需要int");
        return;
    }
    // 发送信号
    if (SUCCESSFUL == res) {
        emit loginResult(SUCCESSFUL);
    } else if (NOUSERNAME == res) {
        emit loginResult(NOUSERNAME);
    } else if (INVALIDPASSWD == res) {
        emit loginResult(INVALIDPASSWD);
    }
}

// 获取IP
QString LoginSocketManage::getIP()
{
    return m_ip;
}

// 获取端口
int LoginSocketManage::getPort()
{
    return m_port;
}
