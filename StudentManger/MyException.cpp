#include "MyException.h"

CMyException::CMyException(char *msg):exception(msg)
{
}
CMyException::~CMyException()
{
}


CMyInputException::CMyInputException(char *msg) :CMyException(msg)
{
}
CMyInputException::~CMyInputException()
{
}

CMyNotFindException::CMyNotFindException(char *msg) :CMyException(msg)
{
}
CMyNotFindException::~CMyNotFindException()
{
}

CMyRepeatException::CMyRepeatException(char *msg) :CMyException(msg)
{
}
CMyRepeatException::~CMyRepeatException()
{
}

CMyFileException::CMyFileException(char *msg) :CMyException(msg)
{
}
CMyFileException::~CMyFileException()
{
}
