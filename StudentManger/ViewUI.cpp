#include "ViewUI.h"
#include <iostream>
using namespace std;

void CViewUI::input(char * data, int maxLen)
{
    clear();
    cin.getline(data,maxLen); //���Զ���maxLen-1
}

void CViewUI::newLine()
{
    cout << endl;
}

void CViewUI::clear()
{
    cin.clear();
    cin.sync();
    rewind(stdin);
}


