#pragma once

/****************************************************
* ���ü�����,ֻ��ͨ��getInstance��ȡһ��ʵ��
*****************************************************/

class CRef
{
private:
    CRef(); //˽�й���,ֻ���ڲ�new
public:
    ~CRef();
    static CRef* getInstance(); //���һ��ʵ��
    bool checkIsEmpty(); //����Ƿ�������
    bool checkIsLast(); //����Ƿ������һ��
    int addRef(); //��������,������������
    int subRef(); //��������,������������
private:
    int m_refNum; //���õĸ���
};

