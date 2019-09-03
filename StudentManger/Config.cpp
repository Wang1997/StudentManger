#include "Config.h"

const char *CConfig::FilePath = "./data.bin"; //�ļ�·��
const int CConfig::InitDataNum = 1000000; //1000000 ��ʼ������(ѧ������)
const int CConfig::IDHashMult = 100000; //100000 id����ֵ
const int CConfig::IDDelFlag = -1; //idɾ����־
const int CConfig::SexType = 3; //�Ա�����
const int CConfig::MinYear = 1970; //��С���
const int CConfig::MaxYear = 2019;//������
const int CConfig::MinMonth = 1; //��С�·�
const int CConfig::MaxMonth = 12; //����·�
const int CConfig::MinNameLen = 4; //��С���ֳ���
const int CConfig::MaxNameLen = 10; //������ֳ���
const char *CConfig::RandomNameStr = 
    "qwert0yuyi1iop2asdf3ghjk4lzxcvb5nmWERT6YUIO7PASD8FGHJ9KKLZXCVBNM"; //��������ַ���
const int CConfig::NameTableSize = 29989;//29989 ���ֱ��С
const int CConfig::NameHashMult = 31; //���ֹ�ϣֵ
const int CConfig::DelTableSize = 20; //ɾ�����С
const int CConfig::PosFindTimes = 3; //λ�ò��Ҵ���
const int CConfig::SquareArr[] = 
    { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,
        524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,
        268435456,536870912,1073741824};
