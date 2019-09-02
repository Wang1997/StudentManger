#include "MyString.h"
#include <stdexcept>
#include <cstring>

const int DEFAULT_SIZE = 5;

CMyString::CMyString() : m_buf(nullptr),m_ref(nullptr),m_size(0)
{
    m_len = 0;
    m_size = getCapacity(DEFAULT_SIZE);
    initBuf(m_size);
    initRef();
}

CMyString::CMyString(const char *buf) : m_buf(nullptr), m_ref(nullptr), m_size(0)
{
    m_len = strlen(buf);
    m_size = getCapacity(m_len+ DEFAULT_SIZE);
    initBuf(m_size,buf);
    initRef();
}

CMyString::CMyString(const CMyString &other)
{
    //浅拷贝
    memcpy(this, &other, sizeof(CMyString));
    m_ref->addRef(); //计数+1
}


CMyString::~CMyString()
{
    m_ref->subRef();
    if (m_ref->checkIsEmpty())
    { //最后一个引用就释放资源
        release();
    }
}

CMyString & CMyString::operator=(const CMyString &other)
{
    if(&other == this)
        return *this;

    //使用引用计数
    if (!m_ref->checkIsLast())
    { //不是最后一个就计数-1
        m_ref->subRef();
    }
    else
    { //否则释放资源
        release();
    }
    //浅拷贝
    memcpy(this,&other,sizeof(CMyString));
    m_ref->addRef(); //计数+1
    return *this;
}

CMyString & CMyString::operator=(const char *buf)
{
    CMyString str(buf);
    return *this = str;
}

int CMyString::length() const
{
    return m_len;
}

bool CMyString::isEmpty()
{
    return (0 == m_len);
}

void CMyString::clear()
{
    CMyString str;
    *this = str;
}

char CMyString::operator[](int index)
{
    return at(index);
}

char CMyString::at(int index)
{
    if (index < 0 || index >= m_len)
        throw std::out_of_range("越界访问");
    return m_buf[index];
}

CMyString & CMyString::operator+=(const CMyString &other)
{
    return *this += other.m_buf;
}

CMyString & CMyString::operator+=(const char *str)
{
    //写实拷贝
    int addSize = strlen(str) + 1;
    int newSize = m_size;
    int newLen = m_len + addSize - 1;
    int newFlag = 0;
    if (!checkIsEnough(m_len - 1, addSize))
    { //空间不足够
        newSize = getCapacity(addSize);
        newFlag = 1; //需新开辟空间
    }
    
    //使用引用计数
    if (!m_ref->checkIsLast())
    { //不是最后一个就计数-1
        m_ref->subRef();
        newFlag = 1; //无论如何都需要新开辟空间
    }
    else
    {//只有自己
        if (newFlag)
        { //释放资源
            newFlag = -1;
        }
        else
        {
            strcpy(this->m_buf + this->m_len, str);
            m_len = newLen;
        }
    }

    //替换新数据
    if (newFlag)
    {
        char *tempBuf = new char[newSize];
        strcpy(tempBuf, this->m_buf);
        strcpy(tempBuf + this->m_len, str);
        if(newFlag == -1)
            release(); //拷贝后释放旧资源
        this->m_buf = tempBuf;
        this->m_len = newLen;
        this->m_size = newSize;
        this->m_ref = CRef::getInstance();
    }
    
    return *this;
}

CMyString & CMyString::operator+=(char ch)
{
    char str[] = { ch,0 };
    return *this += str;
}

CMyString & CMyString::operator+=(int num)
{
    char str[20];
    sprintf(str, "%d", num);
    return *this += str;
}

CMyString & CMyString::append(const CMyString &other)
{
    return *this += other.m_buf;
}

CMyString & CMyString::append(const char *other)
{
    return *this += other;
}

CMyString & CMyString::append(char ch)
{
    return *this += ch;
}

CMyString & CMyString::append(int num)
{
    return *this += num;
}

