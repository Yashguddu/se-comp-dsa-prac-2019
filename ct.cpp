/*Construct an expression tree from the given prefix expression eg. +--a*bc/def and
traverse it using post order traversal (non recursive) and then delete the entire tree.        chatgpt                  */
#include <iostream>
#include <stack>
using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;
};

Node* createNode(char value) {
    Node* newNode = new Node();
    if (newNode == NULL) {
        cout << "Memory allocation failed!" << endl;
        exit(1);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* constructExpressionTree(string prefixExpr) {
    stack<Node*> stk;

    // Iterate over the prefix expression in reverse order
    for (int i = prefixExpr.length() - 1; i >= 0; i--) {
        char token = prefixExpr[i];

        if (isdigit(token) || isalpha(token)) {
            // Operand, create a new node
            Node* node = createNode(token);
            stk.push(node);
        } else {
            // Operator, create a new node with children
            Node* node = createNode(token);
            node->left = stk.top();
            stk.pop();
            node->right = stk.top();
            stk.pop();
            stk.push(node);
        }
    }

    // The last remaining node in the stack is the root of the expression tree
    return stk.top();
}

void postorderTraversal(Node* root) {
    if (root == NULL)
        return;

    stack<Node*> stk;
    stack<Node*> result;
    Node* lastVisited = NULL;

    while (!stk.empty() || root) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            Node* peekNode = stk.top();

            if (peekNode->right && lastVisited != peekNode->right) {
                // Visit the right subtree
                root = peekNode->right;
            } else {
                // Process the current node
                result.push(peekNode);
                stk.pop();
                lastVisited = peekNode;
            }
        }
    }

    // Print the postorder traversal result
    while (!result.empty()) {
        Node* node = result.top();
        cout << node->value;
        result.pop();
    }
}

void deleteTree(Node* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    // Delete the current node
    delete root;
}

int main() {
    string prefixExpression = "+--a*bc/def";

    // Construct the expression tree
    Node* root = constructExpressionTree(prefixExpression);

    // Perform postorder traversal
    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << endl;

    // Delete the entire tree
    deleteTree(root);
    cout<<" The entire tree has been deleted ";

    return 0;
}

