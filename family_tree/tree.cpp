#include "tree.h"
#include "mainexe.h"
tree::tree()
{

}


//读入数据 添加节点
//把node结点加入根节点
void addNode(treenode*& root, treenode* node,treenode* parent = NULL) {
    if (root == NULL) {
        root = node;
        node->parent = parent;
        return;
    }

    //递归遍历并添加成员  先左后右
    if (root->depth == node->depth - 1) {
        addNode(root->leftchild, node,root);
    } else {
        addNode(root->rightbrother, node,parent);
    }
}


// 从字符串流中读入日期数据
//.再看看fin和fout对象
//    fout对象的作用可以理解成：向文件中进行写操作 【从缓冲区–>硬盘】
//    fin对象的作用可以理解成：对文件中的内容进行读操作 【从硬盘–>缓冲区】
// fin和fout 是对文件的操作  将字符串流中的日期数据读入
void parseDate(stringstream& fin, Date& date) {
    fin >> date.year >> date.month >> date.day;
}


//<sstream> 定义了三个类：istringstream、ostringstream 和 stringstream，分别用来进行流的输入、输出和输入输出操作
// 传入 txt 文档中的一行数据，最后以一个成员节点返回  返回值是成员节点
treenode* parseLine(string& line) {
    stringstream ss(line);
    treenode* node = new treenode();

    ss >> node->depth >> node->personMessage.name;

    //parseDate 用来读入日期数据  在这里用作成员出生日期
    parseDate(ss, node->personMessage.birthday);

    ss >> node->personMessage.IsMarried >> node->personMessage.address >> node->personMessage.IsAlive;

    //parseDate 用来读入日期数据  在这里用作成员死亡日期
    parseDate(ss, node->personMessage.deathday);

    // 读取该行余下的部分 给 remarks
    getline(ss, node->personMessage.remarks);

    //这几个节点赋初值为0
    node->leftchild = node->rightbrother = node->parent = NULL;

    return node;
}

// 读取文件，并建立一颗树
treenode* buildTree(string filename) {

    //读取文件使用 ifstream
//    直接调用ifstream 类的构造函数
    ifstream fin(filename);

    //检查文件是否打开成功
    if (!fin) {
        qDebug() << "Could not open file\n";
        return NULL;
    }

    string line;

    //istream& getline (istream&  is, string& str);
    getline(fin, line);
    treenode* root = parseLine(line);

    //只要判断line里存储 不为空 就添加节点
    while (getline(fin, line)) {
        addNode(root, parseLine(line));
    }

    fin.close();
    return root;
}


//设置父节点
void SetParent(treenode*& root, treenode*& parent)
{
    root->parent = parent;
    if (root->leftchild != NULL)
    {
        SetParent(root->leftchild, root);
    }
    if (root->rightbrother != NULL)
    {
        SetParent(root->rightbrother, parent);
    }

}

//打印家谱所有成员信息 先左后右 先序遍历
QString PrintAllMessage(treenode* root)
{
    QString qstr = "";
    if (root != NULL)
    {
        qstr+= PrintMessage(root);
    }
    if (root->leftchild != NULL)
    {
        qstr+=PrintAllMessage(root->leftchild);
    }
    if (root->rightbrother != NULL)
    {
        qstr+= PrintAllMessage(root->rightbrother);
    }
    return qstr;
}

//打印家谱某成员信息
QString PrintMessage(treenode* target)
{
    QString qstr = "";
    //fromStdString用来实现string和qstring之间类型转换
//    std::string a("abc");
//    QString b = QString::fromStdString(a);
    qstr = QString::fromStdString("姓名:" + (target->personMessage.name) + "  "+"家谱中第" + to_string(target->depth)+"代人"+"  ");
    if (target->personMessage.IsMarried == "已婚")
    {
        qstr += QString::fromStdString("婚姻状况:已婚\n");
    }
    else if (target->personMessage.IsMarried == "未婚")
    {
        qstr += "婚姻状况: 未婚\n";
    }
    qstr += QString("出生日期: %1年%2月%3日\n").arg(target->personMessage.birthday.year).arg(target->personMessage.birthday.month).arg(target->personMessage.birthday.day);
    qstr += QString("地址: %1\n").arg(QString::fromStdString(target->personMessage.address));

    if (target->personMessage.IsAlive == "离世")
    {
    qstr += QString("逝世日期: %1年%2月%3日\n").arg(target->personMessage.deathday.year).arg(target->personMessage.deathday.month).arg(target->personMessage.deathday.day);
    }
    qstr += QString("备注: %1\n\n\n").arg(QString::fromStdString(target->personMessage.remarks));
    return qstr;
}

