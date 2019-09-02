#pragma once
#include"AVLTree.hpp"
#include "HashTable.hpp"
#include "Elem.h"
#include "Store.h"

class CManger
{
public:
    CManger();
    ~CManger();
    
    void start(); //开始
    void loadData(char * data, int maxStore); //加载数据
    char* initData(int& maxStore); //初始化新数据

//控制部分
    void menuControl(); //菜单
    void addControl(); //添加
    void deleteControl(); //删除
    void updateControl(); //更新
    void queryIdControl(); //查询Id
    void queryNameControl(); //查询姓名

//输入界面部分
    int inputIdView();//ID输入界面
    CMyString inputNameView(bool ignore=false); //姓名输入界面
    char inputSexView(bool ignore = false); //性别输入界面
    short inputYearView(bool ignore = false); //年份输入界面
    char inputMonthView(bool ignore = false); //月份输入界面
    bool inputConfirmView(); //确认输入界面

//功能逻辑部分
    bool addStudent(CStudent *pStu); //添加学生
    bool addInStore(const CElem& elem);//添加到存储(文件)
    CPostion getStuPostion(int size); //获取一块size大小的空间
    bool deleteStudent(AVLTree<CElem, TreeCompare<CElem>>::Iterator treeIt);//删除学生
    bool deleteInHashName(const CElem& elem); //在hash表中删除
    bool deleteInStore(int pos); //在文件中标记删除
    bool updateName(const CElem& elem,const CMyString& name);
    AVLTree<CElem, TreeCompare<CElem>>::Iterator queryById(int id);//查询ID功能
    void queryByName(CMyString& name); //查询姓名功能

    void showStudent(CStudent *pStu); //展示学生信息
    
private:
    AVLTree<CElem, TreeCompare<CElem>> m_TreeById;
    HashTable<CElem, Hash<CElem>> m_HashByName;
    HashTable<CPostion, Hash<CPostion>> m_HashByPos;
    CStore m_store;
};

