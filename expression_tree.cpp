#include <iostream>
#include <stack>
using namespace std;

struct node {
    char data;
    node* left;
    node* right;

    node(char value) {
        data = value;
        left = right = nullptr;
    }
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

node* buildtree(const string& postfix) {
    stack<node*> s;

    for (char ch : postfix) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            node* newnode = new node(ch);
            s.push(newnode);
        }
        else if (isOperator(ch)) {
            if (s.size() < 2) {
                cout << "Invalid expression" << endl;
                return nullptr;
            }

            node* opright = s.top(); s.pop();
            node* opleft = s.top(); s.pop();

            node* opnode = new node(ch);
            opnode->left = opleft;
            opnode->right = opright;
            s.push(opnode);
        }
        else {
            cout << "Invalid character..." << endl;
            return nullptr;
        }
    }

    if (s.size() != 1) {
        cout << "Invalid postfix.." << endl;
        return nullptr;
    }

    return s.top();
}

void postorder(node* root, string& result) {
    if (root) {
        postorder(root->left, result);
        postorder(root->right, result);
        result += root->data;
    }
}

int main() {
    string postfix;
    cout << "Enter the postfix expression: ";
    cin >> postfix;

    node* root = buildtree(postfix);

    if (root) {
        string generated;
        postorder(root, generated);

        cout << "Postorder of the postfix expression: " << generated << endl;

        if (generated == postfix) {
            cout << "There is a valid expression tree for the given postfix expression." << endl;
        } 
        else {
            cout << "Mismatch between input and the postorder traversal." << endl;
        }
    }

    return 0;
}
