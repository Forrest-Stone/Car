#ifndef LOGINSETDIALOG_H
#define LOGINSETDIALOG_H

#include <QDialog>

namespace Ui {
class LoginSetDialog;
}

class LoginSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginSetDialog(QWidget *parent = 0);
    ~LoginSetDialog();

signals:
    void sendAddr(QString ip, int port);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LoginSetDialog *ui;
};

#endif // LOGINSETDIALOG_H
