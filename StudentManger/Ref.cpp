#include "Ref.h"

CRef * CRef::getInstance()
{
    return new CRef();
}

CRef::CRef() :m_refNum(1) {}

CRef::~CRef() {}

bool CRef::checkIsEmpty()
{
    return (0 == m_refNum);
}

bool CRef::checkIsLast()
{
    return (1 == m_refNum);
}

int CRef::addRef()
{
    return ++m_refNum;
}

int CRef::subRef()
{
    return --m_refNum;
}