//打印某层成员信息  先序遍历整棵树 找到某层 则打印
QString PrintDepthMessage(treenode* root, int depth)
{
    QString qstr ="";
    if (root->depth == depth)
    {
    qstr+=PrintMessage(root);
    }
    if (root->leftchild != NULL)
    {
    qstr+=PrintDepthMessage(root->leftchild, depth);
    }
    if (root->rightbrother != NULL)
    {
    qstr+=PrintDepthMessage(root->rightbrother, depth);
    }
    return qstr;
}

//查找某姓名的信息  包括父亲 孩子 用到了递归
QString SearchName(treenode* root, string name,bool& IsFind)
{
    QString qstr ="";
    if (name == root->personMessage.name)
    {
        IsFind = true;
        qstr += "此人信息:\n";
        qstr += PrintMessage(root);
        if (root->parent != NULL)
        {
            qstr += "其父亲信息:\n";
            qstr += PrintMessage(root->parent);
        }
        treenode* p = root;
        int childrennum = 0;
        if (p->leftchild != NULL)
        {
            qstr += QString("其孩子%1信息:\n").arg(++childrennum);
            p = p->leftchild;
            qstr += PrintMessage(p);
            while (p->rightbrother != NULL)
            {
                qstr += QString("其孩子%1信息:\n").arg(++childrennum);
                p = p->rightbrother;
                qstr += PrintMessage(p);
            }
        }
    }
    if (root->leftchild != NULL)
    {
        qstr+=SearchName(root->leftchild, name, IsFind);
    }
    if (root->rightbrother != NULL)
    {
        qstr+=SearchName(root->rightbrother, name, IsFind);
    }
    return qstr;
}

//按姓名输出成员信息 因为打印函数已经包含在SearchName中 所以此函数直接调用
QString PrintMessageByName(treenode* root,string name)
{
    QString qstr = "";
    bool IsFind = false;
    qstr = SearchName(root, name, IsFind);
    if (IsFind == false)
    {
        qstr += "家谱中无此名字的人!\n";
    }
    return qstr;
}

//查找某日期的信息 和SearchName实现类似 只是把name换成birthday
QString SearchBirthday(treenode* root, Date birthday,bool& IsFind)
{
    QString qstr = "";
    if ((birthday.day == root->personMessage.birthday.day)&& (birthday.month == root->personMessage.birthday.month)&& (birthday.year == root->personMessage.birthday.year))
    {
        IsFind = true;
        qstr += "此人信息:\n";
        qstr += PrintMessage(root);
        if (root->parent != NULL)
        {
            qstr += "其父亲信息:\n";
            qstr += PrintMessage(root->parent);
        }
        treenode* p = root;
        int childrennum = 0;
        if (p->leftchild != NULL)
        {
            qstr += QString("其孩子%1信息:\n").arg(++childrennum);
            p = p->leftchild;
            qstr+=PrintMessage(p);
            while (p->rightbrother != NULL)
            {
                qstr += QString("其孩子%1信息:\n").arg(++childrennum);
                p = p->rightbrother;
                qstr+=PrintMessage(p);
            }
        }
    }
    if (root->leftchild != NULL)
    {
        qstr+=SearchBirthday(root->leftchild, birthday, IsFind);
    }
    if (root->rightbrother != NULL)
    {
       qstr+= SearchBirthday(root->rightbrother, birthday, IsFind);
    }
    return qstr;
}