CMyString & CMyString::assign(const CMyString &other)
{
    return *this = other;
}

CMyString & CMyString::assign(const char *other)
{
    return *this = other;
}

CMyString & CMyString::insert(const CMyString &other, int pos)
{
    return (*this).insert(other.m_buf,pos);
}

CMyString & CMyString::insert(const char *str, int pos)
{
    if (pos < 0 || pos >= m_len)
    {
        return *this += str; //末尾加
    }

    //写实拷贝
    int addSize = strlen(str) + 1;
    int newSize = m_size;
    int newLen = m_len + addSize - 1;
    int newFlag = 0;
    if (!checkIsEnough(m_len - 1, addSize))
    { //空间不足够
        newSize = getCapacity(addSize);
        newFlag = 1; //需新开辟空间
    }

    //使用引用计数
    if (!m_ref->checkIsLast())
    { //不是最后一个就计数-1
        m_ref->subRef();
        newFlag = 1; 
    }
    else
    {
        if (newFlag)
        { //释放资源
            newFlag = -1;
        }
        else
        {
            int tempLen = newLen;
            for (int i = m_len; i >= pos; --i)
            {//挪用空间
                m_buf[tempLen--] = m_buf[i];
            }
            for (int i = addSize-2; i >= 0; --i)
            {//插入数据
                m_buf[tempLen--] = str[i];
            }
            m_len = newLen;
        }
    }

    //分配新数据
    if (newFlag)
    {
        char *tempBuf = new char[newSize];
        int index = 0;
        for (int i = 0; i < pos; ++i)
        {
            tempBuf[index++] = m_buf[i];
        }
        for (int i = 0; i < addSize -1; ++i)
        {
            tempBuf[index++] = str[i];
        }
        for (int i = pos; i <= m_len; ++i) //加'\0'
        {
            tempBuf[index++] = m_buf[i];
        }
        if (newFlag == -1)
            release(); //拷贝后释放旧资源
        this->m_buf = tempBuf;
        this->m_len = newLen;
        this->m_size = newSize;
        this->m_ref = CRef::getInstance();
    }

    return *this;
}

CMyString & CMyString::erase(int pos, int n)
{
    if (pos < 0 || pos >= m_len)
    {
        throw std::out_of_range("pos越界");
    }

    if (n <= 0)
    {
        throw std::out_of_range("删除的数量有误");
    }

    int delEndIndex = pos + n;
    if(delEndIndex > m_len)
        delEndIndex = m_len;

    int newLen = m_len - (delEndIndex - pos);

    //使用引用计数
    if (!m_ref->checkIsLast())
    { //不是最后一个就计数-1
        m_ref->subRef();
        //分离数据
        char *tmpBuf = new char[m_size];
        int index = 0;
        for(int i=0;i < pos;++i)
            tmpBuf[index++] = m_buf[i];
        for(int i=delEndIndex;i<=m_len;++i)
            tmpBuf[index++] = m_buf[i];
        
        m_buf = tmpBuf;
        m_ref = CRef::getInstance();
        m_len = newLen;
    }
    else
    {
        int index = pos;
        for (int i = delEndIndex; i <= m_len; ++i)
            m_buf[index++] = m_buf[i];
        m_len = newLen;
    }
    return *this;
}

const char * CMyString::c_str() const
{
    return m_buf;
}

CMyString CMyString::substr(int pos, int n)
{
    if (pos < 0 || pos >= m_len)
    {
        throw std::out_of_range("pos访问越界");
    }

    if(n <= 0 || pos + n >= m_len)
        n = m_len - pos;
    char endChar = m_buf[pos+n];
    
    m_buf[pos+n] = '\0';
    CMyString str(m_buf+pos);
    m_buf[pos+n] = endChar;

    return str;
}

int CMyString::find(const CMyString &other)
{
    return find(other.m_buf);
}

