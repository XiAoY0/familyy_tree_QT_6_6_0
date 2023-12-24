#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //默认先跳转到dialog即登录界面
    Dialog w;
    w.show();


    //主界面显示 由 dialog登录界面跳转

    return a.exec();
}
