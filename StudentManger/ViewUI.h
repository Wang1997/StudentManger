#pragma once
#include <iostream>

/*
用于输入数据和界面交互
*/
class CViewUI
{
public:
    template<typename TYPE>
    static void show(TYPE& data);
    static void show(char* format, ...);
    template<typename TYPE>
    static TYPE input();
    static void input(char* data,int maxLen);
    static void newLine();
    static void clearStream();
    static void clearScreen();
    static void pause();
};

template<typename TYPE>
void CViewUI::show(TYPE& data)
{
    std::cout << data;
}

template<typename TYPE>
inline TYPE CViewUI::input()
{
    clearStream();
    TYPE data;
    std::cin >> data;
    return data;
}
