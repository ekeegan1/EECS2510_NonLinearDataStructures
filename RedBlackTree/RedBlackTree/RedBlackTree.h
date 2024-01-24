#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

// A node in the red-black tree that stores a double
class RBTNode {
public:
    
    enum Child
    {
        LEFT, RIGHT
    };

    enum Color
    {
        RED, BLACK
    };
    
    double key;
    // Whether the node is red (false denotes black)
    bool red = true;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;
    Color color;

    RBTNode(double nodeKey);
    RBTNode(double nodeKey, RBTNode* parentNode, bool isRed);
    RBTNode(double nodeKey, RBTNode* parentNode, bool isRed, RBTNode* leftChild, RBTNode* rightChild);
    bool areBothChildrenBlack();
    int count();
    RBTNode* getGrandparent();
    RBTNode* getPredecessor();
    RBTNode* getSibling();
    RBTNode* getUncle();
    bool isBlack();
    bool isRed();
    bool replaceChild(RBTNode* currentChild, RBTNode* newChild);
    bool setChild(Child whichChild, RBTNode* child);




};

// A red-black tree that can only insert
class RedBlackTree
{
public:
    RedBlackTree() 
    {
        root = nullptr;
    }
    ~RedBlackTree();

    // Insert a new element and rebalance the tree
    void insert(RBTNode* node);

    void insertNode(RBTNode* node);
    void insertionBalance(RBTNode* node);
    void BSTInsert(RBTNode* node);
    void RBTreeBalance(RBTNode* node);
    RBTNode* rotateLeft(RBTNode* node);
    RBTNode* rotateRight(RBTNode* node);
    RBTNode* getRoot();



private:
    RBTNode* root = nullptr;
    void deleteTree(RBTNode* node);
};

#endif // !REDBLACKTREE_H