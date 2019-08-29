#pragma once
#include "MyStack.hpp"
#include "MyQueue.hpp"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

//AVL 非递归版实现
template<typename TYPE>
class AVLTree
{
    typedef void(*showFun)(TYPE& elem, int height); //打印回调
private:
    typedef struct Node
    {
        TYPE elem;
        Node *left;
        Node *right;
        Node *father; //父亲节点
        int height;
        Node(const TYPE& elem=TYPE{}, Node *father=nullptr,Node *left=nullptr,
                Node *right = nullptr,int height = 0);
    }*PNode;

public:
    AVLTree();
    ~AVLTree();
    
    bool empty() const;
    TYPE& findMin() const;
    TYPE& findMax() const;
    void insert(const TYPE& elem); //插入元素
    void remove(const TYPE& elem); //移除元素

    void preOrder(showFun fun) const; //前序
    void inOrder(showFun fun) const; //中序
    void postOrder(showFun fun) const; //后序
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    PNode find(PNode tree,const TYPE& elem) const;
    void insert(PNode tree, const TYPE& elem);
    void remove(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //获取高度
    int calcHeight(PNode tree) const; //计算高度
    PNode rotateByLeft(PNode tree); //左边旋
    PNode rotateByRight(PNode tree); //右边旋
    PNode rotateByDoubleLeft(PNode tree); //左双旋
    PNode rotateByDoubleRight(PNode tree); //右双旋
    void balance(PNode tree); //从该节点一直往上平衡

private:
    PNode root;
    static const int BF = 2;
};

template<typename TYPE>
inline AVLTree<TYPE>::Node::Node(const TYPE& elem = TYPE{}, Node *father = nullptr, Node *left = nullptr,
    Node *right = nullptr, int height = 0)
    :elem(elem),father(father),left(left),right(right),height(height)
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
        if (top->left != nullptr)
            queue.push(top->left);
        else if (top->right != nullptr)
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
inline void AVLTree<TYPE>::remove(const TYPE & elem)
{
    remove(root,elem);
}

template<typename TYPE>
inline void AVLTree<TYPE>::preOrder(showFun fun) const
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

template<typename TYPE>
inline void AVLTree<TYPE>::inOrder(showFun fun) const
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

template<typename TYPE>
inline void AVLTree<TYPE>::postOrder(showFun fun) const
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
inline void AVLTree<TYPE>::remove(PNode tree, const TYPE & elem)
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
        else //相等
        {
            
            if (tree->left != nullptr && tree->right != nullptr)
            {
                PNode minNode = findMin(tree->right);
                tree->elem = minNode->elem;
                tree = minNode; //换成删除minNode
            }
            
            PNode delNode = tree;
            if (tree == root)
            {
                root = (tree->left != nullptr) ? tree->left : tree->right;
                root->father = nullptr;
                delete delNode;
                balance(root);
                return;
            }
            else
            {
                PNode father = tree->father;
                if (father->left == tree)
                {
                    father->left =
                        (tree->left != nullptr) ? tree->left : tree->right;
                }
                else
                {
                    father->right =
                        (tree->left != nullptr) ? tree->left : tree->right;
                }
                delete delNode;
                balance(father);
                return;
            }
        }
    }
}

template<typename TYPE>
inline int AVLTree<TYPE>::getHeight(PNode tree) const
{
    if (tree == nullptr)
        return -1; //叶子为0,使用null为-1

    return tree->height;
}

template<typename TYPE>
inline int AVLTree<TYPE>::calcHeight(PNode tree) const
{
    return MAX(getHeight(tree->left), getHeight(tree->right)) + 1;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateByLeft(PNode tree)
{
    PNode rotateNode = tree->left;
    //修正tree与rotateNode->right
    tree->left = rotateNode->right;
    if (rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //修正tree->father与rotateNode
    rotateNode->father = tree->father;
    if (tree->father == nullptr)
        root = rotateNode;
    else if (tree == tree->father->right)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //修正tree与rotateNode
    tree->father = rotateNode;
    rotateNode->right = tree;
    
    //修正高度
    tree->height = calcHeight(tree);
    rotateNode->height = calcHeight(rotateNode);

    return rotateNode;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateByRight(PNode tree)
{
    PNode rotateNode = tree->right;
    //修正rotateNode->right与tree的关联
    tree->right = rotateNode->left;
    if (rotateNode->left != nullptr)
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

    //计算高度
    tree->height = calcHeight(tree);
    rotateNode->height = calcHeight(rotateNode);

    return rotateNode;
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateByDoubleLeft(PNode tree)
{
    rotateByRight(tree->left);
    return rotateByLeft(tree);
}

template<typename TYPE>
inline typename AVLTree<TYPE>::PNode AVLTree<TYPE>::rotateByDoubleRight(PNode tree)
{
    rotateByLeft(tree->right);
    return rotateByRight(tree);
}

template<typename TYPE>
inline void AVLTree<TYPE>::balance(PNode tree)
{
    while (tree)
    {
        tree->height = calcHeight(tree);

        int leftHeight = getHeight(tree->left);
        int rightHeight = getHeight(tree->right);
        if (abs(leftHeight - rightHeight) > BF) //需要平衡
        {            
            if (leftHeight > rightHeight) //左旋
            {
                if (getHeight(tree->left->left) >= getHeight(tree->left->right))
                {//左左
                    tree = rotateByLeft(tree);
                }
                else
                {//左右
                    tree = rotateByDoubleLeft(tree);
                }
            }
            else //右旋
            {
                if (getHeight(tree->right->right) >= getHeight(tree->right->left))
                {//右右
                    tree = rotateByRight(tree);
                }
                else
                {//右左
                    tree = rotateByDoubleRight(tree);
                }
            }
        }
        tree = tree->father; //指向父亲平衡
    }
}
