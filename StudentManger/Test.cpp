#include "Test.h"
#include <iostream>
#include <ctime>
#include <algorithm>

#include"AVLTree.hpp"
#include "HashTable.hpp"
#include "Config.h"
using namespace std;

CTest::CTest()
{
}


CTest::~CTest()
{
}

int CTest::test1()
{
    cout << "��ʼ����hash����" << endl;
    //const int size = 29989;
    const int size = 39989;
    srand(time(NULL));
    int randomStrLen = strlen(CConfig::RandomNameStr);
    HashTable<CElem, Hash<CElem>> table(size);
    for (int i = 1; i <= 1000000; ++i)
    {
        int diff = CConfig::MaxNameLen - CConfig::MinNameLen;
        int nameNum = rand() % diff + CConfig::MinNameLen;
        CMyString str;
        for (int i = 0; i < nameNum; ++i)
        {
            str.append(CConfig::RandomNameStr[rand() % randomStrLen]);
        }
        CElem elem(str);
        table.insert(elem);
    }
    cout << "hash���..��ʼ��������" << endl;

    int maxNum = 0;
    int minNum = 0x7fffffff;
    for (int i = 0; i < size; ++i)
    {
        if (table.hashTable[i] != nullptr)
        {
            int num = 0;
            HashTable<CElem, Hash<CElem>>::Node *node = table.hashTable[i];
            while (node)
            {
                node = node->next;
                num++;
            }
            maxNum = max(maxNum, num);
            minNum = min(minNum, num);
        }
    }
    cout << "�����������: " << maxNum << endl; //62 60 ~ 70 ֮�䲨��
    cout << "��С���������: " << minNum << endl; //12 10 ~ 20 ֮�䲨��
    return maxNum * 10000 + minNum;
}

void CTest::test2()
{
    cout << "��ʼ����������(����)" << endl;
    AVLTree<CElem, TreeCompare<CElem>> tree;
    for (int i = 1; i <= 1000000; ++i)
    {
        CElem elem(i);
        //tree.insert_unique(elem); //7-2 6~8s
        tree.insert_equal(elem); //5s - 2s
    }
    cout << "�����������(����)" << endl;
}

void CTest::test3()
{
    cout << "��ʼ����������(����)" << endl;
    AVLTree<CElem, TreeCompare<CElem>> tree;
    int MaxHeight = 0;
    while (MaxHeight <= 30)
    {
        if(CConfig::SquareArr[MaxHeight] >= 1000000)
            break;
        MaxHeight++;
    }
    --MaxHeight;
    cout << CConfig::SquareArr[MaxHeight] << endl;
    MyQueue<int> idQueuqe;
    int num = CConfig::SquareArr[MaxHeight];
    idQueuqe.push(num);
    int Level = 1;
    int TotalNum = 0;
    while (TotalNum <= 1000000)
    {
        int rId = idQueuqe.front();
        CElem elem(rId);
        //tree.insert_unique(elem); // 9 - 3 s
        tree.insert_equal(elem); // 5s - 2s
        idQueuqe.pop();
        int leftId = rId - CConfig::SquareArr[MaxHeight - Level];
        idQueuqe.push(leftId);
        int rightId = rId + CConfig::SquareArr[MaxHeight - Level];
        idQueuqe.push(rightId);
        ++TotalNum;
        if(TotalNum >= CConfig::SquareArr[Level] - 1)
            ++Level;
    }
    cout << "�����������(����)" << endl;
}

/*
100�ݲ������ݷֲ����

size = 29989
��������������:
��Χ: max: 69 ,min: 57
�������Ϊ: 60 ,������: 23��
��С������������:
��Χ: max: 14 ,min: 8
�������Ϊ: 12 ,������: 34��

size=39989
��������������:
��Χ: max: 56 ,min: 46
�������Ϊ: 48 ,������: 26��
��С������������:
��Χ: max: 8 ,min: 4
�������Ϊ: 7 ,������: 44��
*/

void CTest::test4()
{
    int arrMax[10000] = { 0 };
    int arrMin[10000] = { 0 };
    for (int i = 1; i <= 100; ++i)
    {
        int res = test1();
        int maxNum = res / 10000;
        int minNum = res % 10000;
        ++arrMin[minNum];
        ++arrMax[maxNum];
    }
    int MinMin = 0x7fffffff;
    int MinMax = 0;
    int MaxMin = 0x7fffffff;
    int MaxMax = 0;

    int Min_MaxCounts = 0;
    int Min_MaxIndex = 0;
    int Max_MaxCounts = 0;
    int Max_MaxIndex = 0;

    for (int i = 0; i < 10000; ++i)
    {
        if (arrMin[i] != 0)
        {
            MinMax = i;
            if(MinMin == 0x7fffffff)
                MinMin = i;
            if (arrMin[i] >= Min_MaxCounts)
            {
                Min_MaxCounts = arrMin[i];
                Min_MaxIndex = i;
            }
        }
            
        if (arrMax[i] != 0)
        {
            MaxMax = i;
            if (MaxMin == 0x7fffffff)
                MaxMin = i;
            if (arrMax[i] >= Max_MaxCounts)
            {
                Max_MaxCounts = arrMax[i];
                Max_MaxIndex = i;
            }
        }
    }
    cout<<"��������������:"<<endl;
    cout<<"��Χ: max: " << MaxMax << " ,min: " << MaxMin << endl;
    cout<<"�������Ϊ: " << Max_MaxIndex << " ,������: " << Max_MaxCounts << "��"<<endl;
    cout << "��С������������:" << endl;
    cout << "��Χ: max: " << MinMax << " ,min: " << MinMin << endl;
    cout << "�������Ϊ: " << Min_MaxIndex << " ,������: " << Min_MaxCounts << "��" << endl;
}
