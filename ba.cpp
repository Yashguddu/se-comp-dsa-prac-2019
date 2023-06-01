#include <iostream>              //avl tree updated
#include <string>
using namespace std;

// AVL tree node
struct Node {
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Function to update the height of a node
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

// Function to perform a right rotation on a node
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation on a node
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to balance the AVL tree
Node* balance(Node* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Function to create a new AVL tree node
Node* createNode(string keyword, string meaning) {
    Node* newNode = new Node();
    newNode->keyword = keyword;
    newNode->meaning = meaning;
    newNode->height = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a new keyword with its meaning into the AVL tree
Node* insert(Node* root, string keyword, string meaning) {
    if (root == nullptr) {
        return createNode(keyword, meaning);
    }

    if (keyword < root->keyword) {
        root->left = insert(root->left, keyword, meaning);
    } else if (keyword > root->keyword) {
        root->right = insert(root->right, keyword, meaning);
    } else {
        cout << "Keyword already exists!" << endl;
        return root;
    }

    return balance(root);
}

// Function to find the node with the minimum value in a subtree
Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Function to delete a keyword from the AVL tree
Node* remove(Node* root, string keyword) {
    if (root == nullptr) {
        cout << "Keyword not found!" << endl;
        return root;
    }

    if (keyword < root->keyword) {
        root->left = remove(root->left, keyword);
    } else if (keyword > root->keyword) {
        root->right = remove(root->right, keyword);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* minNode = findMin(root->right);
            root->keyword = minNode->keyword;
            root->meaning = minNode->meaning;
            root->right = remove(root->right, minNode->keyword);
        }
    }

    if (root == nullptr) {
        return root;
    }

    return balance(root);
}

// Function to update the meaning of a keyword in the AVL tree
Node* update(Node* root, string keyword, string newMeaning) {
    if (root == nullptr) {
        cout << "Keyword not found!" << endl;
        return root;
    }

    if (keyword < root->keyword) {
        root->left = update(root->left, keyword, newMeaning);
    } else if (keyword > root->keyword) {
        root->right = update(root->right, keyword, newMeaning);
    } else {
        root->meaning = newMeaning;
    }

    return root;
}

// Function to display the entire AVL tree in inorder traversal
void display(Node* root) {
    if (root == nullptr) {
        return;
    }

    display(root->left);
    cout << root->keyword << ": " << root->meaning << endl;
    display(root->right);
}

int main() {
    Node* root = nullptr;

    while (true) {
        cout << "Dictionary Menu:\n";
        cout << "1. Add a keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update the meaning of a keyword\n";
        cout << "4. Display the entire data\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string keyword, meaning;
                cout << "Enter the keyword: ";
                cin >> keyword;
                cout << "Enter the meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                cout << "Keyword added successfully!" << endl;
                break;
            }
            case 2: {
                string keyword;
                cout << "Enter the keyword to delete: ";
                cin >> keyword;
                root = remove(root, keyword);
                cout << "Keyword deleted successfully!" << endl;
                break;
            }
            case 3: {
                string keyword, newMeaning;
                cout << "Enter the keyword to update: ";
                cin >> keyword;
                cout << "Enter the new meaning: ";
                cin.ignore();
                getline(cin, newMeaning);
                root = update(root, keyword, newMeaning);
                cout << "Meaning updated successfully!" << endl;
                break;
            }
            case 4:
                if (root == nullptr) {
                    cout << "Dictionary is empty!" << endl;
                } else {
                    cout << "Dictionary Data:\n";
                    display(root);
                }
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }

        cout << endl;
    }
}

