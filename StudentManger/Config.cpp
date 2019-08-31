#include "Config.h"

const char *CConfig::FilePath = "./data.bin"; //文件路径
const int CConfig::InitDataNum = 6; //初始数据量(学生数量)
const int CConfig::SexType = 3; //性别种类
const int CConfig::MinYear = 1900; //最小年份
const int CConfig::MaxYear = 2019;//最大年份
const int CConfig::MinMonth = 1; //最小月份
const int CConfig::MaxMonth = 12; //最大月份
const int CConfig::MinNameLen = 4; //最小名字长度
const int CConfig::MaxNameLen = 10; //最大名字长度
const char *CConfig::RandomNameStr = 
    "qwert0yuyi1iop2asdf3ghjk4lzxcvb5nmWERT6YUIO7PASD8FGHJ9KKLZXCVBNM"; //名字随机字符串
const int CConfig::NameTableSize = 3;//29989; //名字表大小
const int CConfig::NameHashMult = 31; //名字哈希值
const int CConfig::DelTableSize = 20; //删除表大小
const int CConfig::SquareArr[] = 
    { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,
        524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,
        268435456,536870912,1073741824};
