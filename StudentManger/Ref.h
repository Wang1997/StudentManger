#pragma once

/****************************************************
* 引用计数类,只能通过getInstance获取一个实例
*****************************************************/

class CRef
{
private:
    CRef(); //私有构造,只能内部new
public:
    ~CRef();
    static CRef* getInstance(); //获得一个实例
    bool checkIsEmpty(); //检测是否无引用
    bool checkIsLast(); //检测是否是最后一个
    int addRef(); //增加引用,返回引用数量
    int subRef(); //减少引用,返回引用数量
private:
    int m_refNum; //引用的个数
};

