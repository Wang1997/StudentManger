#pragma once
#include "MyStack.hpp"
#include "MyQueue.hpp"
#include "MyFunction.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

class CTest;

//AVL �ǵݹ��ʵ�� ��֧���ظ�����
template<typename TYPE,typename KeyCompare = TreeCompare<TYPE>>
class AVLTree
{
    friend CTest; //�ȿ��Ÿ�������,�������
    typedef void(*showFun)(TYPE& elem, int height); //��ӡ�ص�
private:
    typedef struct Node
    {
        TYPE elem;
	    Node *father; //���׽ڵ�
        Node *left;
        Node *right;
        int height;

        Node *prev; //ǰһ���ڵ�
        Node *next; //��һ���ڵ�

        Node(const TYPE& elem=TYPE{}, Node *father=nullptr,Node *left=nullptr,
                Node *right = nullptr,int height = 0, Node *prev = nullptr,Node *next=nullptr);
    }*PNode;

public: //�õ��������ڱ����ظ�Ԫ�ص�����
    class Iterator
    {
        friend AVLTree;
    public:
        TYPE& operator* ();
        Iterator& operator++ ();
        Iterator& operator++ (int);
        bool operator==(const Iterator& it);
        bool operator!=(const Iterator& it);
        bool isEnd(); //û�д�βָ��,�����ṩ�÷���
    public:
        Iterator();
    private:
        Iterator(PNode current); //˽�л�
    private:
        PNode current;
    };

public:
    AVLTree();
    ~AVLTree();
    
    bool empty() const;
    TYPE& findMin() const;
    TYPE& findMax() const;
    Iterator find(const TYPE& elem); //����
    void insert(const TYPE& elem); //����Ԫ��
    void insert_unique(const TYPE& elem);
    void insert_equal(const TYPE& elem);
    void remove(const TYPE& elem); //�Ƴ�Ԫ��
    Iterator remove(Iterator it);
    void remove_all(const TYPE& elem);

