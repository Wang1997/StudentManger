#include<cstdlib>
#include <iostream>
#include "MyException.h"
using namespace std;

void fun()
{
    throw CMyInputException("输入长度过长");
}

int main(int argc,char *argv[])
{
    try 
    {
        fun();
    }
    catch (CMyException e)
    {
        cout << e.what();
    }
    system("pause");
}