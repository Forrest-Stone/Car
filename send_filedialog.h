#ifndef SEND_FILEDIALOG_H
#define SEND_FILEDIALOG_H

#include<QFileDialog>

class Send_FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    explicit Send_FileDialog(QWidget* parent=0);
};

#endif // SEND_FILEDIALOG_H
