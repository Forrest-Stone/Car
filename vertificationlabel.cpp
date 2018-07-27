#include "vertificationlabel.h"
#include <QTime>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

VertificationLabel::VertificationLabel(QWidget *parent) :
    QLabel(parent)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    verCodeArray = new QChar[letter_num];
    colorArray = new QColor[letter_num];
    noise_num = this->width();
    connect(this, SIGNAL(click()), this, SLOT(onClick()));
}

VertificationLabel::~VertificationLabel()
{
    delete[] verCodeArray;
    delete[] colorArray;
}

// 重写绘制函数
void VertificationLabel::paintEvent(QPaintEvent *event)
{
    //qDebug() << event->type();
    QPainter painter(this);
    QPoint point;
    painter.fillRect(this->rect(), Qt::white);
    produceVer();
    produceColor();
    // 绘制验证码
    for (int i = 0; i < letter_num; ++i) {
        point.setX(i * (this->width() / letter_num) + this->width() / 8);
        point.setY(this->height() / 2);
        painter.setPen(colorArray[i]);
        painter.drawText(point, QString(verCodeArray[i]));
    }
    // 绘制噪点
    for (int i = 0; i < noise_num; ++i) {
        point.setX(qrand() % this->width());
        point.setY(qrand() % this->height());
        painter.setPen(colorArray[i % letter_num]);
        painter.drawPoint(point);
    }
}

// 重写点击事件
void VertificationLabel::mousePressEvent(QMouseEvent *)
{
    emit click();
}

// 生成验证码
void VertificationLabel::produceVer() const
{
    for (int i = 0; i < letter_num; ++i) {
        verCodeArray[i] = produceLetter();
    }
}

// 生成随机字符
QChar VertificationLabel::produceLetter() const
{
    QChar c;
    int flag = qrand() % 3;
    switch (flag) {
    case NUMBER: c = '0' + qrand() % 10; break;
    case UPPER: c = 'A' + qrand() % 26; break;
    case LOWER: c = 'a' + qrand() % 26; break;
    }
    return c;
}

// 生成随机颜色
void VertificationLabel::produceColor() const
{
    for (int i = 0; i < letter_num; ++i) {
        colorArray[i] = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    }
    return;
}

// 获取验证码字符串
QString VertificationLabel::getVerCode() const
{
    QString ver;
    for (int i = 0; i < letter_num; ++i) {
        ver += verCodeArray[i];
    }
    return ver;
}

// 点击槽函数
void VertificationLabel::onClick()
{
    repaint();
}
