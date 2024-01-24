#include "RedBlackTree.h"
#include "AVLTree.h"
#include <algorithm>
#include "iostream"
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

//AVL.cpp code
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



RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::deleteTree(RBTNode* node) {
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



//RBT.cpp code

void RedBlackTree::insert(RBTNode* node)
{
    BSTInsert(node);
    node->red = true;
    RBTreeBalance(node);
}

void RedBlackTree::BSTInsert(RBTNode* node)
{
    if (root == nullptr)
        root = node;

    else
    {
        RBTNode* currNode = root;
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

void RedBlackTree::RBTreeBalance(RBTNode* node)
{
    if (node->parent == nullptr)
    {
        node->red = false;
        return;
    }
    if (node->parent->red == false)
        return;

    RBTNode* parent = node->parent;
    RBTNode* grandparent = node->getGrandparent();
    RBTNode* uncle = node->getUncle();

    if (uncle != nullptr && uncle->red == true)
    {
        parent->red = false;
        uncle->red = false;
        grandparent->red = true;
        RBTreeBalance(grandparent);
        return;
    }

    if (node == parent->right && grandparent != nullptr && parent == grandparent->left)
    {
        rotateLeft(parent);
        node = parent;
        parent = node->parent;
    }

    else if (node == parent->left && grandparent != nullptr && parent == grandparent->right)
    {
        rotateRight(parent);
        node = parent;
        parent = node->parent;
    }

    parent->red = false;
    if (grandparent != nullptr)
        grandparent->red = true;

    if (node == parent->left)
    {
        if (grandparent != nullptr)
            rotateRight(grandparent);
    }
    else
    {
        if (grandparent != nullptr)
            rotateLeft(grandparent);
    }

}


RBTNode* RedBlackTree::rotateLeft(RBTNode* node)
{
    RBTNode* rightLeftChild = node->right->left;

    if (node->parent != nullptr)
        node->parent->replaceChild(node, node->right);
    else
    {
        root = node->right;
        root->parent = nullptr;
    }

    node->right->setChild(RBTNode::Child::LEFT, node);
    node->setChild(RBTNode::Child::RIGHT, rightLeftChild);

    return node->parent;
}

RBTNode* RedBlackTree::rotateRight(RBTNode* node)
{
    RBTNode* leftRightChild = node->left->right;

    if (node->parent != nullptr)
        node->parent->replaceChild(node, node->left);
    else
    {
        root = node->left;
        root->parent = nullptr;
    }

    node->left->setChild(RBTNode::Child::RIGHT, node);
    node->setChild(RBTNode::Child::LEFT, leftRightChild);

    return node->parent;
}

RBTNode* RedBlackTree::getRoot()
{
    return root;
}


//NODE Class Code
RBTNode::RBTNode(double nodeKey)
{
    this->key = nodeKey;
}

RBTNode::RBTNode(double nodeKey, RBTNode* parentNode, bool isRed)
{
    this->key = nodeKey;
    this->parent = parentNode;
    this->color = isRed ? Color::RED : Color::BLACK;
    this->left = nullptr;
    this->right = nullptr;
}

RBTNode::RBTNode(double nodeKey, RBTNode* parentNode, bool isRed, RBTNode* leftChild, RBTNode* rightChild)
{
    key = nodeKey;
    parent = parentNode;
    left = leftChild;
    right = rightChild;
    color = isRed ? Color::RED : Color::BLACK;
}

bool RBTNode::areBothChildrenBlack()
{
    if (left != nullptr && left->isRed())
        return false;
    if (right != nullptr && right->isRed())
        return false;

    return true;
}

int RBTNode::count()
{
    int count = 1;
    if (left != nullptr)
        count += left->count();
    if (right != nullptr)
        count += right->count();

    return count;
}

RBTNode* RBTNode::getGrandparent()
{
    if (parent == nullptr)
        return nullptr;

    return parent->parent;
}

RBTNode* RBTNode::getPredecessor()
{
    RBTNode* node = left;
    while (node->right != nullptr)
        node = node->right;

    return node;
}

RBTNode* RBTNode::getSibling()
{
    if (parent != nullptr)
    {
        if (this == parent->left)
            return parent->right;

        return parent->left;
    }
    return nullptr;
}

RBTNode* RBTNode::getUncle()
{
    RBTNode* grandparent = getGrandparent();
    if (grandparent == nullptr)
        return nullptr;

    if (grandparent->left == parent)
        return grandparent->right;

    return grandparent->left;
}

bool RBTNode::isBlack()
{
    return color == Color::RED;
}

bool RBTNode::isRed()
{
    return color == Color::BLACK;
}

bool RBTNode::replaceChild(RBTNode* currentChild, RBTNode* newChild)
{
    if (left == currentChild)
        return setChild(Child::LEFT, newChild);

    else if (right == currentChild)
        return setChild(Child::RIGHT, newChild);

    return false;
}

bool RBTNode::setChild(Child whichChild, RBTNode* child)
{
    if (whichChild == Child::LEFT)
        left = child;

    else
        right = child;

    if (child != nullptr)
        child->parent = this;

    return true;
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

void bucketSort(vector<double>& numbers, int numBuckets)
{
    if (numbers.size() < 1)
        return;

    std::vector<std::vector<double>> buckets(numBuckets);
    //std::vector<int> buckets(std::vector<int> test);

    // Find the maximum value
    int maxValue = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] > maxValue)
            maxValue = numbers[i];
    }

    //put each number in a bucket
    for (int i = 0; i < numbers.size(); i++)
    {

        int index = floor(numbers[i] * numBuckets / (maxValue + 1));
        buckets[index].push_back(numbers.at(i));
    }

    //insertion sort
    for (int i = 0; i < numBuckets; i++)
    {
        for (int i = 1; i < numbers.size(); ++i)
        {
            int j = i;

            while (j > 0 && numbers[j] < numbers[j - 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j - 1];
                numbers[j - 1] = temp;
                --j;
            }
        }
    }

    //concatenate the buckets
    int index = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            numbers.at(index) = buckets[i].at(j);
            index++;
        }
    }
}

