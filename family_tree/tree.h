#ifndef TREE_H
#define TREE_H

#include <QWidget>
#include <iostream>//会和QTextStream冲突  不用std全局的命名空间  而是用::在局部使用
#include <QInputDialog>//输入对话框  用来弹出提示信息窗口
#include <string>//C++字符串相关操作
#include <fstream>//文件流 用来操作文件

#include <sstream>// <sstream> 定义了三个类：istringstream、ostringstream 和 stringstream，分别用来进行流的输入、输出和输入输出操作
//同时可以用来进行类型转换

#include <map>//提供一对一的hash  使用哈希表 自动建立key － value的对应
#include <QString>//qt 中字符串相关函数
#include <QTextStream>//QTextStream 可以逐行读取 方便处理数据
#include <QDebug>//qt里的输入输出

using namespace std;//如果不加这一句  使用string 时会报错


//定义日期的结构体 主要用于家族成员 出生日期和死亡日期的存储
typedef struct {
    int year;
    int month;
    int day;
}Date;

//家族成员信息
typedef struct {
    string name;		//名字
    Date birthday;		//出生日期
    string IsMarried;	//是否已婚
    string address;		//地址
    string IsAlive;		//是否在世
    Date deathday;		//死亡日期
    string remarks;		//备注
}PersonMessage;

//定义一个节点
typedef struct treenode {
    PersonMessage personMessage;
    treenode* leftchild;		//左孩子
    treenode* rightbrother;		//右兄弟
    treenode* parent;			//父节点
    int depth;					//代数
}treenode;


//声明自定义数据类型
//Qt中，负责自定义类型的类是QMetaType ，为了让这个类识别自定义的数据类型，需要在定义Message类的头文件中使用Q_DECLARE_METATYPE()宏声明。
Q_DECLARE_METATYPE(Date)
Q_DECLARE_METATYPE(PersonMessage)
Q_DECLARE_METATYPE(treenode)
Q_DECLARE_METATYPE(treenode*)

//读入数据 添加节点
//把node结点加入根节点
void addNode(treenode*& , treenode*,treenode* );

// 从字符串流中读入日期数据
void parseDate(stringstream& , Date&);

// 传入 txt 文档中的一行数据，最后以一个成员节点返回  返回值是成员节点
treenode* parseLine(string&);

// 读取文件，并建立一颗树
treenode* buildTree(string filename);

//暂时没遇到
void CreateGengalogyFile(treenode*&,fstream&,int );

//设置父节点
void SetParent(treenode*& , treenode*&);

//打印家谱所有成员信息
QString PrintAllMessage(treenode*);

//打印家谱某成员信息
QString PrintMessage(treenode* );

//打印某层成员信息
QString PrintDepthMessage(treenode* , int );

//查找某姓名的信息
QString SearchName(treenode* , string,bool&);

//按姓名输出成员信息
QString PrintMessageByName(treenode*,string);

//查找某日期的信息
QString SearchBirthday(treenode*, Date,bool&);

//按出生日期输出成员信息
QString PrintMessageByBirthday(treenode*,Date);

// 在家谱树中，寻找一个指定的人名，并返回其指针
treenode* findPersonByName(treenode*, string);

//先序遍历 遍历整棵树 直到 找到目标节点 主要用于后面几个函数的实现
void ReturnTreenodeByName(treenode*&, string,treenode*&);

//判断两人关系
QString JudgeRelationship(treenode*,QString,QString);

//按照姓名返回根节点 在函数里实现一个遍历
void ReturnTreenodeByNameAndBirthday(treenode*&, string, treenode*&);

//插入一个孩子
QString InsertChild(treenode*&,string,PersonMessage);

//删除节点 暂未实现
void DeleteMember(treenode*&);

//修改某成员信息  前提是某一成员要先存在
QString ModifyMember(treenode*&,string,PersonMessage);

//保存文件
void SaveFile(treenode*, fstream&);

//自写文件保存代码块
void writeDate(ofstream& fout, const Date& date);
void writePerson(ofstream& fout, const PersonMessage& person);
void saveTree(treenode* node, ofstream& fout);
QString saveTreeToFile(string filename, treenode* root);



class tree
{
public:
    tree();
};

#endif // TREE_H