//按出生日期输出成员信息  因为打印函数已经包含在SearchBirthday中 所以此函数直接调用
QString PrintMessageByBirthday(treenode* root,Date date)
{
    QString qstr = "";


    bool IsFind = false;
    qstr = SearchBirthday(root, date, IsFind);

    if (IsFind == false)
    {
       qstr += "家谱中无此出生日期的人!\n";
    }

    return qstr;
}

// 在家谱树中，寻找一个指定的人名，并返回其指针
treenode* findPersonByName(treenode* node, string name) {
    if (node == NULL) {
       return NULL;
    }

    if (node->personMessage.name == name) {
       return node;
    }

    treenode* found = findPersonByName(node->leftchild, name);
    if (found != NULL) {
       return found;
    }

    return findPersonByName(node->rightbrother, name);
}

//先序遍历 遍历整棵树 直到 找到目标节点
void ReturnTreenodeByName(treenode*& root, string name,treenode*& target)
{
    if (root->personMessage.name == name)
    {
       target = root;
    }
    if (root->leftchild != NULL)
    {
       ReturnTreenodeByName(root->leftchild, name, target);
    }
    if (root->rightbrother != NULL)
    {
       ReturnTreenodeByName(root->rightbrother, name, target);
    }
}

//判断两人关系
QString JudgeRelationship(treenode* root,QString member1,QString member2)
{
    QString qstr = "";

    treenode* Person1 = NULL;
    treenode* Person2 = NULL;
    ReturnTreenodeByName(root, member1.toStdString(), Person1);
    ReturnTreenodeByName(root, member2.toStdString(), Person2);

    if (Person1 == NULL)
    {
       qstr += "家谱中没有" + member1 + "这个人\n";
               return qstr;
    }

    if (Person2 == NULL)
    {
       qstr += "家谱中没有" + member2 + "这个人\n";
               return qstr;
    }

    //主要用代数判断关系 包括 父亲 爷爷 祖先 叔叔 兄弟
    int depth1 = Person1->depth;
    int depth2 = Person2->depth;

    if (depth1 == depth2)
    {
       qstr += member1 + "和" + member2 + "为兄弟关系\n";
       return qstr;
    }

    if (depth1 - depth2 == -1)
    {
       if (Person2->parent == Person1)
       {
            qstr += member1 + "是" + member2 + "的父亲\n";
            return qstr;
       }
       else
       {
            qstr += member1 + "是" + member2 + "的叔叔\n";
       }
    }

    if (depth1 - depth2 == 1)
    {
       if (Person1->parent == Person2)
       {
            qstr += member2 + "是" + member1 + "的父亲\n";
            return qstr;
       }
       else
       {
            qstr += member2 + "是" + member1 + "的叔叔\n";
            return qstr;
       }
    }

    if (depth1 - depth2 == -2)
    {
       qstr += member1 + "是" + member2 + "的爷爷\n";
       return qstr;
    }

    if (depth1 - depth2 == 2)
    {
       qstr += member2 + "是" + member1 + "的爷爷\n";
       return qstr;
    }

    if (depth1 - depth2 < -2)
    {
       qstr += member1 + "是" + member2 + "的祖先\n";
       return qstr;
    }

    if (depth2 - depth1 < -2)
    {
       qstr += member2 + "是" + member1 + "的祖先\n";
       return qstr;
    }

    return qstr;
}

//按照姓名返回根节点
void ReturnTreenodeByNameAndBirthday(treenode*& root, string name, treenode*& target)
{
    if ((root->personMessage.name == name) )
    {
       target = root;
       return ;
    }
    if (root->leftchild != NULL)
    {
       ReturnTreenodeByNameAndBirthday(root->leftchild, name, target);
    }
    if (root->rightbrother != NULL)
    {
       ReturnTreenodeByNameAndBirthday(root->rightbrother, name, target);
    }
}

