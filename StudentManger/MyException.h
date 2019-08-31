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

//���Ҳ����쳣
class CMyNotFindException : public CMyException
{
public:
    CMyNotFindException(char *msg);
    ~CMyNotFindException();
};

//�ظ��쳣
class CMyRepeatException : public CMyException
{
public:
    CMyRepeatException(char *msg);
    ~CMyRepeatException();
};



//�ļ������쳣
class CMyFileException : public CMyException
{
public:
    CMyFileException(char *msg);
    ~CMyFileException();
};

