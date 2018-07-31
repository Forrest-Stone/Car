#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "vertificationlabel.h"
#include "useritemwidget.h"
#include "loginsetdialog.h"
#include "loginsocketmanage.h"
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

#define QL QStringLiteral

// 显示提示信息
#define SHOW(a, b) \
QMessageBox::information( \
    this, \
    (a), \
    (b), \
    QMessageBox::Yes \
)


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    init();
}

LoginWindow::~LoginWindow()
{
    m_socketManage->closeSocket();
    delete m_socketManage;
    delete ui;
}

// 初始化
void LoginWindow::init()
{
    m_socketManage = new LoginSocketManage();
    m_loginSet = new LoginSetDialog(this);

    setWindowTitle(QL("登录"));
    ui->comboBox_acc->lineEdit()->setPlaceholderText(QL("用户名"));
    ui->lineEdit_pass->setPlaceholderText(QL("密码"));
    ui->lineEdit_vertify->setPlaceholderText(QL("验证码"));
    ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    ui->label->hide();

    // 设置combobox
    m_nameList = new QListWidget(this);
    ui->comboBox_acc->setModel(m_nameList->model());
    ui->comboBox_acc->setView(m_nameList);

    QStringList historyNames = getNames();
    for (int i = 0; i < historyNames.size(); ++i) {
        UserItemWidget *item = new UserItemWidget(this);
        item->setInfo(i, historyNames.at(i));
        connect(item, SIGNAL(showName(int, QString)), this, SLOT(onShowName(int, QString)));
        connect(item, SIGNAL(removeName(int, QString)), this, SLOT(onRemoveName(int, QString)));
        QListWidgetItem *list_item = new QListWidgetItem(m_nameList);
        m_nameList->setItemWidget(list_item, item);
    }

    // 添加验证码控件
    m_verLabel = new VertificationLabel(this);
    m_verLabel->setGeometry(220, 185, 70, 24);

    // 添加背景图片
    QLabel *label = new QLabel(this);
    QImage img;
    img.load(":/img/head.png");
    label->setPixmap(QPixmap::fromImage(img.scaled(400, 100, Qt::KeepAspectRatio)));
    label->move(0, 0);
    label->setGeometry(0, 0, 400, 100);

    // 信号与槽的连接
    connect(m_loginSet, SIGNAL(sendAddr(QString,int)),
            this, SLOT(on_setAddr(QString,int)));
    connect(m_socketManage, SIGNAL(error(QString)),
            this, SLOT(displayError(QString)));
    connect(m_socketManage, SIGNAL(loginResult(LoginSocketManage::Result)),
            this, SLOT(onLoginResult(LoginSocketManage::Result)));
}

// 显示错误信息
void LoginWindow::displayError(QString error)
{
    m_socketManage->closeSocket();
    SHOW(QL("错误"), error);
    ui->label->hide();
}

// 登录按钮槽函数
void LoginWindow::on_pushButton_login_clicked()
{
    QString name = ui->comboBox_acc->currentText();
    QString passwd = ui->lineEdit_pass->text();
    QString vertify = ui->lineEdit_vertify->text();
    QString verCode = m_verLabel->getVerCode();

    // 判断是否有未填项
    if ("" == name) {
        SHOW(QL("提示"), QL("请输入用户名"));
        return;
    } else if ("" == passwd) {
        SHOW(QL("提示"), QL("请输入密码"));
        return;
    } else if ("" == vertify) {
        SHOW(QL("提示"), QL("请输入验证码"));
        return;
    }

    // 检查验证码是否正确
    if (vertify != verCode.toUpper() && vertify != verCode.toLower()) {
        SHOW(QL("提示"), QL("验证码错误"));
        return;
    }

    // 对密码进行加密
    QByteArray cryptPass(QCryptographicHash::hash(passwd.toLocal8Bit(), QCryptographicHash::Md5));
    qDebug() << cryptPass.toHex().toUpper();

    // 连接至服务器
    m_socketManage->setOperation(LoginSocketManage::LOGIN);
    m_socketManage->setUserInfo(name, cryptPass);
    m_socketManage->connectToServer();
    ui->label->show();
}

// 根据登录结果进行相应操作
void LoginWindow::onLoginResult(LoginSocketManage::Result res)
{
    ui->label->hide();
    switch (res) {
    // 登录成功
    case LoginSocketManage::SUCCESSFUL:
    {
        QString name(ui->comboBox_acc->currentText());
        if (ui->checkBox_rem->isChecked()) {
            QStringList list = getNames();
            if (!list.contains(name)) {
                saveName(name);
            }
        }
        emit loginOk(m_socketManage->getIP(), m_socketManage->getPort());
        break;
    }
    // 用户名不存在
    case LoginSocketManage::NOUSERNAME:
        SHOW(QL("提示"), QL("用户名不存在！"));
        break;
    // 密码错误
    case LoginSocketManage::INVALIDPASSWD:
        SHOW(QL("提示"), QL("密码错误！"));
        break;
    default:
        break;
    }
    m_socketManage->closeSocket();
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

        root = doc.createElement(QL("历史记录"));
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
    m_socketManage->setAddr(ip, port);
}

// 设置按钮槽函数
void LoginWindow::on_pushButton_set_clicked()
{
    m_loginSet->show();
}

// 登出
void LoginWindow::loginOut()
{
    m_socketManage->setOperation(LoginSocketManage::LOGOUT);
    m_socketManage->connectToServer();
}

// 显示密码
void LoginWindow::on_checkBox_show_pass_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->lineEdit_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    }
}

