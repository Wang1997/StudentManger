#include "Postion.h"

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
