#ifndef USERITEMWIDGET_H
#define USERITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QString>
#include <QMouseEvent>

namespace Ui {
class UserItemWidget;
}

class UserItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserItemWidget(QWidget *parent = 0);
    ~UserItemWidget();
    void setInfo(int index, QString name);      // 设置信息
    QString getName();                          // 获取用户名

signals:
    void removeName(int index, QString name);                 // 删除用户名信号
    void showName(int index, QString name);     // 显示用户名信号

private slots:
    void onRemoveBtn();                         // 删除按钮槽函数

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::UserItemWidget *ui;
    bool m_mousePress;
    int m_index;
    QLabel *m_label_name;
    QToolButton *m_toolBtn_del;
};

#endif // USERITEMWIDGET_H
