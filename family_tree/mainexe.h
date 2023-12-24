#ifndef MAINEXE_H
#define MAINEXE_H
#include <tree.h>
#include <QWidget>

namespace Ui {
class mainexe;
}

class mainexe : public QWidget
{
    Q_OBJECT

public:
    explicit mainexe(QWidget *parent = nullptr);
    ~mainexe();

private slots:
    void on_pushButton_clicked();//查询第n代人信息

    void on_pushButton_5_clicked();//退出按钮

    void on_pushButton_9_clicked();//返回按钮

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::mainexe *ui;
//    login* login1 = new login();
    treenode* root1 = new treenode;
    string filepath = "../login/Treedata.txt";//文件导入初始的家族成员信息
};

#endif // MAINEXE_H
