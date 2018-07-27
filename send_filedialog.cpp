#include "send_filedialog.h"

Send_FileDialog::Send_FileDialog(QWidget * parent):
    QFileDialog(parent)
{
    setWindowTitle("选择要上传的图片");
    setDirectory("F:");
    setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
    setFileMode(QFileDialog::ExistingFiles);
    setViewMode(QFileDialog::Detail);

}
