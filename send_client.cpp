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
    ui->local_address_lineEdit->setText(Send_Controller::Send_Get_IP());
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
    QString number=QString::number(pictures.count())+" pictures";
    ui->number_label->setText(number);
}


void Send_Client::on_delete_pushButton_clicked()
{
    //取消发送图片
    int Row=ui->listWidget->currentRow();
    if(Row!=-1){
        QStringList::iterator iter=pictures.begin();
        for(int i=0;i<Row;++i){
            ++iter;
        }
        pictures.erase(iter);
        ui->listWidget->takeItem(Row);
    }
}

void Send_Client::on_reset_pushButton_clicked()
{
    //清空
    pictures.clear();
    ui->listWidget->clear();
}

void Send_Client::on_login_out_pushButton_clicked()
{
    //登出
    socket->Send_Disconnect();
    on_reset_pushButton_clicked();
    emit Send_login_out();
    this->close();
}

void Send_Client::on_send_picture_pushButton_clicked()
{

    if(ui->state_label->text()=="connected"){
        //发送图片        
        socket->Send_Write(pictures);
        qDebug()<<"client success";
        on_reset_pushButton_clicked();
    }
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


void Send_Client::on_pushButton_clicked()
{
    //连接到服务器ip，端口
    if(ui->net_address_lineEdit->text()!="")
    {
        if(ui->state_label->text()!="connected"){
            socket->Send_Connect(ui->net_address_lineEdit->text(),ui->net_port_lineEdit->text().toInt());
        }
    }
}

void Send_Client::Login_in(const QString& ip,const int port)
{
    show();
    ui->net_address_lineEdit->setText(ip);
    ui->net_port_lineEdit->setText(QString::number(port));
}
