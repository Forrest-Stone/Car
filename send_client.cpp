#include "send_client.h"
#include "ui_send_client.h"
#include "send_filedialog.h"
#include "send_controller.h"
#include "send_list_item.h"
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QHostAddress>


Send_Client::Send_Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Send_Client)
{
    ui->setupUi(this);
    ui->listWidget->setIconSize(QSize(200,200));
    socket=new Send_Socket(this);
    ui->local_address_lineEdit->setText(QHostAddress(QHostAddress::LocalHost).toString());
    connect(socket,SIGNAL(Send_state(QString)),this,SLOT(connect_state_change(QString)));
}

Send_Client::~Send_Client()
{
    delete ui;
}

void Send_Client::on_choose_picture_pushButton_clicked()
{
    if(Send_Choose_Pictures()){
        foreach (QString picture, pictures) {
            ui->listWidget->addItem(Send_Controller::Send_Create_Item(picture));
        }
    }
}


void Send_Client::on_delete_pushButton_clicked()
{
    //取消发送图片
    int Row=ui->listWidget->currentRow();
    QStringList::iterator iter=pictures.begin();
    for(int i=0;i<Row;++i){
        ++iter;
    }
    pictures.erase(iter);
    ui->listWidget->takeItem(Row);
}

void Send_Client::on_reset_pushButton_clicked()
{
    //清空
}

void Send_Client::on_login_out_pushButton_clicked()
{
    //登出
    socket->Send_Disconnect();
    this->close();
}

void Send_Client::on_send_picture_pushButton_clicked()
{
    //发送图片
    //Send_Controller::Send_Pictures(pictures);
    //Send_Controller::Send_Pictures(pictures);
    //socket->connectToHost("192.168.0.1",8080);

    //socket->Send_Connect("10.25.19.190",8888 );
    //连接到服务器ip，端口
    if(ui->state_label!="connected"){
        socket->Send_Connect("127.0.0.1",8888 );
    }
    //发送图片
    socket->Send_Write(pictures);

}

void Send_Client::connect_state_change(const QString &state)
{
    ui->state_label->setText(state);
}

bool Send_Client::Send_Choose_Pictures()
{
    Send_FileDialog dialog;
    if(dialog.exec()){
        pictures=dialog.selectedFiles();
    }
    return true;
}

