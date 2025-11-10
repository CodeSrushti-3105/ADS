#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Build expression tree from prefix expression
Node* buildTree(const string &prefix) {
    stack<Node*> st;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            st.push(new Node(ch));
        } else if (isOperator(ch)) {
            if (st.size() < 2) {
                cout << "Invalid expression.\n";
                return nullptr;
            }
            Node* left = st.top(); st.pop();
            Node* right = st.top(); st.pop();
            Node* newNode = new Node(ch);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }
    return (st.size() == 1) ? st.top() : nullptr;
}

// Traversals
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Height
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Count operators
int countOperators(Node* root) {
    if (!root) return 0;
    int cnt = isOperator(root->data) ? 1 : 0;
    return cnt + countOperators(root->left) + countOperators(root->right);
}

// Mirror tree
Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node(root->data);
    newNode->left = mirror(root->right);
    newNode->right = mirror(root->left);
    return newNode;
}

int main() {
    vector<Node*> trees;
    int choice;

    do {
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Construct and store expression tree\n";
        cout << "2. Display traversals (Inorder, Preorder, Postorder)\n";
        cout << "3. Compare height of all trees\n";
        cout << "4. Find tree with maximum number of operators\n";
        cout << "5. Display mirror version of all trees\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string prefix;
            cout << "Enter prefix expression: ";
            cin >> prefix;
            Node* root = buildTree(prefix);
            if (root) {
                trees.push_back(root);
                cout << "Tree constructed successfully!\n";
            }
            break;
        }
        case 2: {
            if (trees.empty()) {
                cout << "No trees constructed yet.\n";
                break;
            }
            for (int i = 0; i < trees.size(); i++) {
                cout << "\nTree " << i + 1 << " Traversals:\n";
                cout << "Inorder: "; inorder(trees[i]); cout << "\n";
                cout << "Preorder: "; preorder(trees[i]); cout << "\n";
                cout << "Postorder: "; postorder(trees[i]); cout << "\n";
            }
            break;
        }
        case 3: {
            if (trees.empty()) {
                cout << "No trees to compare.\n";
                break;
            }
            for (int i = 0; i < trees.size(); i++)
                cout << "Height of Tree " << i + 1 << ": " << height(trees[i]) << "\n";
            break;
        }
        case 4: {
            if (trees.empty()) {
                cout << "No trees available.\n";
                break;
            }
            int maxOps = -1, idx = -1;
            for (int i = 0; i < trees.size(); i++) {
                int ops = countOperators(trees[i]);
                cout << "Tree " << i + 1 << " has " << ops << " operators.\n";
                if (ops > maxOps) {
                    maxOps = ops;
                    idx = i;
                }
            }
            if (idx != -1)
                cout << "Tree " << idx + 1 << " has the maximum number of operators (" << maxOps << ").\n";
            break;
        }
        case 5: {
            if (trees.empty()) {
                cout << "No trees to mirror.\n";
                break;
            }
            for (int i = 0; i < trees.size(); i++) {
                cout << "\nMirror of Tree " << i + 1 << " (Preorder): ";
                Node* mirrorTree = mirror(trees[i]);
                preorder(mirrorTree);
                cout << "\n";
            }
            break;
        }
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
