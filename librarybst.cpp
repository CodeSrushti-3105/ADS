#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int id;
    string title;
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
    void del();
    void inorderdisplay();
    void min();
    void max();
    void countNodes();
    Node* getRoot() { return root; }
    Node* deleteNode(Node* temp, int key);
};

void bstree::insert() {
    Node *p = new Node;
    cout << "Enter Book ID: ";
    cin >> p->id;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, p->title);
    p->left = p->right = nullptr;

    if (root == nullptr) {
        root = p;
        cout << "Root book added" << endl;
        return;
    }

    Node *temp = root;
    while (true) {
        if (p->id < temp->id) {
            if (temp->left == nullptr) {
                temp->left = p;
                cout << "Book inserted" << endl;
                return;
            } else {
                temp = temp->left;
            }
        } else if (p->id > temp->id) {
            if (temp->right == nullptr) {
                temp->right = p;
                cout << "Book inserted" << endl;
                return;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "Duplicate Book ID not allowed" << endl;
            delete p;
            return;
        }
    }
}

Node* bstree::deleteNode(Node* temp, int key) {
    if (temp == nullptr) return temp;

    if (key < temp->id)
        temp->left = deleteNode(temp->left, key);
    else if (key > temp->id)
        temp->right = deleteNode(temp->right, key);
    else {
        if (temp->left == nullptr && temp->right == nullptr) {
            delete temp;
            return nullptr;
        } else if (temp->left == nullptr) {
            Node* r = temp->right;
            delete temp;
            return r;
        } else if (temp->right == nullptr) {
            Node* l = temp->left;
            delete temp;
            return l;
        } else {
            Node* succ = temp->right;
            while (succ->left != nullptr)
                succ = succ->left;
            temp->id = succ->id;
            temp->title = succ->title;
            temp->right = deleteNode(temp->right, succ->id);
        }
    }
    return temp;
}

void bstree::del() {
    if (root == nullptr) {
        cout << "No books available to delete" << endl;
        return;
    }
    int key;
    cout << "Enter Book ID to delete: ";
    cin >> key;
    root = deleteNode(root, key);
    cout << "Book deleted (if ID existed)" << endl;
}

void bstree::inorderdisplay() {
    if (root == nullptr) {
        cout << "No books in catalogue" << endl;
        return;
    }

    stack<Node*> s;
    Node* temp = root;
    cout << "\nBooks in Sorted Order:\n";
    while (true) {
        while (temp != nullptr) {
            s.push(temp);
            temp = temp->left;
        }
        if (s.empty()) return;
        temp = s.top();
        s.pop();
        cout << "Book ID: " << temp->id << " | Title: " << temp->title << endl;
        temp = temp->right;
    }
}

void bstree::min() {
    if (root == nullptr) {
        cout << "No books in catalogue" << endl;
        return;
    }
    Node* temp = root;
    while (temp->left != nullptr)
        temp = temp->left;
    cout << "Book with Smallest ID: " << temp->id << " | Title: " << temp->title << endl;
}

void bstree::max() {
    if (root == nullptr) {
        cout << "No books in catalogue" << endl;
        return;
    }
    Node* temp = root;
    while (temp->right != nullptr)
        temp = temp->right;
    cout << "Book with Largest ID: " << temp->id << " | Title: " << temp->title << endl;
}

void bstree::countNodes() {
    if (root == nullptr) {
        cout << "No books in catalogue" << endl;
        return;
    }

    stack<Node*> s;
    s.push(root);
    int total = 0, leaf = 0;

    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        total++;

        if (curr->left == nullptr && curr->right == nullptr)
            leaf++;

        if (curr->left) s.push(curr->left);
        if (curr->right) s.push(curr->right);
    }

    cout << "Total Books: " << total << endl;
    cout << "Leaf Nodes: " << leaf << endl;
}

int main() {
    bstree T;
    int choice;

    do {
        cout << "\n--- Library Book Catalogue ---" << endl;
        cout << "1. Insert New Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Find Book with Minimum ID" << endl;
        cout << "4. Find Book with Maximum ID" << endl;
        cout << "5. Display All Books (Sorted Order)" << endl;
        cout << "6. Count Total and Leaf Nodes" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: T.insert(); break;
            case 2: T.del(); break;
            case 3: T.min(); break;
            case 4: T.max(); break;
            case 5: T.inorderdisplay(); break;
            case 6: T.countNodes(); break;
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}
