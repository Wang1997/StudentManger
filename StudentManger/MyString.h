#pragma once
#include <iostream>
#include "Ref.h"

//String�� �������ü�����дʵ����
class CMyString
{
public:
    CMyString();
    CMyString(const char*);
    CMyString(const CMyString&);
    ~CMyString();
    CMyString& operator= (const CMyString&);
    CMyString& operator= (const char*);

public: //Capacity
    int length(); //�󳤶�
    bool isEmpty(); //�Ƿ�Ϊ��
    void clear(); //���

public: //Element access
    char operator[] (int index); //����������
    char at(int index);

public: //Modifiers
    CMyString& operator+= (const CMyString&); //����
    CMyString& operator+= (const char*);
    CMyString& operator+= (char ch);
    CMyString& operator+= (int num);
    CMyString& append(const CMyString&); //׷��
    CMyString& append(const char*);
    CMyString& append(char ch);
    CMyString& append(int num);
    CMyString& assign(const CMyString&); //�滻
    CMyString& assign(const char*);
    CMyString& insert(const CMyString&,int pos = 0); //����
    CMyString& insert(const char*,int pos=0);
    CMyString& erase(int pos, int n); //ɾ��

public: //String operations
    const char * c_str() const;
    CMyString substr(int pos,int n = -1); //��ȡ�Ӵ�
    int find(const CMyString&); //kmp���ٲ���
    int find(const char*);
    int find_first_of(const CMyString&,int pos = 0); //�Ӷ���λ�ÿ�ʼ��ͨ����
    int find_first_of(const char*, int pos = 0);
    int find_last_of(const CMyString&, int pos = -1);//�Ӷ���λ�ÿ�ʼ��ͨ�������
    int find_last_of(const char*, int pos = -1);

public: //Other operator
    friend std::ostream& operator<< (std::ostream&,const CMyString&);
    friend std::istream& operator>> (std::istream&,CMyString&);
    friend CMyString operator+ (const CMyString&, const CMyString&);
    friend bool operator== (const CMyString&, const CMyString&);
    friend bool operator!= (const CMyString&, const CMyString&);
    friend bool operator< (const CMyString&, const CMyString&);
    friend bool operator<= (const CMyString&, const CMyString&);
    friend bool operator> (const CMyString&, const CMyString&);
    friend bool operator>= (const CMyString&, const CMyString&);

private:
    void initBuf(int size,const char *buf=nullptr); //��ʼ������
    void initRef(); //��ʼ�����ü���
    void release(); //���ٿռ�
    bool checkIsEnough(int index,int size); //���ռ��Ƿ��㹻
    int getCapacity(int newSize); //��ȡ������С
    void getMatchNextArr(const char *str,int * const nextArr); //���ƥ��next����

private:
    char *m_buf; //�ַ�������
    int m_len;
    int m_size;
    CRef *m_ref; //���ü���
public:
    static const int npos = -1; //���ҽ��ʹ��
};
