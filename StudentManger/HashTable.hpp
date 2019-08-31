#pragma once
#include "MyFunction.h"

template<typename Object,typename KeyHash=Hash<Object>>
class HashTable
{
    friend CTest; //�ȿ��Ÿ�������,�������
private:
    struct Node
    {
        Object elem;
        Node *prev; //ǰָ�� ɾ������
        Node *next; //��ָ��
        Node(const Object& elem,Node *next = nullptr, Node *prev = nullptr);
        ~Node();
    };
public: //�õ��������ڱ�������
    class Iterator
    {
        friend HashTable;
    public:
        Object& operator* ();
        Iterator& operator++ ();
        Iterator& operator++ (int);
        //Iterator& operator-- ();
        //Iterator& operator-- (int);
        bool operator==(const Iterator& it);
        bool operator!=(const Iterator& it);
        bool isEnd(); //û�д�βָ��,�����ṩ�÷���
    private:
        Iterator(Node *current,int index); //˽�л�
    private:
        Node *current;
        int index;
    };
    
public:
    HashTable(int tableSize = 101);
    ~HashTable();
    void insert(const Object& elem); //����һ��Ԫ��
    void remove(const Object& elem); //ɾ��Ԫ��
    Iterator remove(Iterator it); //�Ƴ�һ��Ԫ��
    Iterator begin(const Object& elem);
    Iterator operator[] (const Object& elem);
private:
    unsigned int hash(const Object& elem);
    void releaseTable(Node *hashTableNode);
private:
    Node **hashTable;
    KeyHash keyHash;
    int tableSize;
    int size;
};

template<typename Object,typename KeyHash>
HashTable<Object, KeyHash>::Node::Node(const Object& elem,Node *next,Node *prev)
    :elem(elem) , prev(prev),next(next)
{
}

template<typename Object,typename KeyHash>
HashTable<Object, KeyHash>::Node::~Node()
{ //����̫��ݹ�����ջ���
/*    if(next != nullptr)
        delete next;
    next = nullptr;*/
}

template<typename Object,typename KeyHash>
inline HashTable<Object, KeyHash>::HashTable(int tableSize)
    :tableSize(tableSize),size(0)
{
    hashTable = new Node*[tableSize];
    memset(hashTable,0,sizeof(Node*) * tableSize);
}

template<typename Object,typename KeyHash>
inline HashTable<Object, KeyHash>::~HashTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        if(hashTable[i] != nullptr)
            releaseTable(hashTable[i]);
    }
    delete[] hashTable;
    hashTable = nullptr;
}

template<typename Object,typename KeyHash>
inline void HashTable<Object, KeyHash>::insert(const Object & elem)
{
    int index = hash(elem);
    Node *newNode = new Node(elem, hashTable[index]); //prevΪ nullptr
    if(hashTable[index] != nullptr)
        hashTable[index]->prev = newNode;
    hashTable[index] = newNode;
    size++;
}

template<typename Object, typename KeyHash>
inline void HashTable<Object, KeyHash>::remove(const Object & elem)
{
    int index = hash(elem);
    releaseTable(hashTable[index]);
    hashTable[index] = nullptr;
}

template<typename Object,typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator
        HashTable<Object, KeyHash>::remove(Iterator it)
{
    Node *p = it.current;
    Iterator retIt{p->next,it.index};
    if (p->prev == nullptr) //˵���ǵ�һ��
    {
        if(p->next != nullptr)
            p->next->prev = nullptr;
        hashTable[it.index] = p->next;
    }
    else
    {
        p->prev->next = p->next; //���ǵ�һ���϶���ǰ��
        if(p->next != nullptr)
            p->next->prev = p->prev;
    }
    --size;
    delete p;
    return retIt;
}

template<typename Object, typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator
        HashTable<Object, KeyHash>::begin(const Object & elem)
{
    int index = hash(elem);
    return { hashTable[index] , index};
}

template<typename Object,typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator 
        HashTable<Object, KeyHash>::operator[](const Object & elem)
{
    int index = hash(elem);
    return{ hashTable[index] , index };
}

template<typename Object,typename KeyHash>
inline unsigned int HashTable<Object, KeyHash>::hash(const Object& elem)
{
    return keyHash(elem)%tableSize;
}

template<typename Object,typename KeyHash>
inline void HashTable<Object, KeyHash>::releaseTable(Node * hashTableNode)
{
    while (hashTableNode)
    {
        Node *next = hashTableNode->next;
        delete hashTableNode;
        hashTableNode = next;
    }
}

template<typename Object, typename KeyHash>
HashTable<Object, KeyHash>::Iterator::Iterator(Node *current,int index)
    :current(current),index(index)
{
}

template<typename Object, typename KeyHash>
inline Object & HashTable<Object, KeyHash>::Iterator::operator*()
{
    return current->elem;
}

template<typename Object, typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator & 
        HashTable<Object, KeyHash>::Iterator::operator++()
{
    current = current->next;
    return *this;
}

template<typename Object, typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator &
        HashTable<Object, KeyHash>::Iterator::operator++(int)
{
    Iterator old = *this;
    ++(*this);
    return old;
}

template<typename Object, typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator & 
        HashTable<Object, KeyHash>::Iterator::operator--()
{
    current = current->prev;
    return *this;
}

template<typename Object, typename KeyHash>
inline typename HashTable<Object, KeyHash>::Iterator & 
            HashTable<Object, KeyHash>::Iterator::operator--(int)
{
    Iterator old = *this;
    --(*this);
    return old;
}

template<typename Object, typename KeyHash>
inline bool HashTable<Object, KeyHash>::Iterator::operator==(const Iterator & it)
{
    return current == it.current;
}

template<typename Object, typename KeyHash>
inline bool HashTable<Object, KeyHash>::Iterator::operator!=(const Iterator & it)
{
    return !(*this == it);
}

template<typename Object, typename KeyHash>
inline bool HashTable<Object, KeyHash>::Iterator::isEnd()
{
    return current == nullptr;
}
