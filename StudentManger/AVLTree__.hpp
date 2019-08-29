#pragma once
#include "MyStack.hpp"
#include "MyQueue.hpp"

//AVL 非递归版实现
template<typename TYPE>
class AVLTree
{
    typedef void(*showFun)(TYPE& elem, int diffHeight, int deep); //打印回调
private:
    typedef struct Node
    {
        TYPE elem;
        Node *left;
        Node *right;
        Node *father; //父亲节点
        int diffHeight; //存放高度差
        Node(const TYPE& elem=TYPE{}, Node *father=nullptr,Node *left=nullptr,
                Node *right = nullptr,int diffHeight = 0);
    }*PNode;

public:
    AVLTree();
    ~AVLTree();
    
    bool empty() const;
    TYPE& findMin() const;
    TYPE& findMax() const;
    void insert(const TYPE& elem); //插入元素

    void preOrder(showFun fun) const; //前序
    void inOrder(showFun fun) const; //中序
    void postOrder(showFun fun) const; //后序
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    PNode find(PNode tree,const TYPE& elem) const;
    void insert(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //获取高度差
    int calcHeight(PNode tree) const; //计算高度差
    void calcHeightWithLeft(PNode tree); //重新计算高度差(左边旋)
    void calcHeightWithRight(PNode tree); //重新计算高度差(右边旋)
    PNode rotateWithLeft(PNode tree); //左边旋
    PNode rotateWithRight(PNode tree); //右边旋
    PNode rotateWithDoubleLeft(PNode tree); //左双旋
    PNode rotateWithDoubleRight(PNode tree); //右双旋
    void balance(PNode tree); //从该节点一直往上平衡

private:
    PNode root;
    static const int BF = 1;
};

template<typename TYPE>
inline AVLTree<TYPE>::Node::Node(const TYPE& elem = TYPE{}, Node *father = nullptr, Node *left = nullptr,
    Node *right = nullptr, int diffHeight = 0)
    :elem(elem),father(father),left(left),right(right),diffHeight(diffHeight)
{}

template<typename TYPE>
inline AVLTree<TYPE>::AVLTree()
    :root(nullptr)
{}

template<typename TYPE>
inline AVLTree<TYPE>::~AVLTree()
{
    MyQueue<PNode> queue;
    queue.push(root);
    while (!queue.empty())
    {
        PNode top = queue.front();
        queue.pop();
        if(top->left != nullptr)
            queue.push(top->left);
        else if(top->right != nullptr)
            queue.push(top->right);
        delete top;
        top = nullptr;
    }
    root = nullptr;
}

template<typename TYPE>
inline bool AVLTree<TYPE>::empty() const
{
    return (nullptr == root);
}

template<typename TYPE>
inline TYPE& AVLTree<TYPE>::findMin() const
{
    return findMin(root)->elem;
}

template<typename TYPE>
inline TYPE& AVLTree<TYPE>::findMax() const
{
    return findMax(root)->elem;
}

template<typename TYPE>
inline void AVLTree<TYPE>::insert(const TYPE& elem)
{
    insert(root,elem);
}

template<typename TYPE>
inline void AVLTree<TYPE>::preOrder(showFun fun) const
{
    PNode theNode = root;
    MyStack<PNode> stack;
    int deep = 0;
    while (theNode || !stack.empty())
    {
        while (theNode)
        {
            fun(theNode->elem,theNode->diffHeight, deep);
            stack.push(theNode);
            theNode = theNode->left;
            deep++;
        }
        PNode top = stack.top();
        stack.pop();
        if(top->right != nullptr)
            theNode = top->right;
        else
            deep--;
    }
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::findMin(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while(tree->left)
        tree = tree->left;

    return tree;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::findMax(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while (tree->right)
        tree = tree->right;

    return tree;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::find(PNode tree,const TYPE& elem) const
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
}

template<typename TYPE>
inline void AVLTree<TYPE>::insert(PNode tree, const TYPE & elem)
{
    PNode newNode = new Node(elem);
    if (tree == nullptr)
    {
        root = newNode;
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
            delete newNode;
            return;  //出现重复元 return
        } 
    }
    
    if(dirFlag)
        fatherNode->right = newNode;
    else
        fatherNode->left = newNode;
    
    newNode->father = fatherNode;
    
    balance(fatherNode); //从该父节点开始平衡
}

template<typename TYPE>
inline int AVLTree<TYPE>::getHeight(PNode tree) const
{
    if (tree == nullptr)
        return -1;

    return tree->diffHeight;
}

// 这里高度差计算有问题！！先使用旧方法
template<typename TYPE>
inline int AVLTree<TYPE>::calcHeight(PNode tree) const
{
    if (tree->left != nullptr && tree->right != nullptr)
    {
        int leftH = abs(tree->left->diffHeight);
        int rightH = abs(tree->right->diffHeight);
        return leftH - rightH;
    }
    else
    {
        if (tree->left == nullptr && tree->right == nullptr)
        {
            return 0;
        }
        else if (tree->left == nullptr)
        {
            return (abs(tree->right->diffHeight) + 1) * -1;
        }
        else
        {
            return abs(tree->left->diffHeight) + 1;
        }
    }
}

template<typename TYPE>
inline void AVLTree<TYPE>::calcHeightWithLeft(PNode tree)
{
    int& Tk1 = tree->right->diffHeight;
    int& Tk2 = tree->diffHeight;
    //先更新TK1
    if(Tk2 >= 0)
        Tk1 -= (Tk2 + 1);
    else
        --Tk1;
    //再更新TK2
    if (Tk1 >= 0)
        --Tk2;
    else
        Tk2 += Tk1 - 1;
}

template<typename TYPE>
inline void AVLTree<TYPE>::calcHeightWithRight(PNode tree)
{
    int& Tk1 = tree->left->diffHeight;
    int& Tk2 = tree->diffHeight;
    //先更新TK1
    if(Tk2 >= 0)
        ++Tk1;
    else
        Tk1 += (1-Tk2);
    //再更新TK2
    if (Tk1 >= 0)
        Tk2 += Tk1 + 1;
    else
        ++Tk2;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateWithLeft(PNode tree)
{
    PNode rotateNode = tree->left;
    //修正tree与rotateNode->right
    tree->left = rotateNode->right;
    if(rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //修正tree->father与rotateNode
    rotateNode->father = tree->father;
    if(tree->father == nullptr)
        root = rotateNode;
    else if (tree == tree->father->right)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //修正tree与rotateNode
    tree->father = rotateNode;
    rotateNode->right = tree;
    
    //修正高度差
    calcHeightWithLeft(rotateNode);
    
    return rotateNode;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateWithRight(PNode tree)
{
    PNode rotateNode = tree->right;
    //修正rotateNode->right与tree的关联
    tree->right = rotateNode->left;
    if(rotateNode->left != nullptr)
        rotateNode->left->father = tree;
    //修正rotateNode 与 tree->father
    rotateNode->father = tree->father;
    if (tree->father == nullptr)
        root = rotateNode;
    else if (tree == tree->father->right)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //修正rotateNode 与 tree 的关系
    rotateNode->left = tree;
    tree->father = rotateNode;

    //修正高度差
    calcHeightWithRight(rotateNode);

    return rotateNode;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateWithDoubleLeft(PNode tree)
{
    rotateWithRight(tree->left);
    return rotateWithLeft(tree);
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateWithDoubleRight(PNode tree)
{
    rotateWithLeft(tree->right);
    return rotateWithRight(tree);
}

template<typename TYPE>
inline void AVLTree<TYPE>::balance(PNode tree)
{
    while (tree)
    {
       tree->diffHeight = calcHeight(tree);

        if (abs(tree->diffHeight) > BF) //需要平衡
        {            
            if (tree->diffHeight > 0) //左边旋
            {
                if (tree->left->diffHeight > 0)
                {//左左
                    tree = rotateWithLeft(tree);
                }
                else
                {//左右
                    tree = rotateWithDoubleLeft(tree);
                }
            }
            else //右边旋
            {
                if (tree->right->diffHeight < 0)
                {//右右
                    tree = rotateWithRight(tree);
                }
                else
                {//右左
                    tree = rotateWithDoubleRight(tree);
                }
            }
        }
        tree = tree->father; //指向父亲平衡
    }
}