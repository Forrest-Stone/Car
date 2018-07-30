#include "loginsetdialog.h"
#include "ui_loginsetdialog.h"
#include <QString>

LoginSetDialog::LoginSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginSetDialog)
{
    ui->setupUi(this);
}

LoginSetDialog::~LoginSetDialog()
{
    delete ui;
}

// 确认
void LoginSetDialog::on_buttonBox_accepted()
{
    QString ip = ui->lineEdit_ip->text();
    int port = ui->lineEdit_port->text().toInt();
    emit sendAddr(ip, port);
    close();
}

// 取消
void LoginSetDialog::on_buttonBox_rejected()
{
    close();
}
