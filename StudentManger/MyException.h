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

//查找异常
class CMyNotFindException : public CMyException
{
public:
    CMyNotFindException(char *msg);
    ~CMyNotFindException();
};

