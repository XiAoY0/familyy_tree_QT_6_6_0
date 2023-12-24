#include "mainexe.h"
#include "tree.h"
#include "ui_mainexe.h"
#include <QInputDialog>
#include <string>
#include<QVBoxLayout>
#include <dialog.h>
mainexe::mainexe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainexe)
{
    ui->setupUi(this);
    this->setWindowTitle("家谱管理系统");
    root1 = buildTree(filepath);
    //ui->label_bgp->setScaledContents(true);
    QPixmap pic("../OurFamilyTree/bgp3");
    //ui->label_bgp->setPixmap(pic);

    //输出读入的家谱信息
    QString qstr = PrintAllMessage(root1);
    this->ui->textEdit->setText(qstr);

}

mainexe::~mainexe()
{
    delete ui;
}

void mainexe::on_pushButton_clicked()//查询第n代人信息
{
    //弹出内容输入框  这里用到的是QInputDialog类  （输入对话框）
    //单文本输入框
    //QString getText(QWidget *parent, const QString &title, const QString &label, QLineEdit::EchoMode mode = QLineEdit::Normal, const QString &text = QString(), bool *ok = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)

    //通过此函数实现读入用户输入的字符串
    QString inputVal = QInputDialog::getText(this,tr("查询第n代信息"),tr("N="));

    // 获取n的值 用到的toint函数把字符串转化为整形
    int gen = inputVal.toInt();
    QString qstr = PrintDepthMessage(root1,gen);
    this->ui->textEdit->setText(qstr);

}


void mainexe::on_pushButton_5_clicked()//退出按钮被按下
{
    saveTreeToFile(filepath,root1);
    exit(0);
}


void mainexe::on_pushButton_9_clicked()//返回按钮被按下，本窗口隐藏，登陆界面显示
{
    Dialog* login=new Dialog();
    login->show();
    this->hide();
}


void mainexe::on_pushButton_2_clicked()//按照姓名 查询人员信息
{

    // 弹出内容输入框
    QString inputName = QInputDialog::getText(this, tr("按照姓名查询成员信息"), tr("请输入要查询成员的姓名:"));
    std::string name = inputName.toStdString();
    QString qstr = PrintMessageByName(root1,name);
    this->ui->textEdit->setText(qstr);
}

//按照出生日期查询成员信息
void mainexe::on_pushButton_3_clicked()
{
    QDialog dialog;
    QLabel yearLabel("年:");
    QLineEdit yearLineEdit;
    QLabel monthLabel("月:");
    QLineEdit monthLineEdit;
    QLabel dayLabel("日:");
    QLineEdit dayLineEdit;

    // 创建一个 QPushButton 对象
    QPushButton okButton("OK");

    // 连接 QPushButton 的 clicked 信号到 QDialog 的 accept 槽函数
    QObject::connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // 创建一个 QVBoxLayout 对象并添加 QLabel 和 QLineEdit 对象  qt垂直布局
    QVBoxLayout layout;
    layout.addWidget(&yearLabel);
    layout.addWidget(&yearLineEdit);
    layout.addWidget(&monthLabel);
    layout.addWidget(&monthLineEdit);
    layout.addWidget(&dayLabel);
    layout.addWidget(&dayLineEdit);
    layout.addWidget(&okButton);

    // 设置 QDialog 的布局
    dialog.setLayout(&layout);
    // 显示 QDialog 对象
    dialog.exec();
    Date date;
    date.year = yearLineEdit.text().toInt();
    date.month = monthLineEdit.text().toInt();
    date.day = dayLineEdit.text().toInt();



    QString qstr = PrintMessageByBirthday(root1,date);

    this->ui->textEdit->setText(qstr);
}

//查询两人关系
void mainexe::on_pushButton_4_clicked()
{
    QDialog dialog;
    QLabel member1Label("成员1:");
    QLineEdit member1LineEdit;
    QLabel member2Label("成员2:");
    QLineEdit member2LineEdit;

    // 创建一个 QPushButton 对象
    QPushButton okButton("OK");

    // 连接 QPushButton 的 clicked 信号到 QDialog 的 accept 槽函数
    QObject::connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // 创建一个 QVBoxLayout 对象并添加 QLabel 和 QLineEdit 对象
    QVBoxLayout layout;
    layout.addWidget(&member1Label);
    layout.addWidget(&member1LineEdit);
    layout.addWidget(&member2Label);
    layout.addWidget(&member2LineEdit);
    layout.addWidget(&okButton);

    // 设置 QDialog 的布局
    dialog.setLayout(&layout);
    // 显示 QDialog 对象
    dialog.exec();

    QString member1 = member1LineEdit.text();
    QString member2 = member2LineEdit.text();
    QString qstr1 = JudgeRelationship(root1,member1,member2);
    this->ui->textEdit->setText(qstr1);
}


