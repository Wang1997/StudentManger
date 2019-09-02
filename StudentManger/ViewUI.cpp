#include "ViewUI.h"
#include <cstdarg>
using namespace std;

void CViewUI::show(char * format, ...)
{
    char formatStr[100];
    va_list args;
    va_start(args, format);
    vsprintf(formatStr, format, args);
    va_end(args);

    cout << formatStr;

}

void CViewUI::input(char * data, int maxLen)
{
    clearStream();
    cin.getline(data,maxLen); //¿ÉÒÔ¶ÁÈëmaxLen-1
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


