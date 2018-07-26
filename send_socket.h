#ifndef SEND_SOCKET_H
#define SEND_SOCKET_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>

class Send_Socket : public QWidget
{
    Q_OBJECT
public:
    explicit Send_Socket(QWidget *parent = nullptr);
    bool Send_Connect(const QString &hostName, quint16 port);
    bool Send_Write(QStringList &);
    bool Send_Disconnect();
signals:
    void Send_state(const QString &);
private slots:
    void Send_Connect_Success();
    void Send_Connect_Error(QAbstractSocket::SocketError);
    void Send_Connect_Dis();
private:
    QTcpSocket *socket;
};

#endif // SEND_SOCKET_H
