#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include "loginwindow.h"

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    LoginWindow login;
    login.show();

    return a.exec();
}
