#pragma once
#include "MyStack.hpp"
#include "MyQueue.hpp"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

template<typename Object>
class TreeCompare
{
    int operator()(const Object& t1, const Object& t2)
    {
        if(t1 > t2)
            return 1;
        else if(t1 < t2)
            return -1;
        else
            return 0;
    }
};

//AVL �ǵݹ��ʵ�� ��֧���ظ�����
template<typename TYPE,typename KeyCompare = TreeCompare<TYPE>,typename ValueCompare = TreeCompare<TYPE>>
class AVLTree
{
    typedef void(*showFun)(TYPE& elem, int height); //��ӡ�ص�
private:
    typedef struct Node
    {
        TYPE elem;
        Node *left;
        Node *right;
        Node *father; //���׽ڵ�
        int height;
        Node *prev; //ǰһ���ڵ�
        Node *next; //��һ���ڵ�
        Node(const TYPE& elem=TYPE{}, Node *father=nullptr,Node *left=nullptr,
                Node *right = nullptr,int height = 0,Node *next=nullptr);
    }*PNode;

public:
    AVLTree();
    ~AVLTree();
    
    bool empty() const;
    TYPE& findMin() const;
    TYPE& findMax() const;
    void insert(const TYPE& elem); //����Ԫ��
    void insert_unique(const TYPE& elem);
    void insert_equal(const TYPE& elem);
    void remove(const TYPE& elem); //�Ƴ�Ԫ��
    void remove_unique(const TYPE& elem);
    void remove_equal(const TYPE& elem);

    void preOrder(showFun fun) const; //ǰ��
    void inOrder(showFun fun) const; //����
    void postOrder(showFun fun) const; //����
    
private:
    PNode findMin(PNode tree) const;
    PNode findMax(PNode tree) const;
    PNode find(PNode tree,const TYPE& elem) const;
    void addNode(const TYPE & elem, PNode fatherNode = nullptr, bool dirFlag = true);
    void insert_(PNode tree, const TYPE & elem,bool repeatFlag = false);
    void insert(PNode tree, const TYPE& elem);
    void remove(PNode tree, const TYPE& elem);

    int getHeight(PNode tree) const; //��ȡ�߶�
    int calcHeight(PNode tree) const; //����߶�
    PNode rotateByLeft(PNode tree); //�����
    PNode rotateByRight(PNode tree); //�ұ���
    PNode rotateByDoubleLeft(PNode tree); //��˫��
    PNode rotateByDoubleRight(PNode tree); //��˫��
    void balance(PNode tree); //�Ӹýڵ�һֱ����ƽ��

private:
    PNode root;
    KeyCompare keyCompare;
    ValueCompare valueCompare;
    static const int BF = 1;
};

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline AVLTree<TYPE, KeyCompare, ValueCompare>::Node::Node(const TYPE& elem, Node *father, Node *left,
    Node *right, int height, Node *next)
    :elem(elem),father(father),left(left),right(right),height(height),next(next)
{}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline AVLTree<TYPE, KeyCompare, ValueCompare>::AVLTree()
    :root(nullptr)
{}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline AVLTree<TYPE, KeyCompare, ValueCompare>::~AVLTree()
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline bool AVLTree<TYPE, KeyCompare, ValueCompare>::empty() const
{
    return (nullptr == root);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline TYPE& AVLTree<TYPE, KeyCompare, ValueCompare>::findMin() const
{
    return findMin(root)->elem;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline TYPE& AVLTree<TYPE, KeyCompare, ValueCompare>::findMax() const
{
    return findMax(root)->elem;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::insert(const TYPE& elem)
{
    insert(root,elem);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::insert_unique(const TYPE & elem)
{
    insert_(root,elem);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::insert_equal(const TYPE & elem)
{
    insert_(root,elem,true);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::remove(const TYPE & elem)
{
    remove(root,elem);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::preOrder(showFun fun) const
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::inOrder(showFun fun) const
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::postOrder(showFun fun) const
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::findMin(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while(tree->left)
        tree = tree->left;

    return tree;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::findMax(PNode tree) const
{
    if (tree == nullptr)
        return nullptr;

    while (tree->right)
        tree = tree->right;

    return tree;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::find(PNode tree,const TYPE& elem) const
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::addNode(const TYPE & elem, PNode fatherNode, bool dirFlag)
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::insert_(PNode tree, const TYPE & elem, bool repeatFlag)
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
                newNode->next = tree->next;
                tree->next = newNode;
            }
            return; 
        }
    }

    addNode(elem, fatherNode, dirFlag);

    balance(fatherNode); //�Ӹø��ڵ㿪ʼƽ��
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::insert(PNode tree, const TYPE & elem)
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::remove(PNode tree, const TYPE & elem)
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
            
            if (tree->left != nullptr && tree->right != nullptr)
            {
                PNode minNode = findMin(tree->right);
                tree->elem = minNode->elem;
                tree = minNode; //����ɾ��minNode
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline int AVLTree<TYPE, KeyCompare, ValueCompare>::getHeight(PNode tree) const
{
    if (tree == nullptr)
        return -1; //Ҷ��Ϊ0,ʹ��nullΪ-1

    return tree->height;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline int AVLTree<TYPE, KeyCompare, ValueCompare>::calcHeight(PNode tree) const
{
    return MAX(getHeight(tree->left), getHeight(tree->right)) + 1;
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::rotateByLeft(PNode tree)
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::rotateByRight(PNode tree)
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

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::rotateByDoubleLeft(PNode tree)
{
    rotateByRight(tree->left);
    return rotateByLeft(tree);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline typename AVLTree<TYPE, KeyCompare, ValueCompare>::PNode AVLTree<TYPE, KeyCompare, ValueCompare>::rotateByDoubleRight(PNode tree)
{
    rotateByLeft(tree->right);
    return rotateByRight(tree);
}

template<typename TYPE, typename KeyCompare, typename ValueCompare>
inline void AVLTree<TYPE, KeyCompare, ValueCompare>::balance(PNode tree)
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
