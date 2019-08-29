#include<iostream>
#include "AVLTree.hpp"
using namespace std;

void show(int& elem, int height)
{
    cout << elem << "[" << height << "]" << "  ";
}


int main(int argc,char *argv[])
{
    AVLTree<int> tree;
    tree.insert(12);
    tree.insert(8);
    tree.insert(5);
    tree.insert(9);
    tree.insert(10);
    tree.insert(18);
    tree.insert(20);
    tree.insert(22);
    tree.insert(21);
    
    cout << "Ç°" << endl;
    tree.preOrder(show);
    cout << endl;
    cout << "ÖĞ" << endl;
    tree.inOrder(show);
    cout << endl;
    cout << "ºó" << endl;
    tree.postOrder(show);
    cout << endl;
    system("pause");
}