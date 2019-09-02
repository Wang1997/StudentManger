#pragma once
#include "Elem.h"
#include "Config.h"
/*
存放一些仿函数
*/


template<typename Object>
class TreeCompare
{
public:
    int operator()(const Object& t1, const Object& t2)
    {
        if (t1 > t2)
            return 1;
        else if (t1 < t2)
            return -1;
        else
            return 0;
    }
};

template<>
class TreeCompare<CElem>
{
public:
    int operator()(const CElem& t1, const CElem& t2)
    {
        int t1Id = t1.getStudent()->getId() % CConfig::IDHashMult;
        int t2Id = t2.getStudent()->getId() % CConfig::IDHashMult;
        if (t1Id > t2Id)
            return 1;
        else if (t1Id < t2Id)
            return -1;
        else
            return 0;
    }
};



template<typename Object>
class Hash
{
public:
    unsigned int operator()(const Object& elem)
    {
        return (unsigned int)elem;
    }
};

template<>
class Hash<CElem>
{
public:
    unsigned int operator()(const CElem& elem)
    {
        unsigned int res = 0;
        const char *str = elem.getStudent()->getName().c_str();
        while (*str)
        {
            res = res * CConfig::NameHashMult + *str;
            ++str;
        }
        return res;
    }
};


template<>
class Hash<CPostion>
{
public:
    unsigned int operator()(const CPostion& pos)
    {
        return pos.getSize();
    }
};



