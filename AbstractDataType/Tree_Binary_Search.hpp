//
// Created by Sea on 2021/6/16.
//

#ifndef ABSTRACTDATATYPE_TREE_BINARY_SEARCH_HPP
#define ABSTRACTDATATYPE_TREE_BINARY_SEARCH_HPP

/*
 * 二叉搜索树
 * 对于树中每个节点X,它的左子树所有项的值小于X中的项
 * 而它的右子树所有项的值大于X中的项
 */

//二叉搜索树ADT
template <class T>
class BinarySearchTree{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    ~BinarySearchTree();

    const T& findMin() const;
    const T& findMax() const;

    bool contains(const T& x) const;
    bool isEmpty();
    void printTree() const;

    void makeEmpty();
    void insert(const T& x);
    void remove(const T& x);

    const BinarySearchTree& operator=(const BinarySearchTree & rhs);

private:
    struct BinaryNode{
        T element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const T& theElement,BinaryNode *lt,BinaryNode *rt)
        :element(theElement),left(lt),right(rt){}
    };

    //根节点
    BinaryNode*root;
    void insert(const T& x,BinaryNode * &t) const;
    void remove(const T& x,BinaryNode * &t) const;
    BinaryNode* findMin(BinaryNode *t) const;
    BinaryNode* findMax(BinaryNode *t) const;
    bool contains(const T& x,BinaryNode * &t) const;
    void makeEmpty(BinaryNode * &t);
    void printTree(BinaryNode * t) const;
    BinaryNode* clone(BinaryNode *t) const;
};


#endif //ABSTRACTDATATYPE_TREE_BINARY_SEARCH_HPP
