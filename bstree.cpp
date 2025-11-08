#include <iostream>
#include <stack>
using namespace std;

struct node {
    int data;
    node *left, *right;
};

class bstree {
public:
    node* root;
    bstree() {
        root = nullptr;
    }

    void create();
    void insertnode();
    void inorder(node* temp);
    void preorder(node* temp);
    void postorder(node* temp);
    void nonrec_inorder(node* temp);
    void nonrec_preorder(node* temp);
    void nonrec_postorder(node* temp);
    node* rec_search(node* temp, int key);
    void nonrec_search(node* temp, int key);
    void minNode(node* temp);
    void maxNode(node* temp);
    void display(node* temp, int space = 0);
    node* getroot() { return root; }
};

void bstree::create() {
    if (root != nullptr) {
        cout << "Root is already created!" << endl;
    } else {
        root = new node;
        root->left = root->right = nullptr;
        cout << "Enter the data for root: ";
        cin >> root->data;
        cout << "Root created successfully!" << endl;
    }
}

void bstree::insertnode() {
    if (root == nullptr) {
        create();
        return;
    }

    node* p = new node;
    p->left = p->right = nullptr;
    cout << "Enter data for new node: ";
    cin >> p->data;

    node* temp = root;
    while (temp != nullptr) {
        if (p->data < temp->data) {
            if (temp->left == nullptr) {
                temp->left = p;
                cout << "Node inserted on LEFT of " << temp->data << endl;
                return;
            } else {
                temp = temp->left;
            }
        } else if (p->data > temp->data) {
            if (temp->right == nullptr) {
                temp->right = p;
                cout << "Node inserted on RIGHT of " << temp->data << endl;
                return;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "Duplicates are not allowed!" << endl;
            delete p;
            return;
        }
    }
}

void bstree::inorder(node* temp) {
    if (temp != nullptr) {
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
}

void bstree::preorder(node* temp) {
    if (temp != nullptr) {
        cout << temp->data << " ";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void bstree::postorder(node* temp) {
    if (temp != nullptr) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << " ";
    }
}

void bstree::nonrec_inorder(node* temp) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    stack<node*> s;
    while (true) {
        while (temp != nullptr) {
            s.push(temp);
            temp = temp->left;
        }

        if (s.empty()) return;

        temp = s.top();
        s.pop();
        cout << temp->data << " ";
        temp = temp->right;
    }
}

void bstree::nonrec_preorder(node* temp) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    stack<node*> s;
    s.push(temp);

    while (!s.empty()) {
        temp = s.top();
        s.pop();

        cout << temp->data << " ";

        if (temp->right) s.push(temp->right);
        if (temp->left) s.push(temp->left);
    }
}

void bstree::nonrec_postorder(node* temp) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    stack<node*> s1, s2;
    s1.push(temp);

    while (!s1.empty()) {
        node* curr = s1.top();
        s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }

    cout << endl;
}

void bstree::minNode(node* temp) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    while (temp->left != nullptr) {
        temp = temp->left;
    }

    cout << "Minimum Node Value: " << temp->data << endl;
}

void bstree::maxNode(node* temp) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    while (temp->right != nullptr) {
        temp = temp->right;
    }

    cout << "Maximum Node Value: " << temp->data << endl;
}

node* bstree::rec_search(node* temp, int key) {
    if (temp == nullptr) return nullptr;

    if (key == temp->data)
        return temp;
    else if (key < temp->data)
        return rec_search(temp->left, key);
    else
        return rec_search(temp->right, key);
}

void bstree::nonrec_search(node* temp, int key) {
    if (temp == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    while (temp != nullptr) {
        if (key == temp->data) {
            cout << "Node found!" << endl;
            return;
        } else if (key < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    cout << "Node not found!" << endl;
}

void bstree::display(node* temp, int space) {
    if (temp == nullptr)
        return;

    space += 5;
    display(temp->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << temp->data << endl;

    display(temp->left, space);
}

int main() {
    bstree T;
    int choice;

    do {
        cout << "\n---- Binary Search Tree Operations ----" << endl;
        cout << "1. Create Root Node" << endl;
        cout << "2. Insert New Node" << endl;
        cout << "3. Inorder (Recursive)" << endl;
        cout << "4. Preorder (Recursive)" << endl;
        cout << "5. Postorder (Recursive)" << endl;
        cout << "6. Minimum Node" << endl;
        cout << "7. Maximum Node" << endl;
        cout << "8. Non-Recursive Inorder" << endl;
        cout << "9. Non-Recursive Preorder" << endl;
        cout << "10. Non-Recursive Postorder" << endl;
        cout << "11. Search (Recursive)" << endl;
        cout << "12. Search (Non-Recursive)" << endl;
        cout << "13. Display Tree (Rotated)" << endl;
        cout << "15. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                T.create();
                break;
            case 2:
                T.insertnode();
                break;
            case 3:
                cout << "Inorder Traversal: ";
                T.inorder(T.getroot());
                cout << endl;
                break;
            case 4:
                cout << "Preorder Traversal: ";
                T.preorder(T.getroot());
                cout << endl;
                break;
            case 5:
                cout << "Postorder Traversal: ";
                T.postorder(T.getroot());
                cout << endl;
                break;
            case 6:
                T.minNode(T.getroot());
                break;
            case 7:
                T.maxNode(T.getroot());
                break;
            case 8:
                cout << "Non-Recursive Inorder: ";
                T.nonrec_inorder(T.getroot());
                cout << endl;
                break;
            case 9:
                cout << "Non-Recursive Preorder: ";
                T.nonrec_preorder(T.getroot());
                cout << endl;
                break;
            case 10:
                cout << "Non-Recursive Postorder: ";
                T.nonrec_postorder(T.getroot());
                cout << endl;
                break;
            case 11: {
                int key;
                cout << "Enter value to search (Recursive): ";
                cin >> key;
                node* found = T.rec_search(T.getroot(), key);
                if (found)
                    cout << "Node found!" << endl;
                else
                    cout << "Node not found!" << endl;
                break;
            }
            case 12: {
                int key;
                cout << "Enter value to search (Non-Recursive): ";
                cin >> key;
                T.nonrec_search(T.getroot(), key);
                break;
            }
            case 13:
                cout << "\nTree Structure (Rotated):" << endl;
                T.display(T.getroot());
                break;
            case 15:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 15);

    return 0;
}