int CMyString::find(const char *str)
{
    int strLen = strlen(str);
    int *nextArr = new int[strLen];
    getMatchNextArr(str,nextArr); //获取next数组

    int i = 0;
    int j = 0;
    while (i < m_len && j < strLen)
    {
        if (j == -1 || m_buf[i] == str[j])
        {
            ++i;
            ++j;
        } 
        else
        {
            j = nextArr[j]; //匹配回退
        }
    }

    delete nextArr;

    if(j == strLen)
        return i - strLen;

    return npos;
}

int CMyString::find_first_of(const CMyString &other, int pos)
{
    return find_first_of(other.m_buf,pos);
}

int CMyString::find_first_of(const char *str, int pos)
{
    if(pos < 0 || pos >= m_len)
        return npos;

    int searchLen = strlen(str);
    for (int i = pos; i <= m_len - searchLen; ++i)
    {
        if(i > m_len - searchLen)
            break; //剩余匹配长度不够
        int index = i;
        bool find = true;
        //暴力匹配
        for (int j = 0; j < searchLen; ++j)
        {
            if (m_buf[index++] != str[j])
            {
                find = false;
                break;
            }
        }
        if(find)
            return i;
    }
    return npos;
}

int CMyString::find_last_of(const CMyString &other, int pos)
{
    return find_last_of(other.m_buf,pos);
}

int CMyString::find_last_of(const char *str, int pos)
{
    if(pos == -1 || pos >= m_len)
        pos = m_len - 1;

    if(pos < 0)
        return npos;

    int searchLen = strlen(str);

    for (int i = pos; i >= 0; --i)
    {
        if(pos < searchLen - 1)
            break; //匹配长度不够
        int index = i;
        bool find = true;
        //暴力匹配
        for (int j = searchLen - 1; j >= 0; --j)
        {
            if (m_buf[index--] != str[j])
            {
                find = false;
                break;
            }
        }
        if (find)
            return i;
    }
    
    return npos;
}

void CMyString::initBuf(int size,const char *buf)
{
    m_buf = new char[size];
    if (buf != nullptr)
    {
        strcpy(m_buf,buf);
    }
}

void CMyString::initRef()
{
    m_ref = CRef::getInstance();
}

void CMyString::release()
{
    if (m_buf != nullptr)
    {
        delete[] m_buf;
        m_buf = nullptr;
    }
    if (m_ref != nullptr)
    {
        delete m_ref;
        m_ref = nullptr;
    }
}

bool CMyString::checkIsEnough(int index, int size)
{
    if(index + 1 + size > m_size)
        return false;
    return true;
}

int CMyString::getCapacity(int newSize)
{
    return (newSize + m_size) * 2;
}

void CMyString::getMatchNextArr(const char *str, int * const nextArr)
{
    int strLen = strlen(str);
    int j = 0;
    int k = -1;
    nextArr[0] = -1;
    while (j < strLen)
    {
        if (k == -1 || str[j] == str[k])
        {
            nextArr[++j] = ++k;
        }
        else
        {
            k = nextArr[k];
        }
    }
}

std::ostream & operator<<(std::ostream &out, const CMyString &strObj)
{
    if (strObj.m_len > 0)
        out << strObj.m_buf;
    return out;
}

std::istream & operator >> (std::istream &in, CMyString &strObj)
{
    char str[1024] = { 0 };
    in.getline(str, 1024); //输入
    strObj = str;
    return in;
}

CMyString operator+(const CMyString &strObj1, const CMyString &strObj2)
{
    CMyString str(strObj1.m_buf);
    str += strObj2.m_buf;
    return str;
}

bool operator==(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) == 0 ? true : false;
}

bool operator!=(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) != 0 ? true : false;
}

bool operator<(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) < 0 ? true : false;
}

bool operator<=(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) <= 0 ? true : false;
}

bool operator>(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) > 0 ? true : false;
}

bool operator>=(const CMyString &strObj1, const CMyString &strObj2)
{
    return strcmp(strObj1.m_buf, strObj2.m_buf) >= 0 ? true : false;
}