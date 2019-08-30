#pragma once

/*
用于输入数据和界面交互
*/
class CViewUI
{
public:
    template<typename TYPE>
    static void show(TYPE& data,bool flag=false);
    template<typename TYPE>
    static void input(TYPE& data);
    static void input(char* data,int maxLen);
    static void newLine();
    static void clear();
};

template<typename TYPE>
void CViewUI::show(TYPE& data, bool flag)
{
    cout << data;
    if(flag)
        newLine();
}

template<typename TYPE>
inline void CViewUI::input(TYPE & data)
{
    clear();
    cin >> data;
}
