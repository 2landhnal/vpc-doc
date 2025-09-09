#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(int data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Function to print postorder traversal
// Left-Right-Root 
void printPostorder(struct Node* node)
{
    if (node == nullptr)
        return;

    // First recur on left subtree
    printPostorder(node->left);

    // Then recur on right subtree
    printPostorder(node->right);

    // Now deal with the node
    cout << node->data << " ";
}

// Function to perform preorder traversal
// Root → Left → Right
void preorderTraversal(Node* node)
{
    if (node != nullptr) {
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

// Function to print inorder traversal
// Left → Root → Right
void printInorder(struct Node* node)
{
    if (node == nullptr)
        return;

    // First recur on left subtree
    printInorder(node->left);

    // Now deal with the node
    cout << node->data << " ";

    // Then recur on right subtree
    printInorder(node->right);
}
