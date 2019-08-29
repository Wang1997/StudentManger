#pragma once
#include <iostream>
#include "Ref.h"

//String类 增加引用计数和写实功能
class CMyString
{
public:
    CMyString();
    CMyString(const char*);
    CMyString(const CMyString&);
    ~CMyString();
    CMyString& operator= (const CMyString&);
    CMyString& operator= (const char*);

public: //Capacity
    int length(); //求长度
    bool isEmpty(); //是否为空
    void clear(); //清空

public: //Element access
    char operator[] (int index); //不返回引用
    char at(int index);

public: //Modifiers
    CMyString& operator+= (const CMyString&); //增加
    CMyString& operator+= (const char*);
    CMyString& operator+= (char ch);
    CMyString& operator+= (int num);
    CMyString& append(const CMyString&); //追加
    CMyString& append(const char*);
    CMyString& append(char ch);
    CMyString& append(int num);
    CMyString& assign(const CMyString&); //替换
    CMyString& assign(const char*);
    CMyString& insert(const CMyString&,int pos = 0); //插入
    CMyString& insert(const char*,int pos=0);
    CMyString& erase(int pos, int n); //删除

public: //String operations
    const char * c_str() const;
    CMyString substr(int pos,int n = -1); //截取子串
    int find(const CMyString&); //kmp快速查找
    int find(const char*);
    int find_first_of(const CMyString&,int pos = 0); //从多少位置开始普通查找
    int find_first_of(const char*, int pos = 0);
    int find_last_of(const CMyString&, int pos = -1);//从多少位置开始普通倒叙查找
    int find_last_of(const char*, int pos = -1);

public: //Other operator
    friend std::ostream& operator<< (std::ostream&,const CMyString&);
    friend std::istream& operator>> (std::istream&,CMyString&);
    friend CMyString operator+ (const CMyString&, const CMyString&);
    friend bool operator== (const CMyString&, const CMyString&);
    friend bool operator!= (const CMyString&, const CMyString&);
    friend bool operator< (const CMyString&, const CMyString&);
    friend bool operator<= (const CMyString&, const CMyString&);
    friend bool operator> (const CMyString&, const CMyString&);
    friend bool operator>= (const CMyString&, const CMyString&);

private:
    void initBuf(int size,const char *buf=nullptr); //初始化缓存
    void initRef(); //初始化引用计数
    void release(); //销毁空间
    bool checkIsEnough(int index,int size); //检测空间是否足够
    int getCapacity(int newSize); //获取容量大小
    void getMatchNextArr(const char *str,int * const nextArr); //获得匹配next数组

private:
    char *m_buf; //字符串缓存
    int m_len;
    int m_size;
    CRef *m_ref; //引用计数
public:
    static const int npos = -1; //查找结果使用
};
