#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int id;
    string name;
    Node *left, *right;
};

class bstree {
private:
    Node* root;
public:
    bstree() {
        root = nullptr;
    }
    void insert();
    void search();
    void inorderdisplay();
    void min();
    void max();
    void countNodes();
    int height(Node* temp);
    Node* getRoot() { return root; }
};

void bstree::insert() {
    Node *p = new Node;
    cout << "Enter the id of patient: ";
    cin >> p->id;
    cout << "Enter the name of the patient: ";
    cin.ignore();
    getline(cin, p->name);
    p->left = p->right = nullptr;

    if (root == nullptr) {
        root = p;
        cout << "Root patient created" << endl;
        return;
    }

    Node *temp = root;
    while (true) {
        if (p->id < temp->id) {
            if (temp->left == nullptr) {
                temp->left = p;
                cout << "Record inserted" << endl;
                return;
            } else {
                temp = temp->left;
            }
        } else if (p->id > temp->id) {
            if (temp->right == nullptr) {
                temp->right = p;
                cout << "Record inserted" << endl;
                return;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "Duplicate record not allowed" << endl;
            delete p;
            return;
        }
    }
}

void bstree::search() {
    if (root == nullptr) {
        cout << "No record inserted yet" << endl;
        return;
    }

    int key;
    cout << "Enter the key: ";
    cin >> key;

    Node* temp = root;
    while (temp != nullptr) {
        if (key == temp->id) {
            cout << "Patient found! Name: " << temp->name << endl;
            return;
        } else if (key < temp->id) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    cout << "Patient not found" << endl;
}

void bstree::inorderdisplay() {
    if (root == nullptr) {
        cout << "No record inserted yet" << endl;
        return;
    }

    stack<Node*> s;
    Node* temp = root;
    while (true) {
        while (temp != nullptr) {
            s.push(temp);
            temp = temp->left;
        }
        if (s.empty()) return;
        temp = s.top();
        s.pop();
        cout << "ID: " << temp->id << " | Name: " << temp->name << endl;
        temp = temp->right;
    }
}

void bstree::min() {
    if (root == nullptr) {
        cout << "No record inserted yet" << endl;
        return;
    }
    Node* temp = root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    cout << "Minimum patient ID: " << temp->id << " | Name: " << temp->name << endl;
}

void bstree::max() {
    if (root == nullptr) {
        cout << "No record inserted yet" << endl;
        return;
    }
    Node* temp = root;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    cout << "Maximum patient ID: " << temp->id << " | Name: " << temp->name << endl;
}

void bstree::countNodes() {
    if (root == nullptr) {
        cout << "No record inserted yet" << endl;
        return;
    }

    stack<Node*> s;
    s.push(root);
    int total = 0, leaf = 0;

    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        total++;
        if (curr->left == nullptr && curr->right == nullptr) {
            leaf++;
        }
        if (curr->left) s.push(curr->left);
        if (curr->right) s.push(curr->right);
    }

    cout << "Total nodes: " << total << endl;
    cout << "Total leaf nodes: " << leaf << endl;
}

int bstree::height(Node* temp) {
    if (temp == nullptr)
        return 0;
    int leftHeight = height(temp->left);
    int rightHeight = height(temp->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main() {
    bstree T;
    int choice;
    do {
        cout << "\n--- Hospital Patient Record System ---" << endl;
        cout << "1. Insert new patient record" << endl;
        cout << "2. Search patient by ID" << endl;
        cout << "3. Display all patient records (Inorder)" << endl;
        cout << "4. Find Minimum patient ID" << endl;
        cout << "5. Find Maximum patient ID" << endl;
        cout << "6. Count total and leaf nodes" << endl;
        cout << "7. Display height of tree" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: T.insert(); break;
            case 2: T.search(); break;
            case 3: T.inorderdisplay(); break;
            case 4: T.min(); break;
            case 5: T.max(); break;
            case 6: T.countNodes(); break;
            case 7: cout << "Height of Tree: " << T.height(T.getRoot()) << endl; break;
            case 8: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);
    return 0;
}
