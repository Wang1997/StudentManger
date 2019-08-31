#pragma once
#include<exception>

// 异常基类
class CMyException : public std::exception
{
public:
    CMyException(char *msg);
    ~CMyException();
};

//输入相关异常
class CMyInputException : public CMyException
{
public:
    CMyInputException(char *msg);
    ~CMyInputException();
};

//查找不到异常
class CMyNotFindException : public CMyException
{
public:
    CMyNotFindException(char *msg);
    ~CMyNotFindException();
};

//重复异常
class CMyRepeatException : public CMyException
{
public:
    CMyRepeatException(char *msg);
    ~CMyRepeatException();
};



//文件操作异常
class CMyFileException : public CMyException
{
public:
    CMyFileException(char *msg);
    ~CMyFileException();
};

