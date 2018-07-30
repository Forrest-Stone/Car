#include "useritemwidget.h"
#include "ui_useritemwidget.h"
#include <QHBoxLayout>

UserItemWidget::UserItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItemWidget)
{
    ui->setupUi(this);
    m_mousePress = false;
    m_label_name = new QLabel(this);
    m_toolBtn_del = new QToolButton(this);
    m_toolBtn_del->setText("X");
    m_toolBtn_del->setStyleSheet("background-color: transparent");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_label_name);
    layout->addStretch();
    layout->addWidget(m_toolBtn_del);
    layout->setContentsMargins(5, 5, 5, 5);

    connect(m_toolBtn_del, SIGNAL(clicked(bool)), this, SLOT(onRemoveBtn()));
}

UserItemWidget::~UserItemWidget()
{
    delete ui;
}

void UserItemWidget::setInfo(int index, QString name)
{
    m_index = index;
    m_label_name->setText(name);
}

QString UserItemWidget::getName()
{
    return m_label_name->text();
}

void UserItemWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePress = true;
    }
}

void UserItemWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (m_mousePress) {
        emit showName(m_index, m_label_name->text());
        m_mousePress = false;
    }
}

void UserItemWidget::onRemoveBtn()
{
    emit removeName(m_index, m_label_name->text());
}