    void preOrder(showFun fun) const; //ǰ��
    void inOrder(showFun fun) const; //����
    void postOrder(showFun fun) const; //����
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    //PNode find(PNode tree,const TYPE& elem) const;
    void addNode(const TYPE & elem, PNode fatherNode = nullptr, bool dirFlag = true);
    void insert_(PNode tree, const TYPE & elem,bool repeatFlag = false);
    void insert(PNode tree, const TYPE& elem);
    void remove_(PNode tree);
    void remove(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //��ȡ�߶�
    int calcHeight(PNode tree) const; //����߶�
    PNode rotateByLeft(PNode tree); //�����
    PNode rotateByRight(PNode tree); //�ұ���
    PNode rotateByDoubleLeft(PNode tree); //��˫��
    PNode rotateByDoubleRight(PNode tree); //��˫��
    void balance(PNode tree); //�Ӹýڵ�һֱ����ƽ��
    
    void releaseNode(PNode node); //�ͷŽڵ�
    void replaceNode(PNode needReplacedNode,PNode pNode);//�滻�ڵ�
private:
    PNode root;
    KeyCompare keyCompare;
    static const int BF = 1;
};

template<typename TYPE, typename KeyCompare>
inline AVLTree<TYPE, KeyCompare>::Node::Node(const TYPE& elem, Node *father, Node *left,
    Node *right, int height,Node *prev,Node *next)
    :elem(elem),father(father),left(left),right(right),height(height), prev(prev),next(next)
{}

template<typename TYPE, typename KeyCompare>
inline AVLTree<TYPE, KeyCompare>::AVLTree()
    :root(nullptr)
{}

template<typename TYPE, typename KeyCompare>
inline AVLTree<TYPE, KeyCompare>::~AVLTree()
{
    if(root == nullptr)
        return;

    MyQueue<PNode> queue;
    queue.push(root);
    while (!queue.empty())
    {
        PNode top = queue.front();
        queue.pop();
        if (top->left != nullptr)
            queue.push(top->left);
        else if (top->right != nullptr)
            queue.push(top->right);
        delete top;
        top = nullptr;
    }
    root = nullptr;
}

template<typename TYPE, typename KeyCompare>
inline bool AVLTree<TYPE, KeyCompare>::empty() const
{
    return (nullptr == root);
}

template<typename TYPE, typename KeyCompare>
inline TYPE& AVLTree<TYPE, KeyCompare>::findMin() const
{
    return findMin(root)->elem;
}

template<typename TYPE, typename KeyCompare>
inline TYPE& AVLTree<TYPE, KeyCompare>::findMax() const
{
    return findMax(root)->elem;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator 
        AVLTree<TYPE, KeyCompare>::find(const TYPE & elem)
{
    PNode tree = root;
    while (tree)
    {
        if (keyCompare(elem,tree->elem) > 0)
        {
            tree = tree->right;
        }
        else if (keyCompare(elem, tree->elem) < 0)
        {
            tree = tree->left;
        }
        else
            break;
    }

    return {tree};
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::insert(const TYPE& elem)
{
    insert(root,elem);
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::insert_unique(const TYPE & elem)
{
    insert_(root,elem);
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::insert_equal(const TYPE & elem)
{
    insert_(root,elem,true);
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::remove(const TYPE & elem)
{
    remove(root,elem);
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator 
    AVLTree<TYPE, KeyCompare>::remove(Iterator it)
{
    PNode node = it.current;
    Iterator resIt = {node->next};
    if (node->prev == nullptr && node->next == nullptr) //ֻ��һ���ڵ�
    {
        remove_(node);
    }
    else if(node->prev == nullptr) //˵���ǵ�һ��
    {
        PNode next = node->next; //�϶��к��
        //��������
        next->father = node->father;
        next->left = node->left;
        next->right = node->right;
        next->height = node->height;
        next->prev = nullptr;
        //���׹���
        if (node->father == nullptr)
        {
            root = next;
        }
        else
        {
            if(node->father->left == node)
                node->father->left = next;
            else
                node->father->right = next;
        }
        //���ӹ���
        if (node->left != nullptr)
        {
            node->left->father = next;
        }
        if (node->right != nullptr)
        {
            node->right->father = next;
        }
        delete node;
    }
    else
    {
        node->prev->next = node->next;
        if(node->next != nullptr)
            node->next->prev = node->prev;
        delete node;
    }
    return resIt;
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::remove_all(const TYPE & elem)
{
    Iterator it = find(elem);
    remove_(it.current);
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::preOrder(showFun fun) const
{
    PNode theNode = root;
    MyStack<PNode> stack;
    while (theNode || !stack.empty())
    {
        while (theNode)
        {
            fun(theNode->elem, theNode->height);
            stack.push(theNode);
            theNode = theNode->left;
        }
        PNode top = stack.top();
        stack.pop();
        if (top->right != nullptr)
            theNode = top->right;
    }
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::inOrder(showFun fun) const
{
    PNode theNode = root;
    MyStack<PNode> stack;
    while (theNode || !stack.empty())
    {
        while (theNode)
        {
            stack.push(theNode);
            theNode = theNode->left;
        }
        PNode top = stack.top();
        stack.pop();
        fun(top->elem, top->height);
        if (top->right != nullptr)
            theNode = top->right;
    }
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::postOrder(showFun fun) const
{
    PNode theNode = root;
    PNode lastNode = root;
    MyStack<PNode> stack;
    while (theNode || !stack.empty())
    {
        while (theNode)
        {
            stack.push(theNode);
            theNode = theNode->left;
        }
        PNode top = stack.top();
        if (top->right == nullptr || top->right == lastNode)
        {
            fun(top->elem, top->height);
            stack.pop();
            lastNode = top;
        }
        else
        {
            theNode = top->right;
        }
    }
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::findMin(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while(tree->left)
        tree = tree->left;

    return tree;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::findMax(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while (tree->right)
        tree = tree->right;

    return tree;
}
/*
template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::find(PNode tree,const TYPE& elem) const
{
    if(tree == nullptr)
        return nullptr;
    while (tree)
    {
        if (elem > tree->elem)
        {
            tree = tree->right;
        }
        else if(elem < tree->elem)
        {
            tree = tree->left;
        }
        else
            break;
    }
    return tree;
}*/

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::addNode(const TYPE & elem, PNode fatherNode, bool dirFlag)
{
    PNode newNode = new Node(elem, fatherNode);
    if (fatherNode == nullptr)
    {
        root = newNode;
        return;
    }

    if (dirFlag)
        fatherNode->right = newNode;
    else
        fatherNode->left = newNode;

    return;
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::insert_(PNode tree, const TYPE & elem, bool repeatFlag)
{
    if (tree == nullptr)
    {
        addNode(elem);
        return;
    }

    PNode fatherNode = nullptr;
    bool dirFlag = true;
    while (tree)
    {
        fatherNode = tree;
        if (keyCompare(elem, tree->elem) > 0)
        {
            dirFlag = true;
            tree = tree->right;
        }
        else if (keyCompare(elem, tree->elem) < 0)
        {
            dirFlag = false;
            tree = tree->left;
        }
        else //�ظ�Ԫ
        {
            if (repeatFlag) //���ظ��ڵ�� next
            {
                PNode newNode = new Node(elem);
                newNode->next = tree->next;
                if (tree->next != nullptr)
                {
                    tree->next->prev = newNode;
                }
                newNode->prev = tree;
                tree->next = newNode;
            }
            /*else
            {
                throw CMyRepeatException("���ظ�Ԫ");
            }*/
            return; 
        }
    }

    addNode(elem, fatherNode, dirFlag);

    balance(fatherNode); //�Ӹø��ڵ㿪ʼƽ��
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::insert(PNode tree, const TYPE & elem)
{
    if (tree == nullptr)
    {
        addNode(elem);
        return;
    }

    PNode fatherNode = nullptr;
    bool dirFlag = true;
    while (tree)
    {
        fatherNode = tree;
        if (elem > tree->elem)
        {
            dirFlag = true;
            tree = tree->right;
        }
        else if (elem < tree->elem)
        {
            dirFlag = false;
            tree = tree->left;
        }
        else
        {
            return;  //�����ظ�Ԫ return
        } 
    }
    
    addNode(elem, fatherNode,dirFlag);

    balance(fatherNode); //�Ӹø��ڵ㿪ʼƽ��
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::remove_(PNode tree)
{
    if(tree == nullptr)
        return;

    if (tree->left != nullptr && tree->right != nullptr)
    {
        PNode minNode = findMin(tree->right);
        replaceNode(tree, minNode);
        tree = minNode; //����ɾ��minNode
    }

    PNode delNode = tree;
    if (tree == root)
    {
        root = (tree->left != nullptr) ? tree->left : tree->right;
        if(root != nullptr)
            root->father = nullptr;
        releaseNode(delNode);
        balance(root);
    }
    else
    {
        PNode father = tree->father;
        PNode child = 
            (tree->left != nullptr) ? tree->left : tree->right;
        if (father->left == tree)
        {
            father->left = child;
        }
        else
        {
            father->right = child;
        }
        if(child != nullptr)
            child->father = father;
        releaseNode(delNode);
        balance(father);
    }
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::remove(PNode tree, const TYPE & elem)
{
    while (tree)
    {
        if (elem > tree->elem)
        {
            tree = tree->right;
        }
        else if (elem < tree->elem)
        {
            tree = tree->left;
        }
        else //���
        {
            remove_(tree);
            return;
        }
    }
}

template<typename TYPE, typename KeyCompare>
inline int AVLTree<TYPE, KeyCompare>::getHeight(PNode tree) const
{
    if (tree == nullptr)
        return -1; //Ҷ��Ϊ0,ʹ��nullΪ-1

    return tree->height;
}

template<typename TYPE, typename KeyCompare>
inline int AVLTree<TYPE, KeyCompare>::calcHeight(PNode tree) const
{
    return MAX(getHeight(tree->left), getHeight(tree->right)) + 1;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::rotateByLeft(PNode tree)
{
    PNode rotateNode = tree->left;
    //����tree��rotateNode->right
    tree->left = rotateNode->right;
    if (rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //����tree->father��rotateNode
    rotateNode->father = tree->father;
    if (tree->father == nullptr)
        root = rotateNode;
    else if (tree == tree->father->right)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //����tree��rotateNode
    tree->father = rotateNode;
    rotateNode->right = tree;
    
    //�����߶�
    tree->height = calcHeight(tree);
    rotateNode->height = calcHeight(rotateNode);

    return rotateNode;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::rotateByRight(PNode tree)
{
    PNode rotateNode = tree->right;
    //����rotateNode->right��tree�Ĺ���
    tree->right = rotateNode->left;
    if (rotateNode->left != nullptr)
        rotateNode->left->father = tree;
    //����rotateNode �� tree->father
    rotateNode->father = tree->father;
    if (tree->father == nullptr)
        root = rotateNode;
    else if (tree == tree->father->right)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //����rotateNode �� tree �Ĺ�ϵ
    rotateNode->left = tree;
    tree->father = rotateNode;

    //����߶�
    tree->height = calcHeight(tree);
    rotateNode->height = calcHeight(rotateNode);

    return rotateNode;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::rotateByDoubleLeft(PNode tree)
{
    rotateByRight(tree->left);
    return rotateByLeft(tree);
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::PNode AVLTree<TYPE, KeyCompare>::rotateByDoubleRight(PNode tree)
{
    rotateByLeft(tree->right);
    return rotateByRight(tree);
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::balance(PNode tree)
{
    while (tree)
    {
        tree->height = calcHeight(tree);

        int leftHeight = getHeight(tree->left);
        int rightHeight = getHeight(tree->right);
        if (abs(leftHeight - rightHeight) > BF) //��Ҫƽ��
        {            
            if (leftHeight > rightHeight) //����
            {
                if (getHeight(tree->left->left) >= getHeight(tree->left->right))
                {//����
                    tree = rotateByLeft(tree);
                }
                else
                {//����
                    tree = rotateByDoubleLeft(tree);
                }
            }
            else //����
            {
                if (getHeight(tree->right->right) >= getHeight(tree->right->left))
                {//����
                    tree = rotateByRight(tree);
                }
                else
                {//����
                    tree = rotateByDoubleRight(tree);
                }
            }
        }
        tree = tree->father; //ָ����ƽ��
    }
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::releaseNode(PNode node)
{
    while (node)
    {
        Node *next = node->next;
        delete node;
        node = next;
    }
}

template<typename TYPE, typename KeyCompare>
inline void AVLTree<TYPE, KeyCompare>::replaceNode(PNode needReplacedNode, PNode pNode)
{
    needReplacedNode->elem = pNode->elem; //�滻Ԫ��

    PNode nextTemp = needReplacedNode->next;

    needReplacedNode->next = pNode->next;
    if(needReplacedNode->next != nullptr)
        needReplacedNode->next->prev = needReplacedNode; //����ǰ��
    
    pNode->next = nextTemp;
    if (pNode->next != nullptr)
        pNode->next->prev = pNode;//����ǰ��
}

template<typename TYPE, typename KeyCompare>
AVLTree<TYPE, KeyCompare>::Iterator::Iterator(PNode current)
    :current(current)
{
}

template<typename TYPE, typename KeyCompare>
inline TYPE & AVLTree<TYPE, KeyCompare>::Iterator::operator*()
{
    return current->elem;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator &
AVLTree<TYPE, KeyCompare>::Iterator::operator++()
{
    current = current->next;
    return *this;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator &
AVLTree<TYPE, KeyCompare>::Iterator::operator++(int)
{
    Iterator old = *this;
    ++(*this);
    return old;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator &
AVLTree<TYPE, KeyCompare>::Iterator::operator--()
{
    current = current->prev;
    return *this;
}

template<typename TYPE, typename KeyCompare>
inline typename AVLTree<TYPE, KeyCompare>::Iterator &
AVLTree<TYPE, KeyCompare>::Iterator::operator--(int)
{
    Iterator old = *this;
    --(*this);
    return old;
}

template<typename TYPE, typename KeyCompare>
inline bool AVLTree<TYPE, KeyCompare>::Iterator::operator==(const Iterator & it)
{
    return current == it.current;
}

template<typename TYPE, typename KeyCompare>
inline bool AVLTree<TYPE, KeyCompare>::Iterator::operator!=(const Iterator & it)
{
    return !(*this == it);
}

template<typename TYPE, typename KeyCompare>
inline bool AVLTree<TYPE, KeyCompare>::Iterator::isEnd()
{
    return current == nullptr;
}

template<typename TYPE, typename KeyCompare>
inline AVLTree<TYPE, KeyCompare>::Iterator::Iterator()
    :current(nullptr)
{
}
