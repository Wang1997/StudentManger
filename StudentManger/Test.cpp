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

void CTest::test1()
{
    cout << "��ʼ����hash����" << endl;
    const int size = 29989;
    //const int size = 39989;
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
