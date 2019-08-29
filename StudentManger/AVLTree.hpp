#pragma once

//AVL 非递归版实现
template<typename TYPE>
class AVLTree
{
    typedef void(*showFun)(TYPE& elem, int height, int deep); //打印回调
private:
    typedef struct Node
    {
        TYPE elem;
        Node *left;
        Node *right;
        Node *father; //父亲节点
        int height; //存放高度差
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
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    PNode find(PNode tree,const TYPE& elem) const;
    void insert(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //获取高度差
    int calcHeight(PNode tree) const; //计算高度差
    void calcHeightWithLeft(PNode tree); //重新计算高度差(左边旋)
    void calcHeightWithRight(PNode tree); //重新计算高度差(右边旋)
    void rotateWithLeft(PNode tree); //左边旋
    void rotateWithRight(PNode tree); //右边旋
    void rotateWithDoubleLeft(PNode tree); //左双旋
    void rotateWithDoubleRight(PNode tree); //右双旋
    void balance(PNode tree); //从该节点一直往上平衡

private:
    PNode root;
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
    //TODO
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

    return tree->height;
}

template<typename TYPE>
inline int AVLTree<TYPE>::calcHeight(PNode tree) const
{
    return getHeight(tree->left) - getHeight(tree->right);
}

template<typename TYPE>
inline void AVLTree<TYPE>::calcHeightWithLeft(PNode tree)
{
    int& Tk1 = tree->right->height;
    int& Tk2 = tree->height;
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
    int& Tk1 = tree->left->height;
    int& Tk2 = tree->height;
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
inline void AVLTree<TYPE>::rotateWithLeft(PNode tree)
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
    else if (tree->elem > tree->father->elem)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //修正tree与rotateNode
    tree->father = rotateNode;
    rotateNode->right = tree;
    
    //修正高度差
    calcHeightWithLeft(rotateNode);
}

template<typename TYPE>
inline void AVLTree<TYPE>::rotateWithRight(PNode tree)
{
    PNode rotateNode = tree->right;
    //修正rotateNode->right与tree的关联
    tree->right = rotateNode->right;
    if(rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //修正rotateNode 与 tree->father
    rotateNode->father = tree->father;
    if (tree->father == nullptr)
    {
        root = rotateNode;
    }
    else if (tree->elem > tree->father->elem)
    {
        tree->father->right = rotateNode;
    }
    else
    {
        tree->father->left = rotateNode;
    }
    //修正rotateNode 与 tree 的关系
    rotateNode->right = tree;
    tree->father = rotateNode;

    //修正高度差
    calcHeightWithLeft(rotateNode);
}

template<typename TYPE>
inline void AVLTree<TYPE>::rotateWithDoubleLeft(PNode tree)
{
    rotateWithRight(tree->left);
    rotateWithLeft(tree);
}

template<typename TYPE>
inline void AVLTree<TYPE>::rotateWithDoubleRight(PNode tree)
{
    rotateWithLeft(tree->right);
    rotateWithRight(tree);
}

template<typename TYPE>
inline void AVLTree<TYPE>::balance(PNode tree)
{
    while (tree)
    {
       tree->height = calcHeight(tree);

        if (abs(tree->height) > 1) //需要平衡
        {            
            if (tree->height > 0) //左边旋
            {
                if (tree->left->height > 0)
                {//左左
                    rotateWithLeft(tree);
                }
                else
                {//左右
                    rotateWithDoubleLeft(tree);
                }
            }
            else //右边旋
            {
                if (tree->right->height > 0)
                {//右右
                    rotateWithRight(tree);
                }
                else
                {//右左
                    rotateWithDoubleRight(tree);
                }
            }
        }
        tree = tree->father; //指向父亲平衡
    }
}