#include "Util.h"
#include "Elem.h"
#include "Config.h"

int CUtil::calcRandomMaxStore()
{
    return (1 + CStudent::BASE_SIZE + CConfig::MaxNameLen)
                * CConfig::InitDataNum;
}

CMyString CUtil::randomName()
{
    CMyString str;
    int randomStrLen = strlen(CConfig::RandomNameStr);
    int diff = CConfig::MaxNameLen - CConfig::MinNameLen;
    int nameNum = rand() % diff + CConfig::MinNameLen;
    for (int i = 0; i < nameNum; ++i)
    {
        str.append(CConfig::RandomNameStr[rand() % randomStrLen]);
    }
    return str;
}

char CUtil::randomSex()
{
    return (char)(rand() % CConfig::SexType);
}

short CUtil::randomYear()
{
    return (short)(rand() % (CConfig::MaxYear - CConfig::MinYear) + CConfig::MinYear);
}

char CUtil::randomMonth()
{
    return (char)(rand() % CConfig::MaxMonth + 1);
}

int CUtil::strToInt(char * str)
{
    int len = strlen(str);
    int res = 0;
    for (int i = 0; i < len; ++i)
    {
        if (!(str[i] >= '0' && str[i] <= '9')) //不为数字结束
        {
            break;
        }
        res = res * 10 + (str[i] - '0');
    }
    
    return res;
}

void CUtil::write(char *& dest, const char * src)
{
    int size = strlen(src) + 1;
    memcpy(dest, src, size);
    dest += size;
}

void CUtil::write(char *& dest, void * src, int size)
{
    memcpy(dest, src, size);
    dest += size;
}

void CUtil::write(void * dest, void * src, int size)
{
    memcpy(dest, src, size);
}

void CUtil::read(void * dest, void * src, int size)
{
    memcpy(dest, src, size);
}
