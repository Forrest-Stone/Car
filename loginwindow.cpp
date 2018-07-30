#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "vertificationlabel.h"
#include "useritemwidget.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <QtXml>
#include <QImage>
#include <QPainter>
#include "loginsetdialog.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    init();
}

LoginWindow::~LoginWindow()
{
    socket->close();
    delete ui;
}

// 初始化
void LoginWindow::init()
{
    ip = "localhost";
    port = 7777;
    socket = new QTcpSocket(this);
    loginSet = new LoginSetDialog(this);

    setWindowTitle(QStringLiteral("登录"));
    ui->comboBox_acc->lineEdit()->setPlaceholderText(QStringLiteral("用户名"));
    ui->lineEdit_pass->setPlaceholderText(QStringLiteral("密码"));
    ui->lineEdit_vertify->setPlaceholderText(QStringLiteral("验证码"));

    // 设置combobox
    name_list = new QListWidget(this);
    ui->comboBox_acc->setModel(name_list->model());
    ui->comboBox_acc->setView(name_list);

    QStringList historyNames = getNames();
    for (int i = 0; i < historyNames.size(); ++i) {
        UserItemWidget *item = new UserItemWidget(this);
        item->setInfo(i, historyNames.at(i));
        connect(item, SIGNAL(showName(int, QString)), this, SLOT(onShowName(int, QString)));
        connect(item, SIGNAL(removeName(int, QString)), this, SLOT(onRemoveName(int, QString)));
        QListWidgetItem *list_item = new QListWidgetItem(name_list);
        name_list->setItemWidget(list_item, item);
    }

    // 添加验证码控件
    verLabel = new VertificationLabel(this);
    verLabel->setGeometry(220, 185, 70, 24);

    // 添加背景图片
    QLabel *label = new QLabel(this);
    QImage img;
    img.load("head.png");
    label->setPixmap(QPixmap::fromImage(img.scaled(400, 100, Qt::KeepAspectRatio)));
    label->move(0, 0);
    label->setGeometry(0, 0, 400, 100);

    // 信号与槽的连接
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(loginSet, SIGNAL(sendAddr(QString,int)),
            this, SLOT(on_setAddr(QString,int)));
}

// 连接到服务器
void LoginWindow::connectToServer()
{
    socket->abort();
    socket->connectToHost(ip, port);
}

// 登录按钮槽函数
void LoginWindow::on_pushButton_login_clicked()
{
    QString name = ui->comboBox_acc->currentText();
    QString passwd = ui->lineEdit_pass->text();
    QString vertify = ui->lineEdit_vertify->text();
    // 判断是否有未填项
    if ("" == name) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入用户名"), QMessageBox::Ok);
        return;
    } else if ("" == passwd) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入密码"), QMessageBox::Ok);
        return;
    } else if ("" == vertify) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入验证码"), QMessageBox::Ok);
        return;
    }
    // 检查验证码是否正确
    if (vertify != verLabel->getVerCode()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("验证码错误"), QMessageBox::Ok);
        return;
    }
    // 加密数据并发送至服务器
    QByteArray cryptPass = QCryptographicHash::hash(passwd.toLocal8Bit(),
                                                    QCryptographicHash::Md5);
    qDebug() << cryptPass.toHex().toUpper();
    QByteArray data;
    data.append(name);
    data.append('#');
    data.append(cryptPass);
    data.append('$');

    connectToServer();
    socket->waitForConnected();
    socket->write(data);
}

// 显示错误
void LoginWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug() << socket->errorString();
    QMessageBox::information(this, QStringLiteral("连接错误"),
                             socket->errorString(), QMessageBox::Yes);
}

// 读取返回数据
void LoginWindow::readMsg()
{
    QString data = socket->readAll();
    qDebug() << "返回值：" << data;

    // 登录失败
    if ("1" == data) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("用户名不存在"), QMessageBox::Yes);
        return;
    }
    if ("2" == data) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("密码错误"), QMessageBox::Yes);
        return;
    }

    // 登录成功
    if ("0" == data) {
        qDebug() << QStringLiteral("登录成功！");
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("登录成功"), QMessageBox::Yes);
        // 保存历史用户名
        if (ui->checkBox_rem->isChecked()) {
            QStringList list = getNames();
            if (!list.contains(ui->comboBox_acc->currentText())) {
                saveName(ui->comboBox_acc->currentText());
            }
        }
        emit loginOk(ip, port);
    }
}

// 保存用户名
void LoginWindow::saveName(const QString &name)
{
    QFile file("savednames.xml");
    QDomDocument doc;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    }
    doc.setContent(&file);
    file.close();

    // 检查文件内容是否为空
    QDomElement root = doc.documentElement();
    if (root.isNull()) {
        QDomProcessingInstruction ins;
        ins = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
        doc.appendChild(ins);

        root = doc.createElement(QStringLiteral("历史记录"));
        doc.appendChild(root);
    }

    // 向DOM中添加一个元素
    QDomElement e = doc.createElement(name);
    root.appendChild(e);

    // 写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

// 获取历史用户名
QStringList LoginWindow::getNames()
{
    QStringList list;
    QFile file("savednames.xml");
    QDomDocument doc;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return list;
    }
    if (!doc.setContent(&file)) {
        return list;
    }
    file.close();

    // 读取XML信息
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement item = node.toElement();
            list.append(item.tagName());
        }
        node = node.nextSibling();
    }
    return list;
}

// 删除已保存的历史用户名
void LoginWindow::delName(const QString &name)
{
    QFile file("savednames.xml");
    QDomDocument doc;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    if (!doc.setContent(&file)) {
        return;
    }
    file.close();

    // 移除用户名
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement e = node.toElement();
            if (e.tagName() == name) {
                root.removeChild(node);
                break;
            }
        }
        node = node.nextSibling();
    }

    // 写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

// 显示选中的用户名槽函数
void LoginWindow::onShowName(int /*index*/, QString name)
{
    ui->comboBox_acc->setEditText(name);
    ui->comboBox_acc->hidePopup();
}

// 删除用户名槽函数
void LoginWindow::onRemoveName(int index, QString name)
{
    delName(name);
    ui->comboBox_acc->removeItem(index);
    ui->comboBox_acc->hidePopup();
}

// 设置连接地址
void LoginWindow::on_setAddr(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
}

// 设置按钮槽函数
void LoginWindow::on_pushButton_set_clicked()
{
    loginSet->show();
}
