#pragma once

//AVL �ǵݹ��ʵ��
template<typename TYPE>
class AVLTree
{
    typedef void(*showFun)(TYPE& elem, int height, int deep); //��ӡ�ص�
private:
    typedef struct Node
    {
        TYPE elem;
        Node *left;
        Node *right;
        Node *father; //���׽ڵ�
        int height; //��Ÿ߶Ȳ�
        Node(const TYPE& elem=TYPE{}, Node *father=nullptr,Node *left=nullptr,
                Node *right = nullptr,int height = 0);
    }*PNode;

public:
    AVLTree();
    ~AVLTree();
    
    bool empty() const;
    TYPE& findMin() const;
    TYPE& findMax() const;
    void insert(const TYPE& elem); //����Ԫ��
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    PNode find(PNode tree,const TYPE& elem) const;
    void insert(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //��ȡ�߶Ȳ�
    int calcHeight(PNode tree) const; //����߶Ȳ�
    void calcHeightWithLeft(PNode tree); //���¼���߶Ȳ�(�����)
    void calcHeightWithRight(PNode tree); //���¼���߶Ȳ�(�ұ���)
    void rotateWithLeft(PNode tree); //�����
    void rotateWithRight(PNode tree); //�ұ���
    void rotateWithDoubleLeft(PNode tree); //��˫��
    void rotateWithDoubleRight(PNode tree); //��˫��
    void balance(PNode tree); //�Ӹýڵ�һֱ����ƽ��

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
            return;  //�����ظ�Ԫ return
        } 
    }
    
    if(dirFlag)
        fatherNode->right = newNode;
    else
        fatherNode->left = newNode;
    
    newNode->father = fatherNode;
    
    balance(fatherNode); //�Ӹø��ڵ㿪ʼƽ��
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
    //�ȸ���TK1
    if(Tk2 >= 0)
        Tk1 -= (Tk2 + 1);
    else
        --Tk1;
    //�ٸ���TK2
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
    //�ȸ���TK1
    if(Tk2 >= 0)
        ++Tk1;
    else
        Tk1 += (1-Tk2);
    //�ٸ���TK2
    if (Tk1 >= 0)
        Tk2 += Tk1 + 1;
    else
        ++Tk2;
}

template<typename TYPE>
inline void AVLTree<TYPE>::rotateWithLeft(PNode tree)
{
    PNode rotateNode = tree->left;
    //����tree��rotateNode->right
    tree->left = rotateNode->right;
    if(rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //����tree->father��rotateNode
    rotateNode->father = tree->father;
    if(tree->father == nullptr)
        root = rotateNode;
    else if (tree->elem > tree->father->elem)
        tree->father->right = rotateNode;
    else
        tree->father->left = rotateNode;
    //����tree��rotateNode
    tree->father = rotateNode;
    rotateNode->right = tree;
    
    //�����߶Ȳ�
    calcHeightWithLeft(rotateNode);
}

template<typename TYPE>
inline void AVLTree<TYPE>::rotateWithRight(PNode tree)
{
    PNode rotateNode = tree->right;
    //����rotateNode->right��tree�Ĺ���
    tree->right = rotateNode->right;
    if(rotateNode->right != nullptr)
        rotateNode->right->father = tree;
    //����rotateNode �� tree->father
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
    //����rotateNode �� tree �Ĺ�ϵ
    rotateNode->right = tree;
    tree->father = rotateNode;

    //�����߶Ȳ�
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

        if (abs(tree->height) > 1) //��Ҫƽ��
        {            
            if (tree->height > 0) //�����
            {
                if (tree->left->height > 0)
                {//����
                    rotateWithLeft(tree);
                }
                else
                {//����
                    rotateWithDoubleLeft(tree);
                }
            }
            else //�ұ���
            {
                if (tree->right->height > 0)
                {//����
                    rotateWithRight(tree);
                }
                else
                {//����
                    rotateWithDoubleRight(tree);
                }
            }
        }
        tree = tree->father; //ָ����ƽ��
    }
}