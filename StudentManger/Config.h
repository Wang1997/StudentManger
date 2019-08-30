#pragma once
/*
全局的数据配置
*/
class CConfig
{
public:
    static const char *FilePath; //文件路径
    static const int InitDataNum; //初始数据量
    static const int MinNameLen; //最小名字长度
    static const int MaxNameLen; //最大名字长度
    static const int NameTableSize; //名字表大小
    static const int NameHashMult; //名字哈希值
    static const int DelTableSize; //删除表大小
};

