#pragma once
#include "MyString.h"

class CUtil
{
public:
    static int calcRandomMaxStore();
    static CMyString randomName();
    static char randomSex();
    static short randomYear();
    static char randomMonth();

    static int strToInt(char *str);

    template<typename Type>
    static void write(char*& dest,Type src);
    static void write(char*& dest,const char* src);
    static void write(char*& dest, void* src,int size);
    static void write(void* dest, void* src, int size);

    template<typename Type>
    static Type read(void* src);
    static void read(void* dest, void* src, int size);
};

template<typename Type>
inline void CUtil::write(char*& dest, Type src)
{
    memcpy(dest,&src,sizeof(Type));
    dest += sizeof(Type);
}

template<typename Type>
inline Type CUtil::read(void * src)
{
    Type dest;
    memcpy(&dest, src, sizeof(Type));
    return dest;
}
