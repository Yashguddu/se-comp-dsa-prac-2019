/*Beginning with an empty binary search tree, Construct binary search tree
by inserting the values in the order given. After constructing a binary tree -
i. Insert new node ii. Find number of nodes in longest path from root 
v. Search a value */

#include <iostream>
using namespace std;

struct bstnode 
{
    int data;
    bstnode* left;
    bstnode* right;
};

class btree 
{
private:
    bstnode* root;

public:
    btree() 
    {
        root = nullptr;
    }

    bstnode* getNewNode(int data) 
    {
        bstnode* newNode = new bstnode();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    bstnode* insert(bstnode* root, int data) 
    {
        if (root == nullptr) 
        {
            root = getNewNode(data);
        }
        else if (data <= root->data) 
        {
            root->left = insert(root->left, data);
        }
        else 
        {
            root->right = insert(root->right, data);
        }
        return root;
    }

    int findLongestPath(bstnode* root) 
    {
        if (root == nullptr) 
        {
            return 0;
        }
        int leftPath = findLongestPath(root->left);
        int rightPath = findLongestPath(root->right);
        return max(leftPath, rightPath) + 1;
    }

    bool search(bstnode* root, int data) 
    {
        if (root == nullptr)
         {
            return false;
        }
        else if (root->data == data)
         {
            return true;
        }
        else if (data < root->data) 
        {
            return search(root->left, data);
        }
        else 
        {
            return search(root->right, data);
        }
    }

    void inorderTraversal(bstnode* root) 
    {
    if (root == nullptr) 
    {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

    void constructTree() 
    {
        int n;
        cout << "Enter the number of values: ";
        cin >> n;

        cout << "Enter the values in order: ";
        for (int i = 0; i < n; i++) 
        {
            int value;
            cin >> value;
            root = insert(root, value);
        }
    }

    void insertNode()
     {
        int value;
        cout << "Enter the value to insert: ";
        cin >> value;
        root = insert(root, value);
        cout << "Value " << value << " inserted successfully!" << endl;
    }

    void findLongestPathFromRoot() 
    {
        int longestPath = findLongestPath(root);
        cout << "Number of nodes in the longest path from root: " << longestPath << endl;
    }

    void searchValue() 
    {
        int value;
        cout << "Enter the value to search: ";
        cin >> value;

        if (search(root, value)) 
        {
            cout << "Value " << value << " found in the tree" << endl;
        }
        else 
        {
            cout << "Value " << value << " not found in the tree" << endl;
        }
    }

    void displayInorder() 
    {
        cout << "Inorder Traversal: ";
        inorderTraversal(root);
        cout << endl;
    }
};

int main() 
{
    btree tree;

    // Construct binary search tree
    tree.constructTree();

    // Insert a new node
    tree.insertNode();

    // Find number of nodes in the longest path from root
    tree.findLongestPathFromRoot();

    // Search a value
    tree.searchValue();

    // Display the tree using inorder traversal
    tree.displayInorder();

    return 0;
}

