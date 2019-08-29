
template<typename Object>
class MyStack
{
private:
    struct Node
    {
        Object data;
        Node *next;
        Node(const Object& data=Object{},Node *next=nullptr);
    };
public:
    MyStack();
    ~MyStack();
    
    bool empty() const;
    int size() const;
    void clear();
//operator
    void push(Object& obj);
    Object& top();
    void pop();

private:
    Node *m_node; //链表的头部模拟栈的一端
    int m_size;
};

template<typename Object>
inline MyStack<Object>::Node::Node(const Object & data, Node * next)
    :data(data),next(next)
{
}

template<typename Object>
inline MyStack<Object>::MyStack()
    :m_node(nullptr), m_size(0)
{
}

template<typename Object>
inline MyStack<Object>::~MyStack()
{
    clear();
}

template<typename Object>
inline bool MyStack<Object>::empty() const
{
    return (0 == m_size);
}

template<typename Object>
inline int MyStack<Object>::size() const
{
    return m_size;
}

template<typename Object>
inline void MyStack<Object>::clear()
{
    while (!empty())
    {
        pop();
    }
}

template<typename Object>
inline void MyStack<Object>::push(Object & obj)
{
    Node *newNode = new Node(obj, m_node);
    m_node = newNode;
    ++m_size;
}

template<typename Object>
inline Object & MyStack<Object>::top()
{
    return m_node->data;
}

template<typename Object>
inline void MyStack<Object>::pop()
{
    if(empty())
        return;

    Node *delNode = m_node;
    m_node = m_node->next;
    delete delNode;
    --m_size;
}


