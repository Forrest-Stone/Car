#ifndef VERTIFICATIONLABEL_H
#define VERTIFICATIONLABEL_H

/*
 * 登录验证码控件
 * */

#include <QLabel>


class VertificationLabel : public QLabel
{
    Q_OBJECT

public:
    VertificationLabel(QWidget *parent = 0);
    ~VertificationLabel();
    QString getVerCode() const;              // 获取验证码字符串

signals:
    void click();                            // 发送点击信号

public slots:
    void onClick();                          // 点击动作槽函数

protected:
    void paintEvent(QPaintEvent *event);    // 重写绘制函数
    void mousePressEvent(QMouseEvent *event);   // 重写鼠标点击事件函数

private:
    void produceVer() const;                // 生成验证码
    QChar produceLetter() const;            // 生成随机字符
    void produceColor() const;              // 生成随机颜色

    const int letter_num = 4;               // 字符数
    int noise_num;                          // 噪点数

    QChar *verCodeArray;                    // 存放字符的数组
    QColor *colorArray;                     // 存放颜色的数组

    enum {                                   // 生成数字或大写或小写字母
        NUMBER = 0,
        UPPER,
        LOWER
    };
};

#endif // VERTIFICATIONLABEL_H
