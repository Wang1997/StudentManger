#include<iostream>
#include <fstream>
#include <time.h>
#include "AVLTree.hpp"
#include "HashTable.hpp"
#include "MyString.h"
using namespace std;

void show(int& elem, int height)
{
    cout << elem << "[" << height << "]" << "  ";
}

void test()
{
    AVLTree<int> tree;
    tree.insert(12);
    tree.insert(8);
    /*tree.insert(5);
    tree.insert(9);
    tree.insert(10);
    tree.insert(18);
    tree.insert(20);
    tree.insert(22);
    tree.insert(21);*/

    //tree.remove(10);
    tree.remove(12);
    cout << "ǰ" << endl;
    tree.preOrder(show);
    cout << endl;
    cout << "��" << endl;
    tree.inOrder(show);
    cout << endl;
    cout << "��" << endl;
    tree.postOrder(show);
    cout << endl;
}

void test1()
{
    //cout << "��ʼ����������" <<endl;
    //AVLTree<int> tree;
    //for (int i = 1; i <= 1000000; ++i)
    //{
    //    tree.insert(i);
    //}
    //cout << "��ʼ����hash����" << endl;
    //const int size = 29989;
    ////const int size = 39989;
    //srand(time(NULL));
    //char randomStr[] = "qwertyuyiiopasdfghjklzxcvbnmWERTYUIOPASDFGHJKKLZXCVBNM";
    //int randomStrLen = strlen(randomStr);
    //HashTable<CMyString,int> table(size);
    //for (int i = 1; i <= 1000000; ++i)
    //{
    //    int nameNum = rand() % 12 + 1;
    //    CMyString str;
    //    for (int i = 0; i < nameNum; ++ i)
    //    {
    //        str.append(randomStr[rand()% randomStrLen]);
    //    }
    //    table.insert(str,i);
    //}
    //cout << "hash���..��ʼд����" << endl;
    //ofstream tableOut;
    //tableOut.open("./hashTable.txt");
    //int totalNum = 0;
    //int maxNum = 0;
    //for (int i = 0; i < size; ++i)
    //{
    //    tableOut << i << " :";
    //    if (table.hashTable[i] != nullptr)
    //    {
    //        int num = 0;
    //        HashTable<CMyString, int>::Node *node = table.hashTable[i];
    //        while (node)
    //        {
    //            tableOut << node->key << "*" << node->value << " ";
    //            node = node->next;
    //            totalNum++;
    //            num++;
    //        }
    //        maxNum = MAX(maxNum,num);
    //    }
    //    tableOut << endl;
    //}
    //tableOut << "totalNum: " << totalNum << endl;
    //tableOut << "maxNum: " << maxNum << endl;
}

void test2()
{
    HashTable<int> hash(2);
    for(int i=1;i <= 4;++i)
        hash.insert(i);
    HashTable<int>::Iterator it = hash.begin(0);
    while (!it.isEnd())
    {
        cout << *it << endl;
        ++it;
    }
}


int main(int argc,char *argv[])
{
    test2();
    system("pause");
}