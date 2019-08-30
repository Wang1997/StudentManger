#include<cstdlib>
#include <iostream>
#include "MyException.h"
#include "ViewUI.h"
using namespace std;

void fun()
{
    throw CMyInputException("输入长度过长");
}

int main(int argc,char *argv[])
{
    int i = 10;
    int j = 10;
    char str[20];
    CViewUI::input(str,5);
    CViewUI::input(i);
    CViewUI::show(i);
    CViewUI::show(str);
    CViewUI::show("...");
    system("pause");
}