#pragma once
#include "MyString.h"

template<typename KEY>
class Hash
{
public:
    int operator()(const KEY& key)
    {
        return key;
    }
};

//模板特化
template<>
class Hash<CMyString>
{
public:
    unsigned int operator()(const CMyString& str)
    {
        const char *key = str.c_str();
        unsigned int res = 0;
        const unsigned int MULT = 31;
        while (*key)
        {
            res = MULT * res  + *key;
            key++;
        }
        return res;
    }
};

template<typename KEY,typename VALUE>
class HashTable
{
public:
    struct Node
    {
        KEY key;
        VALUE value;
        Node *next;
        Node(const KEY& key, const VALUE& value, Node *next = nullptr);
        ~Node();
    };
    
public:
    HashTable(int tableSize = 101);
    ~HashTable();
    void insert(const KEY& key,const VALUE& value);
    void remove(const KEY& key, const VALUE& value);
    void remove(const KEY& key);
    VALUE& operator[] (const KEY& key);
private:
    unsigned int hash(const KEY& key);
public:
    Node **hashTable;
    int tableSize;
    int size;
};

template<typename KEY,typename VALUE>
HashTable<KEY,VALUE>::Node::Node(const KEY& key, const VALUE& value, Node *next)
    :key(key),value(value),next(next)
{
}

template<typename KEY, typename VALUE>
HashTable<KEY, VALUE>::Node::~Node()
{
    if(next != nullptr)
        delete next;
    next = nullptr;
}

template<typename KEY, typename VALUE>
inline HashTable<KEY, VALUE>::HashTable(int tableSize)
    :tableSize(tableSize),size(0)
{
    hashTable = new Node*[tableSize];
    memset(hashTable,0,sizeof(Node*) * tableSize);
}

template<typename KEY, typename VALUE>
inline HashTable<KEY, VALUE>::~HashTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        if(hashTable[i] != nullptr)
            delete hashTable[i];
    }
    delete[] hashTable;
}

template<typename KEY, typename VALUE>
inline void HashTable<KEY, VALUE>::insert(const KEY & key, const VALUE & value)
{
    int index = hash(key);
    Node *newNode = new Node(key,value, hashTable[index]);
    hashTable[index] = newNode;
}

template<typename KEY, typename VALUE>
inline void HashTable<KEY, VALUE>::remove(const KEY & key, const VALUE & value)
{
    int index = hash(key);
    Node *node = hashTable[index];
    Node *fatherNode = node;
    while (node)
    {
        if (node->key == key)
        {
            if (fatherNode == node) //说明是第一个
            {
                fatherNode = node->next;
            }
            else
            {
                fatherNode->next = node->next;
            }
            node->next = nullptr;
            delete node;
            return;
        }
        fatherNode = node;
        node = node->next;
    }
}

template<typename KEY, typename VALUE>
inline void HashTable<KEY, VALUE>::remove(const KEY & key)
{
    int index = hash(key);
    if (hashTable[index] != nullptr)
    {
        delete hashTable[index];
        hashTable[index] = nullptr;
    }
}

template<typename KEY, typename VALUE>
inline VALUE & HashTable<KEY, VALUE>::operator[](const KEY & key)
{
    int index = hash(key);
    Node *node = hashTable[index];
    while (node)
    {
        if(node->key == key)
            return node->value;
        node = node->next;
    }
    //throw
}

template<typename KEY, typename VALUE>
inline unsigned int HashTable<KEY, VALUE>::hash(const KEY& key)
{
    static Hash<KEY> hashFun;
    return hashFun(key)%tableSize;
}