int getRBTHeight(RBTNode* node)
{
    if (node == nullptr)
        return -1;

    else
        return 1 + max(getRBTHeight(node->left), getRBTHeight(node->right));
}

int getAVLHeight(Node* node)
{
    if (node == nullptr)
        return -1;

    else
        return 1 + max(getAVLHeight(node->left), getAVLHeight(node->right));
}

int main()
{
    /*
    Test red-black tree inserts
    RedBlackTree a;
    RBTNode* aRoot = new RBTNode(22);
    a.insert(aRoot);
    a.insert(new RBTNode(11));
    a.insert(new RBTNode(33));
    a.insert(new RBTNode(55));
    a.insert(new RBTNode(44));
    cout << aRoot->key << endl;
    cout << aRoot->left->key << " " << aRoot->right->key << endl;
    cout << aRoot->right->left->key << " " << aRoot->right->right->key << endl;
    */

    
    // seed the random number generator via system clock
    auto seedTime = system_clock::now();
    unsigned int seed = duration_cast<seconds>(seedTime.time_since_epoch()).count() % UINT_MAX;	// modulo by the maximum value for an object of type unsigned int
    std::srand(seed);

    //tree size starts at 100
    int size = 100;

    //Unsorted Insertions
    while (size <= 100000)
    {
        //varibale definitions
        std::vector<double> randNumbers(size);
        double AVLMinHeight = 0;
        double AVLMaxHeight = 0;
        double AVLAvgHeight = 0;
        double RBTMinHeight = 0;
        double RBTMaxHeight = 0;
        double RBTAvgHeight = 0;
        double AVLAvgInsertionTime = 0;
        double RBTAvgInsertionTime = 0;

        //make 10 trees to have min, average, and max height
        for (int i = 0; i < 10; i++)
        {
            AVLTree newAVL;
            RedBlackTree newRBT;
            randNumbers = genNumbers(size);

            int currAVLHeight = 0;
            int currRBTHeight = 0;


            auto start1 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newAVL.insert(new Node(randNumbers.at(i)));

            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds>(stop1 - start1);
            AVLAvgInsertionTime += duration1.count();

            auto start2 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newRBT.insert(new RBTNode(randNumbers.at(i)));

            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
            RBTAvgInsertionTime += duration2.count();

            //current tree's height
            currAVLHeight = getAVLHeight(newAVL.getRoot());
            currRBTHeight = getRBTHeight(newRBT.getRoot());

            //calculate min,max, avg heights
            //first, AVL
            if (AVLMinHeight > currAVLHeight || AVLMinHeight == 0)
                AVLMinHeight = currAVLHeight;

            if (AVLMaxHeight < currAVLHeight || AVLMaxHeight == 0)
                AVLMaxHeight = currAVLHeight;

            AVLAvgHeight += currAVLHeight;

            //second, RBT
            if (RBTMinHeight > currRBTHeight || RBTMinHeight == 0)
                RBTMinHeight = currRBTHeight;

            if (RBTMaxHeight < currRBTHeight || RBTMaxHeight == 0)
                RBTMaxHeight = currRBTHeight;

            RBTAvgHeight += currRBTHeight;
        }
        AVLAvgHeight /= 10;
        AVLAvgInsertionTime /= 10;
        RBTAvgHeight /= 10;
        RBTAvgInsertionTime /= 10;


        std::cout << "For 10 interations of unsorted insertions, an Tree of size: " << size << " yeilds the following:" << std::endl;
        std::cout << "AVL's Minimum Height: " << AVLMinHeight << "                     RBT's Minimum Height: " << RBTMinHeight << std::endl;
        std::cout << "AVL's Maximum Height: " << AVLMaxHeight << "                     RBT's Maximum Height: " << RBTMaxHeight << std::endl;
        std::cout << "AVL's Average Height: " << AVLAvgHeight << "                     RBT's Average Height: " << RBTAvgHeight << std::endl;
        std::cout << "AVL's Average Insertion Time: " << AVLAvgInsertionTime / 1000.0 << " ms     RBT's Average Insertion Time: " << RBTAvgInsertionTime / 1000.0 << " ms" << std::endl;
        std::cout << std::endl;

        size *= 10;
    }

    //reset size
    size = 100;

    //Fully Sorted Insertions
    while (size <= 100000)
    {
        //varibale definitions
        std::vector<double> randNumbers(size);
        double AVLMinHeight = 0;
        double AVLMaxHeight = 0;
        double AVLAvgHeight = 0;
        double RBTMinHeight = 0;
        double RBTMaxHeight = 0;
        double RBTAvgHeight = 0;
        double AVLAvgInsertionTime = 0;
        double RBTAvgInsertionTime = 0;

        //make 10 trees to have min, average, and max height
        for (int i = 0; i < 10; i++)
        {
            AVLTree newAVL;
            RedBlackTree newRBT;
            randNumbers = genNumbers(size);

            bucketSort(randNumbers, 10);

            int currAVLHeight = 0;
            int currRBTHeight = 0;


            auto start1 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newAVL.insert(new Node(randNumbers.at(i)));

            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds>(stop1 - start1);
            AVLAvgInsertionTime += duration1.count();

            auto start2 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newRBT.insert(new RBTNode(randNumbers.at(i)));

            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
            RBTAvgInsertionTime += duration2.count();

            //current tree's height
            currAVLHeight = getAVLHeight(newAVL.getRoot());
            currRBTHeight = getRBTHeight(newRBT.getRoot());

            //calculate min,max, avg heights
            //first, AVL
            if (AVLMinHeight > currAVLHeight || AVLMinHeight == 0)
                AVLMinHeight = currAVLHeight;

            if (AVLMaxHeight < currAVLHeight || AVLMaxHeight == 0)
                AVLMaxHeight = currAVLHeight;

            AVLAvgHeight += currAVLHeight;

            //second, RBT
            if (RBTMinHeight > currRBTHeight || RBTMinHeight == 0)
                RBTMinHeight = currRBTHeight;

            if (RBTMaxHeight < currRBTHeight || RBTMaxHeight == 0)
                RBTMaxHeight = currRBTHeight;

            RBTAvgHeight += currRBTHeight;
        }
        AVLAvgHeight /= 10;
        AVLAvgInsertionTime /= 10;
        RBTAvgHeight /= 10;
        RBTAvgInsertionTime /= 10;


        std::cout << "For 10 interations of fully sorted insertions, an Tree of size: " << size << " yeilds the following:" << std::endl;
        std::cout << "AVL's Minimum Height: " << AVLMinHeight << "                     RBT's Minimum Height: " << RBTMinHeight << std::endl;
        std::cout << "AVL's Maximum Height: " << AVLMaxHeight << "                     RBT's Maximum Height: " << RBTMaxHeight << std::endl;
        std::cout << "AVL's Average Height: " << AVLAvgHeight << "                     RBT's Average Height: " << RBTAvgHeight << std::endl;
        std::cout << "AVL's Average Insertion Time: " << AVLAvgInsertionTime / 1000.0 << " ms     RBT's Average Insertion Time: " << RBTAvgInsertionTime / 1000.0 << " ms" << std::endl;
        std::cout << std::endl;

        size *= 10;
    }

    //reset size
    size = 100;

    //Half Sorted Insertions
    while (size <= 100000)
    {
        //varibale definitions
        std::vector<double> randNumbers(size);
        double AVLMinHeight = 0;
        double AVLMaxHeight = 0;
        double AVLAvgHeight = 0;
        double RBTMinHeight = 0;
        double RBTMaxHeight = 0;
        double RBTAvgHeight = 0;
        double AVLAvgInsertionTime = 0;
        double RBTAvgInsertionTime = 0;

        //make 10 trees to have min, average, and max height
        for (int i = 0; i < 10; i++)
        {

            AVLTree newAVL;
            RedBlackTree newRBT;
            randNumbers = genNumbers(size);

            //sort the middle numbers
            vector<double> sortingVector(size / 2);
            for (int i = (size / 4); i < (3 * size / 4); i++)
            {
                int j = 0;
                sortingVector[j] = randNumbers[i];
                j += 1;
            }

            //sort them
            bucketSort(sortingVector, 10);

            //add them back to the randNumbers list
            for (int i = (size / 4); i < (3 * size / 4); i++)
            {
                int j = 0;
                randNumbers[i] = sortingVector[j];
                j += 1;
            }

            int currAVLHeight = 0;
            int currRBTHeight = 0;


            auto start1 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newAVL.insert(new Node(randNumbers.at(i)));

            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds>(stop1 - start1);
            AVLAvgInsertionTime += duration1.count();

            auto start2 = high_resolution_clock::now();

            //assemble tree
            for (int i = 0; i < size; i++)
                newRBT.insert(new RBTNode(randNumbers.at(i)));

            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
            RBTAvgInsertionTime += duration2.count();

            //current tree's height
            currAVLHeight = getAVLHeight(newAVL.getRoot());
            currRBTHeight = getRBTHeight(newRBT.getRoot());

            //calculate min,max, avg heights
            //first, AVL
            if (AVLMinHeight > currAVLHeight || AVLMinHeight == 0)
                AVLMinHeight = currAVLHeight;

            if (AVLMaxHeight < currAVLHeight || AVLMaxHeight == 0)
                AVLMaxHeight = currAVLHeight;

            AVLAvgHeight += currAVLHeight;

            //second, RBT
            if (RBTMinHeight > currRBTHeight || RBTMinHeight == 0)
                RBTMinHeight = currRBTHeight;

            if (RBTMaxHeight < currRBTHeight || RBTMaxHeight == 0)
                RBTMaxHeight = currRBTHeight;

            RBTAvgHeight += currRBTHeight;
        }
        AVLAvgHeight /= 10;
        AVLAvgInsertionTime /= 10;
        RBTAvgHeight /= 10;
        RBTAvgInsertionTime /= 10;


        std::cout << "For 10 interations of half sorted insertions, an Tree of size: " << size << " yeilds the following:" << std::endl;
        std::cout << "AVL's Minimum Height: " << AVLMinHeight << "                     RBT's Minimum Height: " << RBTMinHeight << std::endl;
        std::cout << "AVL's Maximum Height: " << AVLMaxHeight << "                     RBT's Maximum Height: " << RBTMaxHeight << std::endl;
        std::cout << "AVL's Average Height: " << AVLAvgHeight << "                     RBT's Average Height: " << RBTAvgHeight << std::endl;
        std::cout << "AVL's Average Insertion Time: " << AVLAvgInsertionTime / 1000.0 << " ms     RBT's Average Insertion Time: " << RBTAvgInsertionTime / 1000.0 << " ms" << std::endl; 
        std::cout << std::endl;

        size *= 10;
    }
    

    return 0;
}