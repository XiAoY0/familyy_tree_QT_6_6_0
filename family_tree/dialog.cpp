#include "dialog.h"
#include "ui_dialog.h"
#include<QPushButton>
#include "mainexe.h"
#include "ui_mainexe.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登入");
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnLogin_clicked()
{
    //只有当账号为ADMIN密码为123456 可以登录
//    本程序账号密码写死 但实际上的登陆验证 需要以下几个步骤 ： 输入的账号密码发送到腾讯的服务器 ->  腾讯服务器校验通过->  登录
//        可以使用数据库完成账号密码的注册和读取   暂时不理
    //使登录跳转
    if(ui->txtUserName->text()==tr("ADMIN")&&ui->txtPassword->text()==tr("123456")){
        //accept();
        //Dialog::~Dialog();//登录界面退出

        this->hide();

        //进入程序主界面
        mainexe *w=new mainexe() ;
        w->show();
    }
    //否则进入下一轮验证
    else{
        //检验用户名和密码是否为空
        if(ui->txtUserName->text().isEmpty()){ QMessageBox::warning(this,tr("warning"),tr("userName is Empty!"),QMessageBox::Yes);}
        if(ui->txtPassword->text().isEmpty()){ QMessageBox::warning(this,tr("warning"),tr("passWord is Empty!"),QMessageBox::Yes);}
        else{
            //用户名密码错误 则输出warning信息
            QMessageBox::warning(this,tr("warning"),tr("userName or passWord Error"),QMessageBox::Yes);}
    }
}


void Dialog::on_btnClose_clicked()
{
//退出 按钮被按下 执行dialog的析构函数 退出窗口
   // Dialog::~Dialog();
    this->close();
}

//按下显示密码  不按下显示密文
void Dialog::on_checkBox_clicked(bool checked)
{
    if(checked){
        ui->txtPassword->setEchoMode(QLineEdit::Normal);
    }
    else{
    ui->txtPassword->setEchoMode(QLineEdit::Password);
    }
}

