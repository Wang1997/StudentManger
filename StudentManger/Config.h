#pragma once
/*
��������
*/
class CConfig
{
public:
    static const char *FilePath; //�ļ�·��
    static const int InitDataNum; //��ʼ������
    static const int IDHashMult; //id����ֵ
    static const int IDDelFlag; //idɾ����־
    static const int SexType; //�Ա�����
    static const int MinYear; //��С���
    static const int MaxYear;//������
    static const int MinMonth; //��С�·�
    static const int MaxMonth; //����·�
    static const int MinNameLen; //��С���ֳ���
    static const int MaxNameLen; //������ֳ���
    static const char *RandomNameStr; //��������ַ���
    static const int NameTableSize; //���ֱ��С
    static const int NameHashMult; //���ֹ�ϣֵ
    static const int DelTableSize; //ɾ�����С
    static const int PosFindTimes; //λ�ò��Ҵ���
    static const int SquareArr[]; //2�Ĵη�����
};

