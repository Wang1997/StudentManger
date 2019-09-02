#pragma once
#include"AVLTree.hpp"
#include "HashTable.hpp"
#include "Elem.h"
#include "Store.h"

class CManger
{
public:
    CManger();
    ~CManger();
    
    void start(); //��ʼ
    void loadData(char * data, int maxStore); //��������
    char* initData(int& maxStore); //��ʼ��������

//���Ʋ���
    void menuControl(); //�˵�
    void addControl(); //���
    void deleteControl(); //ɾ��
    void updateControl(); //����
    void queryIdControl(); //��ѯId
    void queryNameControl(); //��ѯ����

//������沿��
    int inputIdView();//ID�������
    CMyString inputNameView(bool ignore=false); //�����������
    char inputSexView(bool ignore = false); //�Ա��������
    short inputYearView(bool ignore = false); //����������
    char inputMonthView(bool ignore = false); //�·��������
    bool inputConfirmView(); //ȷ���������

//�����߼�����
    bool addStudent(CStudent *pStu); //���ѧ��
    bool addInStore(const CElem& elem);//��ӵ��洢(�ļ�)
    CPostion getStuPostion(int size); //��ȡһ��size��С�Ŀռ�
    bool deleteStudent(AVLTree<CElem, TreeCompare<CElem>>::Iterator treeIt);//ɾ��ѧ��
    bool deleteInHashName(const CElem& elem); //��hash����ɾ��
    bool deleteInStore(int pos); //���ļ��б��ɾ��
    bool updateName(const CElem& elem,const CMyString& name);
    AVLTree<CElem, TreeCompare<CElem>>::Iterator queryById(int id);//��ѯID����
    void queryByName(CMyString& name); //��ѯ��������

    void showStudent(CStudent *pStu); //չʾѧ����Ϣ
    
private:
    AVLTree<CElem, TreeCompare<CElem>> m_TreeById;
    HashTable<CElem, Hash<CElem>> m_HashByName;
    HashTable<CPostion, Hash<CPostion>> m_HashByPos;
    CStore m_store;
};

