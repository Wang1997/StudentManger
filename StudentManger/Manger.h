#pragma once
#include"AVLTree.hpp"
#include "HashTable.hpp"
#include "Elem.h"
#include "Store.h"

class CManger
{
public:
    CManger();
    ~CManger();
    
    void start(); //开始
    void loadData(); //加载数据
    void initData(); //初始化新数据

    void menuControl();
    
private:
    AVLTree<CElem, TreeCompare<CElem>> m_TreeById;
    HashTable<CElem, Hash<CElem>> m_HashByName;
    HashTable<CPostion, Hash<CPostion>> m_HashByDelete;
    CStore m_store;
};

