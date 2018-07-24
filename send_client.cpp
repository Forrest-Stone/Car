#include "send_client.h"
#include "ui_send_client.h"
#include "send_filedialog.h"
#include "send_controller.h"
#include <QString>
#include <QStringList>
#include <QDebug>


Send_Client::Send_Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Send_Client)
{
    ui->setupUi(this);
}

Send_Client::~Send_Client()
{
    delete ui;
}

void Send_Client::on_choose_picture_pushButton_clicked()
{
    qDebug()<<Send_Choose_Pictures();
}


void Send_Client::on_delete_pushButton_clicked()
{
    //取消发送图片

}

void Send_Client::on_reset_pushButton_clicked()
{
    //清空
}

void Send_Client::on_login_out_pushButton_clicked()
{
    //登出
}

void Send_Client::on_send_picture_pushButton_clicked()
{
    //发送图片
    controller.Send_Pictures();
}

QStringList Send_Client::Send_Choose_Pictures()
{
    Send_FileDialog dialog;
    QStringList pictures;
    if(dialog.exec()){
        pictures=dialog.selectedFiles();
    }
    return pictures;
}

