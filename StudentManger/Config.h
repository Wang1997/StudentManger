#pragma once
/*
数据配置
*/
class CConfig
{
public:
    static const char *FilePath; //文件路径
    static const int InitDataNum; //初始数据量
    static const int IDHashMult; //id多重值
    static const int IDDelFlag; //id删除标志
    static const int SexType; //性别种类
    static const int MinYear; //最小年份
    static const int MaxYear;//最大年份
    static const int MinMonth; //最小月份
    static const int MaxMonth; //最大月份
    static const int MinNameLen; //最小名字长度
    static const int MaxNameLen; //最大名字长度
    static const char *RandomNameStr; //名字随机字符串
    static const int NameTableSize; //名字表大小
    static const int NameHashMult; //名字哈希值
    static const int DelTableSize; //删除表大小
    static const int PosFindTimes; //位置查找次数
    static const int SquareArr[]; //2的次方数表
};

