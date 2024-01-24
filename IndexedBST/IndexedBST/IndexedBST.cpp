#include "IndexedBST.h"

Node* IndexedBST::search(double desiredKey) {
    Node* cur = root;
    while (cur != nullptr) {
        // Return the node if the key matches
        if (cur->key == desiredKey) {
            return cur;
        }

        // Navigate to the left if the search key is 
        // less than the node's key.
        else if (desiredKey < cur->key) {
            cur = cur->left;
        }

        // Navigate to the right if the search key is 
        // greater than the node's key.
        else {
            cur = cur->right;
        }
    }

    // The key was not found in the tree.
    return nullptr;
}

Node* IndexedBST::at(int index) {
    Node* cur = root;
    while (cur != nullptr) {
        if (index == cur->leftSize)
            return cur;     // Found
        else if (index < cur->leftSize)
            cur = cur->left;    // index is in left subtree
        else {
            // index is in right subtree
            index = index - cur->leftSize - 1;
            cur = cur->right;
        }
    }

    return nullptr;
}


// Add implementations of insert and remove (keeping indexing in mind)


void IndexedBST::insert(Node* node)
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


bool IndexedBST::remove(double key)
{
    Node* parent = nullptr;
    Node* currentNode = root;

    // Search for the node.
    while (currentNode != nullptr) {
        // Check if currentNode has a matching key.
        if (currentNode->key == key) {
            if (currentNode->left == nullptr && currentNode->right == nullptr) { // Case 1
                if (parent == nullptr) { // Node is root
                    root = nullptr;
                }
                else if (parent->left == currentNode) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
                return true; // Node found and removed
            }
            else if (currentNode->left != nullptr && currentNode->right == nullptr) { // Case 2
                if (parent == nullptr) { // Node is root
                    root = currentNode->left;
                }
                else if (parent->left == currentNode) {
                    parent->left = currentNode->left;
                }
                else {
                    parent->right = currentNode->left;
                }
                return true; // Node found and removed
            }
            else if (currentNode->left == nullptr && currentNode->right != nullptr) { // Case 2
                if (parent == nullptr) { // Node is root
                    root = currentNode->right;
                }
                else if (parent->left == currentNode) {
                    parent->left = currentNode->right;
                }
                else {
                    parent->right = currentNode->right;
                }
                return true; // Node found and removed
            }
            else { // Case 3
                // Find successor (leftmost child of right subtree)
                Node* successor = currentNode->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                currentNode->key = successor->key; // Copy successor to current node
                parent = currentNode;
                currentNode = currentNode->right; // Remove successor from right subtree
                key = successor->key;             // Loop continues with new key
            }
        }
        else if (currentNode->key < key) { // Search right
            parent = currentNode;
            currentNode = currentNode->right;
        }
        else { // Search left
            parent = currentNode;
            currentNode = currentNode->left;
        }
    }
    return false; // Node not found

}