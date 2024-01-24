#ifndef AVLTREE_H
#define AVLTREE_H

// A node in the AVL tree that stores a double
class Node {
public:
    enum Child
    {
        LEFT, RIGHT
    };

    double key;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) {
        key = nodeKey;
    }

    int getBalence();
    void updateHeight();
    bool setChild(Child whichChild, Node* child);
    bool replaceChild(Node* currentChild, Node* newChild);
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
    AVLTree() {};
    ~AVLTree();

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rebalence(Node* node);
    Node* getRoot();


    // Insert a new element and rebalance the tree
    void insert(Node* node);
    // Insert a new element without rebalancing the tree
    void insertWithoutRebalance(Node* node);

private:
    Node* root = nullptr;
    void deleteTree(Node* node);
};

#endif // !AVLTREE_H