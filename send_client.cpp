#include "send_client.h"
#include "ui_send_client.h"
#include <QFileDialog>
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
    //QList<QUrl> files=QFileDialog::getOpenFileUrls(this,"choose","E:","*");
    QFileDialog dialog;
    dialog.setWindowTitle("选择要上传的图片");
    dialog.setDirectory("E:");
    dialog.setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList files;
    if(dialog.exec()){
        files=dialog.selectedFiles();
    }
    qDebug()<<files;
}
