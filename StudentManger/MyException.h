#pragma once
#include<exception>

// �쳣����
class CMyException : public std::exception
{
public:
    CMyException(char *msg);
    ~CMyException();
};

//��������쳣
class CMyInputException : public CMyException
{
public:
    CMyInputException(char *msg);
    ~CMyInputException();
};

//�����쳣
class CMyNotFindException : public CMyException
{
public:
    CMyNotFindException(char *msg);
    ~CMyNotFindException();
};

