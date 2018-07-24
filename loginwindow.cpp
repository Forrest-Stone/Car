#include <QString>
#include <QMessageBox>
#include "loginwindow.h"

#define IP ""               // IP��ַ
#define PORT 8000           // �˿ں�

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    init();
    connectToServer();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

// ��ʼ��
void LoginWindow::init()
{
    ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

// ���ӵ�������
void LoginWindow::connectToServer()
{
    socket->abort();
    socket->connectToHost(IP, PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

// ��¼��ť�ۺ���
void LoginWindow::on_pushButton_login_clicked()
{
    QString userName = ui->comboBox_acc->currentText();
    QString passwd = ui->lineEdit_pass->text();
    if ("" == userName || "" == passwd) {
        QMessageBox::information(this, tr("����"), tr("���벻��Ϊ�գ�"), QMessageBox::Ok);
        return;
    }
    QString data = userName + '#' + passwd;
    socket->write(data.toLatin1());
}

// ��ʾ����
void LoginWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug() << socket->errorString();
}

// ��ȡ��Ϣ
void LoginWindow::readMsg()
{
    QString data = socket->readAll();
    if ("" == data) {
        // ��֤ͨ��
    } else {
        // ��֤ʧ��
        QMessageBox::information(this, "����", "�û����������������", QMessageBox::Ok);
    }
}
