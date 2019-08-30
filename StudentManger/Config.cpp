#include "Config.h"

const char *CConfig::FilePath = "./data.bin"; //文件路径
const int CConfig::InitDataNum = 10; //初始数据量(学生数量)
const int CConfig::MinNameLen = 4; //最小名字长度
const int CConfig::MaxNameLen = 16; //最大名字长度
const int CConfig::NameTableSize = 29989; //名字表大小
const int CConfig::NameHashMult = 31; //名字哈希值
const int CConfig::DelTableSize = 28; //删除表大小