//添加孩子 是给某个人添加孩子  需要明确父亲
QString InsertChild(treenode*& root,string father,PersonMessage childl)
{
    QString qstr = "";

    treenode* person = NULL;
    ReturnTreenodeByName(root, father, person);
    if (person == NULL)
    {
       qstr += "输入信息有误!\n";
       return qstr;
    }

    treenode* child = new treenode;

    //设置新添加孩子代数
    child->depth = person->depth + 1;

    while (childl.IsMarried != "0" && childl.IsMarried != "1")
    {
       qstr += "输入数据非法，请重新输入:\n";
    }
    child->personMessage.IsMarried = (childl.IsMarried == "0") ? "已婚" : "未婚";
    if (person->leftchild == NULL)
    {
       person->leftchild = child;
       child->parent = person;
       child->leftchild = NULL;
       child->rightbrother = NULL;
       child->depth = person->depth + 1;
    }
    else
    {
       treenode* p = person->leftchild;
       while (p->rightbrother != NULL)
       {
            p = p->rightbrother;
       }
       p->rightbrother = child;
       child->parent = person;
       child->leftchild = NULL;
       child->rightbrother = NULL;
       child->depth = person->depth + 1;
    }
    child->personMessage.name = childl.name;
    child->personMessage.birthday = childl.birthday;
    child->personMessage.address = childl.address;
    child->personMessage.IsMarried = childl.IsMarried;
    child->personMessage.remarks = childl.remarks;
    return qstr;

    return ("信息添加成功！");
}

//修改某成员信息  前提是某一成员要先存在
QString ModifyMember(treenode*& root,string name,PersonMessage personMessage)
{
    QString qstr = "";


    treenode* member = NULL;
    ReturnTreenodeByNameAndBirthday(root, name, member);
    if (member == NULL)
    {
       qstr = "输入信息有误!\n";
       return qstr;
    }
    member->personMessage.name = personMessage.name;
    member->personMessage.birthday = personMessage.birthday;
    member->personMessage.address = personMessage.address;
    member->personMessage.IsMarried = personMessage.IsMarried;
    member->personMessage.remarks = personMessage.remarks;

    return ("信息修改成功！");
}


//先序遍历把树中元素存在文件中
void SaveFile(treenode* root, fstream& file)
{
    if (root != NULL)
    {
       file << root->depth;
       file << " ";
       file << root->personMessage.name;
       file << " ";
       file << root->personMessage.birthday.year;
       file << " ";
       file << root->personMessage.birthday.month;
       file << " ";
       file << root->personMessage.birthday.day;
       file << " ";
       file << root->personMessage.IsMarried;
       file << " ";
       file << root->personMessage.address;
       file << " ";
       file << root->personMessage.IsAlive;
       file << " ";
       file << root->personMessage.deathday.year;
       file << " ";
       file << root->personMessage.deathday.month;
       file << " ";
       file << root->personMessage.deathday.day;
       file << " ";
       file << root->personMessage.remarks;
       file << '\n';
    }
    if (root->leftchild != NULL)
    {
       SaveFile(root->leftchild, file);

    }
    if (root->rightbrother != NULL)
    {
       SaveFile(root->rightbrother, file);
    }
}


void writeDate(ofstream& fout, const Date& date) {
    fout << date.year << " " << date.month << " " << date.day << " ";
}

void writePerson(ofstream& fout, const PersonMessage& person) {
    fout << person.name << " ";
    writeDate(fout, person.birthday);
    fout << person.IsMarried << " " << person.address << " " << person.IsAlive << " ";
    writeDate(fout, person.deathday);
    fout << person.remarks << "\n";
}

void saveTree(treenode* node, ofstream& fout) {
    if (node == NULL) {
       return;
    }

    fout << node->depth << " ";
    writePerson(fout, node->personMessage);

    saveTree(node->leftchild, fout);
    saveTree(node->rightbrother, fout);
}


//存不进去
QString saveTreeToFile(string filename, treenode* root) {
    QString qstr;
    ofstream fout(filename);
    if (!fout) {
       qstr ="信息保存失败，文件未能正常打开\n";
       return qstr;
    }

    saveTree(root, fout);

    fout.close();

    return "信息保存成功";
}
