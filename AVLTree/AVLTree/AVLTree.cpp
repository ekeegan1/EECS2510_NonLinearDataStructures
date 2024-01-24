
#include "AVLTree.h"
#include <algorithm>
#include "iostream"
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

Node* AVLTree::rotateLeft(Node* node)
{
    Node* rightLeftChild = node->right->left;

    if (node->parent != nullptr)
        node->parent->replaceChild(node, node->right);

    else   //node is root
    {
        root = node->right;
        root->parent = nullptr;
    }

    node->right->setChild(Node::Child::LEFT, node);
    node->setChild(Node::Child::RIGHT, rightLeftChild);

    return node->parent;
}

Node* AVLTree::rotateRight(Node* node)
{
    Node* leftRightChild = node->left->right;

    if (node->parent != nullptr)
        node->parent->replaceChild(node, node->left);

    else   //node is root
    {
        root = node->left;
        root->parent = nullptr;
    }

    node->left->setChild(Node::Child::RIGHT, node);
    node->setChild(Node::Child::LEFT, leftRightChild);

    return node->parent;
}

Node* AVLTree::rebalence(Node* node)
{
    node->updateHeight();

    if (node->getBalence() == -2)
    {
        if (node->right->getBalence() == 1)
            rotateRight(node->right);

        return rotateLeft(node);
    }

    else if (node->getBalence() == 2)
    {
        if (node->left->getBalence() == -1)
            rotateLeft(node->left);

        return rotateRight(node);
    }

    return node;
}

// Insert a new element and rebalance the tree
void AVLTree::insert(Node* node)
{
    if (root == nullptr)
        root = node;

    else
    {
        Node* currNode = root;
        while (currNode != nullptr)
        {
            if (node->key < currNode->key)
            {
                if (currNode->left == nullptr)
                {
                    currNode->left = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
                else
                    currNode = currNode->left;
            }
            else
            {
                if (currNode->right == nullptr)
                {
                    currNode->right = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
                else
                    currNode = currNode->right;
            }
        }
        node = node->parent;
        while (node != nullptr)
        {
            rebalence(node);
            node = node->parent;
        }
    }
}
// Insert a new element without rebalancing the tree
void AVLTree::insertWithoutRebalance(Node* node)
{
    if (root == nullptr)
        root = node;
    
    else
    {
        Node* currNode = root;
        while (currNode != nullptr)
        {
            if (node->key < currNode->key)
            {
                if (currNode->left == nullptr)
                {
                    currNode->left = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
                else
                    currNode = currNode->left;
            }
            else
            {
                if (currNode->right == nullptr)
                {
                    currNode->right = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
                else
                    currNode = currNode->right;
            }
        }
    }
}

Node* AVLTree::getRoot()
{
    return root;
}

void Node::updateHeight()
{
    int leftHeight = -1;
    if (left != nullptr)
        leftHeight = left->height;

    int rightHeight = -1;
    if (right != nullptr)
        rightHeight = right->height;

    height = max(leftHeight, rightHeight) + 1;
}

int Node::getBalence()
{
    int leftHeight = -1;
    if (left != nullptr)
        leftHeight = left->height;

    int rightHeight = -1;
    if (right != nullptr)
        rightHeight = right->height;

    return leftHeight - rightHeight;

}


bool Node::setChild(Child whichChild, Node* child)
{
    //if (whichChild != "left" && whichChild != "right")
    //   return false;

    if (whichChild == Node::Child::LEFT)
        left = child;
    else
        right = child;

    if (child != nullptr)
        child->parent = this;

    updateHeight();
    return true;
}

bool Node::replaceChild(Node* currentChild, Node* newChild)
{
    if (left == currentChild)
        return setChild(Node::Child::LEFT, newChild);
    else if (right == currentChild)
        return setChild(Node::Child::RIGHT, newChild);
    return false;
}

vector<double> genNumbers(int size)
{
    // vector to hold random numbers
    vector<double> randomNums(size);

    // generate some random numbers
    for (int i = 0; i < size; i++)
    {
        // divide by RAND_MAX from <cstdlib>
        // the maximum value (1) that can be returned by rand()
        randomNums.at(i) = ((double)rand() * 1 / (double)RAND_MAX);
    }

    return randomNums;
}

int getHeight(Node* node)
{
    if (node == nullptr)
        return -1;

    else
        return 1 + max(getHeight(node->left), getHeight(node->right));
}

int main()
{
    
    // seed the random number generator via system clock
    auto seedTime = system_clock::now();
    unsigned int seed = duration_cast<seconds>(seedTime.time_since_epoch()).count() % UINT_MAX;	// modulo by the maximum value for an object of type unsigned int
    std::srand(seed);

    //tree size starts at 100
    int size = 100;

    //AVL Tree
    while (size <= 100000)
    {
        //varibale definitions
        std::vector<double> randNumbers(size);
        double minHeight = 0;
        double maxHeight = 0;
        double avgHeight = 0;

        //make 10 trees to have min, average, and max height
        for (int i = 0; i < 10; i++)
        {
            AVLTree newTree;
            randNumbers = genNumbers(size);
            
            int currHeight = 0;

            //assemble tree
            for (int i = 0; i < size; i++)
                newTree.insert(new Node(randNumbers.at(i)));

            //current tree's height
            currHeight = getHeight(newTree.getRoot());

            //calculate min,max, avg heights
            if (minHeight > currHeight || minHeight == 0)
                minHeight = currHeight;

            if (maxHeight < currHeight || maxHeight == 0)
                maxHeight = currHeight;
          
            avgHeight += currHeight;
        }
        avgHeight /= 10;

        cout << "For 10 interations, an AVLTree of size: " << size << " yeilds the following:" << endl;
        cout << "Minimum Height: " << minHeight << endl;
        cout << "Maximum Height: " << maxHeight << endl;
        cout << "Average Height: " << avgHeight << endl;

        size *= 10;
    }

    //reset tree size back to 100
    size = 100;

    //BST
    while (size <= 100000)
    {
        //varibale definitions
        std::vector<double> randNumbers(size);
        double minHeight = 0;
        double maxHeight = 0;
        double avgHeight = 0;

        //make 10 trees to have min, average, and max height
        for (int i = 0; i < 10; i++)
        {
            AVLTree newTree;
            randNumbers = genNumbers(size);

            int currHeight = 0;

            //assemble tree
            for (int i = 0; i < size; i++)
                newTree.insertWithoutRebalance(new Node(randNumbers.at(i)));

            //current tree's height
            currHeight = getHeight(newTree.getRoot());

            //calculate min,max, avg heights
            if (minHeight > currHeight || minHeight == 0)
                minHeight = currHeight;

            else if (maxHeight < currHeight || maxHeight == 0)
                maxHeight = currHeight;

            avgHeight += currHeight;
        }
        avgHeight /= 10;

        cout << "For 10 interations, a BST of size: " << size << " yeilds the following:" << endl;
        cout << "Minimum Height: " << minHeight << endl;
        cout << "Maximum Height: " << maxHeight << endl;
        cout << "Average Height: " << avgHeight << endl;

        size *= 10;
    }


    
    return 0;
}


