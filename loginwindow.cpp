#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>

#define IP ""       // IP地址
#define PORT 8800   // 端口地址

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

// 初始化
void LoginWindow::init()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

// 连接到服务器
void LoginWindow::connectToServer()
{
    socket->abort();
    socket->connectToHost(IP, PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

// 登录按钮槽函数
void LoginWindow::on_pushButton_login_clicked()
{
    QString name = ui->comboBox_acc->currentText();
    QString passwd = ui->lineEdit_pass->text();
    if ("" == name || "" == passwd) {
        QMessageBox::information(this, "错误", "用户名和密码不能为空", QMessageBox::Ok);
        return;
    }
    QString data = name + '#' + passwd;
    socket->write(data.toLatin1());
}

// 显示错误
void LoginWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug() << socket->errorString();
}

// 读取返回数据
void LoginWindow::readMsg()
{
    QString data = socket->readAll();
}
