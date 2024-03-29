#pragma once
#include "MyString.h"

typedef unsigned int uInt;
typedef unsigned short uShort;
typedef unsigned char uChar;

/*
学生类 用于存放学生基本信息
*/
class CStudent
{
public:
    CStudent(int id);
    CStudent(const CMyString& name, uChar sex, uShort year,uChar month);
    CStudent(const CMyString& name);
    ~CStudent();

    uInt getId() const;
    uShort getYear() const;
    void setYear(uShort year);
    uChar getMonth() const;
    void setMonth(uChar month);
    uChar getSex() const;
    void setSex(uChar sex);
    const CMyString& getName() const;
    void setName(const CMyString& name);

    int getTotalSize();
    
public:
    static void initMaxId(uInt maxId);
    static int calcTotalSize(int nameLen);
    static const uInt BASE_SIZE; //除姓名以外的字节大小
private:
    uInt m_id;
    uShort m_year;
    uChar m_month;
    uChar m_sex;
    CMyString m_name;

    static uInt MAX_ID;
};

