#include "ViewUI.h"
#include <iostream>
using namespace std;

void CViewUI::input(char * data, int maxLen)
{
    clearStream();
    cin.getline(data,maxLen); //ø…“‘∂¡»ÎmaxLen-1
}

void CViewUI::newLine()
{
    cout << endl;
}

void CViewUI::clearStream()
{
    cin.clear();
    cin.sync();
    rewind(stdin);
}

void CViewUI::clearScreen()
{
    system("cls");
}

void CViewUI::pause()
{
    system("pause");
}


