#include "Student.h"

uInt CStudent::MAX_ID = 1;
const uInt CStudent::BASE_SIZE = 8;

CStudent::CStudent(int id)
    :m_id(id)
{
}

CStudent::CStudent(uShort year, uChar month, uChar sex, CMyString name)
    :m_id(MAX_ID),m_year(year),m_month(month),m_sex(sex),m_name(name)
{
    ++MAX_ID; //id自增
}

CStudent::CStudent(CMyString name)
    :m_name(name)
{
}

CStudent::~CStudent()
{
}

uInt CStudent::getId() const
{
    return m_id;
}

uShort CStudent::getYear() const
{
    return m_year;
}

void CStudent::setYear(uShort year)
{
    m_year = year;
}

uChar CStudent::getMonth() const
{
    return m_month;
}

void CStudent::setMonth(uChar month)
{
    m_month = month;
}

uChar CStudent::getSex() const
{
    return m_sex;
}

void CStudent::setSex(uChar sex)
{
    m_sex = sex;
}

const CMyString & CStudent::getName() const
{
    return m_name;
}

void CStudent::setName(CMyString & name)
{
    m_name = name;
}

int CStudent::getTotalSize()
{
    return BASE_SIZE + m_name.length() + 1; //算上\0
}

void CStudent::initMaxId(uInt maxId)
{
    MAX_ID = maxId;
}

int CStudent::calcTotalSize(int nameLen)
{
    return BASE_SIZE + nameLen + 1; //加上 \0
}