//为某成员添加孩子
void mainexe::on_pushButton_6_clicked()
{
    QDialog dialog;
    QLabel fatherLabel("请输入孩子父亲的名字:");
    QLineEdit fatherLineEdit;

    QLabel nameLabel("孩子的名字:");
    QLineEdit nameLineEdit;
    QLabel yearLabel("孩子出生那年:");
    QLineEdit yearLineEdit;
    QLabel monthLabel("孩子出生那月:");
    QLineEdit monthLineEdit;
    QLabel dayLabel("孩子出生那日:");
    QLineEdit dayLineEdit;
    QLabel MarriedLabel("请输入婚姻状况，已婚输入0，未婚输入1:");
    QLineEdit MarriedLineEdit;
    QLabel addressLabel("住址:");
    QLineEdit addressLineEdit;
    QLabel remarksLabel("备注:");
    QLineEdit remarksLineEdit;


    // 创建一个 QPushButton 对象
    QPushButton okButton("OK");

    // 连接 QPushButton 的 clicked 信号到 QDialog 的 accept 槽函数
    QObject::connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // 创建一个 QVBoxLayout 对象并添加 QLabel 和 QLineEdit 对象
    QVBoxLayout layout;
    layout.addWidget(&fatherLabel);
    layout.addWidget(&fatherLineEdit);
    layout.addWidget(&nameLabel);
    layout.addWidget(&nameLineEdit);
    layout.addWidget(&yearLabel);
    layout.addWidget(&yearLineEdit);
    layout.addWidget(&monthLabel);
    layout.addWidget(&monthLineEdit);
    layout.addWidget(&dayLabel);
    layout.addWidget(&dayLineEdit);
    layout.addWidget(&MarriedLabel);
    layout.addWidget(&MarriedLineEdit);
    layout.addWidget(&addressLabel);
    layout.addWidget(&addressLineEdit);
    layout.addWidget(&remarksLabel);
    layout.addWidget(&remarksLineEdit);
    layout.addWidget(&okButton);

    // 设置 QDialog 的布局
    dialog.setLayout(&layout);
    // 显示 QDialog 对象
    dialog.exec();

    string father = fatherLineEdit.text().toStdString();

    PersonMessage person;
    person.name = nameLineEdit.text().toStdString();
    person.birthday.year = yearLineEdit.text().toInt();
    person.birthday.month = monthLineEdit.text().toInt();
    person.birthday.day = dayLineEdit.text().toInt();
    person.IsMarried = MarriedLineEdit.text().toStdString();
    person.address = addressLineEdit.text().toStdString();
    person.remarks = addressLineEdit.text().toStdString();
    person.IsAlive = "在世";

    QString qstr = InsertChild(root1,father,person);

    this->ui->textEdit->setText(qstr);
    saveTreeToFile(filepath,root1);
}

//修改成员信息
void mainexe::on_pushButton_7_clicked()
{
    QDialog dialog;
    QLabel memberLabel("请输入需要修改信息成员的名字:");
    QLineEdit memberLineEdit;

    QLabel nameLabel("修改后的名字:");
    QLineEdit nameLineEdit;
    QLabel yearLabel("修改后出生年:");
    QLineEdit yearLineEdit;
    QLabel monthLabel("修改后出生月:");
    QLineEdit monthLineEdit;
    QLabel dayLabel("修改后出生日:");
    QLineEdit dayLineEdit;
    QLabel MarriedLabel("请输入婚姻状况，已婚输入0，未婚输入1:");
    QLineEdit MarriedLineEdit;
    QLabel addressLabel("住址:");
    QLineEdit addressLineEdit;
    QLabel remarksLabel("备注:");
    QLineEdit remarksLineEdit;


    // 创建一个 QPushButton 对象
    QPushButton okButton("OK");

    // 连接 QPushButton 的 clicked 信号到 QDialog 的 accept 槽函数
    QObject::connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // 创建一个 QVBoxLayout 对象并添加 QLabel 和 QLineEdit 对象
    QVBoxLayout layout;
    layout.addWidget(&memberLabel);
    layout.addWidget(&memberLineEdit);
    layout.addWidget(&nameLabel);
    layout.addWidget(&nameLineEdit);
    layout.addWidget(&yearLabel);
    layout.addWidget(&yearLineEdit);
    layout.addWidget(&monthLabel);
    layout.addWidget(&monthLineEdit);
    layout.addWidget(&dayLabel);
    layout.addWidget(&dayLineEdit);
    layout.addWidget(&MarriedLabel);
    layout.addWidget(&MarriedLineEdit);
    layout.addWidget(&addressLabel);
    layout.addWidget(&addressLineEdit);
    layout.addWidget(&remarksLabel);
    layout.addWidget(&remarksLineEdit);
    layout.addWidget(&okButton);

    // 设置 QDialog 的布局
    dialog.setLayout(&layout);
    // 显示 QDialog 对象
    dialog.exec();

    string member = memberLineEdit.text().toStdString();

    PersonMessage person;
    person.name = nameLineEdit.text().toStdString();
    person.birthday.year = yearLineEdit.text().toInt();
    person.birthday.month = monthLineEdit.text().toInt();
    person.birthday.day = dayLineEdit.text().toInt();
    person.IsMarried = MarriedLineEdit.text().toStdString();
    person.address = addressLineEdit.text().toStdString();
    person.remarks = remarksLineEdit.text().toStdString();
    person.IsAlive = "在世";

    QString qstr = ModifyMember(root1,member,person);
    this->ui->textEdit->setText(qstr);
    saveTreeToFile(filepath,root1);
}


//输出所有成员信息
void mainexe::on_pushButton_8_clicked()
{
    QString qstr = PrintAllMessage(root1);
    this->ui->textEdit->setText(qstr);
}

