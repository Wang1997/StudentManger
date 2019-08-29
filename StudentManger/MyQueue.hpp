#pragma once

template <typename Object>
class MyQueue
{
private:
    struct Node
    {
        Object data;
        Node *next;
        Node(const Object& data = Object{}, Node *next = nullptr);
    };
public:
    MyQueue();
    ~MyQueue();

    void clear();
    bool empty();
    void size();
    
//operator
    void push(Object& obj);
    void pop();
    Object& back(); //ÄÃÎ²
    Object& front(); //ÄÃÍ·

private:
    Node *m_head;
    Node *m_tail;
    int m_size;
};

template<typename Object>
inline MyQueue<Object>::Node::Node(const Object & data, Node * next)
    :data(data), next(next)
{
}

template<typename Object>
inline MyQueue<Object>::MyQueue()
    :m_head(nullptr),m_tail(nullptr),m_size(0)
{
}

template<typename Object>
inline MyQueue<Object>::~MyQueue()
{
    clear();
}

template<typename Object>
inline void MyQueue<Object>::clear()
{
    while (!empty())
    {
        pop();
    }
}

template<typename Object>
inline bool MyQueue<Object>::empty()
{
    return (0 == m_size);
}

template<typename Object>
inline void MyQueue<Object>::size()
{
    return m_size;
}

template<typename Object>
inline void MyQueue<Object>::push(Object & obj)
{
    Node *newNode = new Node(obj,nullptr);
    if (empty())
    {
        m_tail = m_head = newNode;
    }
    else
    {
        m_tail->next = newNode;
        m_tail = newNode;
    }
    ++m_size;
}

template<typename Object>
inline void MyQueue<Object>::pop()
{
    if(empty())
        return;

    Node *delNode = m_head;
    m_head = m_head->next;
    delete delNode;
    --m_size;

    if(empty())
        m_tail = nullptr;
}

template<typename Object>
inline Object & MyQueue<Object>::back()
{
    return m_tail->data;
}

template<typename Object>
inline Object & MyQueue<Object>::front()
{
    return m_head->data;
}
