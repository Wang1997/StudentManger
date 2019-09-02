#include "Postion.h"

CPostion::CPostion():m_pos(-1),m_size(-1)
{
}

CPostion::CPostion(int pos, int size)
    :m_pos(pos),m_size(size)
{
}

CPostion::CPostion(int size)
    :m_size(size)
{
}

CPostion::~CPostion()
{
}

int CPostion::getPos() const
{
    return m_pos;
}

int CPostion::getSize() const
{
    return m_size;
}

CPostion & CPostion::operator++()
{
    ++m_size;
    return *this;
}

CPostion & CPostion::operator++(int)
{
    CPostion old = *this;
    ++*this;
    return old;
}
