#include <iostream>
#include <string.h>
using namespace std;

class AVLNode {
public:
    int id;
    char name[20];
    AVLNode *left, *right;
    int ht;
};

class AVLTree {
public:
    AVLNode *root;
    AVLTree() {
        root = nullptr;
    }

    int height(AVLNode *T);
    int BF(AVLNode *T);
    AVLNode *rotate_right(AVLNode *x);
    AVLNode *rotate_left(AVLNode *x);
    AVLNode *RR(AVLNode *T);
    AVLNode *LL(AVLNode *T);
    AVLNode *RL(AVLNode *T);
    AVLNode *LR(AVLNode *T);
    AVLNode *insert(AVLNode *root, int id, char name[20]);
    AVLNode *search(AVLNode *root, int id, int &count);
    AVLNode *deleteNode(AVLNode *root, int id);
    AVLNode *findmin(AVLNode *T);
    void inorder(AVLNode *root);
    void descending(AVLNode *root);
};

//---------------- Height ----------------
int AVLTree::height(AVLNode *T) {
    int lh, rh;
    if (T == nullptr)
        return 0;

    lh = height(T->left);
    rh = height(T->right);

    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

//---------------- Balance Factor ----------------
int AVLTree::BF(AVLNode *T) {
    int lh, rh;
    if (T == nullptr)
        return 0;

    if (T->left == nullptr)
        lh = 0;
    else
        lh = 1 + T->left->ht;

    if (T->right == nullptr)
        rh = 0;
    else
        rh = 1 + T->right->ht;

    return lh - rh;
}

//---------------- Rotations ----------------
AVLNode *AVLTree::rotate_right(AVLNode *x) {
    AVLNode *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

AVLNode *AVLTree::rotate_left(AVLNode *x) {
    AVLNode *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

AVLNode *AVLTree::RR(AVLNode *T) {
    T = rotate_left(T);
    return T;
}

AVLNode *AVLTree::LL(AVLNode *T) {
    T = rotate_right(T);
    return T;
}

AVLNode *AVLTree::RL(AVLNode *T) {
    T->right = rotate_right(T->right);
    T = rotate_left(T);
    return T;
}

AVLNode *AVLTree::LR(AVLNode *T) {
    T->left = rotate_left(T->left);
    T = rotate_right(T);
    return T;
}

//---------------- Insert ----------------
AVLNode *AVLTree::insert(AVLNode *root, int id, char name[20]) {
    if (root == nullptr) {
        AVLNode *temp = new AVLNode;
        temp->id = id;
        strcpy(temp->name, name);
        temp->left = temp->right = nullptr;
        temp->ht = 0;
        root = temp;
        return root;
    }

    if (id < root->id) {
        root->left = insert(root->left, id, name);
        if (BF(root) == 2) {
            if (id < root->left->id)
                root = LL(root);
            else
                root = LR(root);
        }
    } else if (id > root->id) {
        root->right = insert(root->right, id, name);
        if (BF(root) == -2) {
            if (id > root->right->id)
                root = RR(root);
            else
                root = RL(root);
        }
    } else {
        cout << "Duplicate" << endl;
    }

    root->ht = height(root);
    return root;
}

//---------------- Find Minimum ----------------
AVLNode *AVLTree::findmin(AVLNode *T) {
    while (T->left != nullptr)
        T = T->left;
    return T;
}

//---------------- Delete Node ----------------
AVLNode *AVLTree::deleteNode(AVLNode *root, int id) {
    if (root == nullptr)
        return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            AVLNode *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            AVLNode *temp = root->left;
            delete root;
            return temp;
        } else {
            AVLNode *temp = findmin(root->right);
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->right = deleteNode(root->right, temp->id);
        }
    }

    root->ht = height(root);
    int bal = BF(root);

    if (bal == 2 && BF(root->left) >= 0)
        return LL(root);
    if (bal == 2 && BF(root->left) < 0)
        return LR(root);
    if (bal == -2 && BF(root->right) <= 0)
        return RR(root);
    if (bal == -2 && BF(root->right) > 0)
        return RL(root);

    return root;
}

//---------------- Search ----------------
AVLNode *AVLTree::search(AVLNode *root, int id, int &count) {
    if (root == nullptr)
        return nullptr;

    count++;
    if (id == root->id)
        return root;
    else if (id < root->id)
        return search(root->left, id, count);
    else
        return search(root->right, id, count);
}

//---------------- Traversals ----------------
void AVLTree::inorder(AVLNode *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->id << " - " << root->name << endl;
        inorder(root->right);
    }
}

void AVLTree::descending(AVLNode *root) {
    if (root != nullptr) {
        descending(root->right);
        cout << root->id << " - " << root->name << endl;
        descending(root->left);
    }
}

//---------------- Main ----------------
int main() {
    AVLTree T;
    int ch, id, count;
    char name[20];

    do {
        cout << "\n1. Insert Employee"
             << "\n2. Search Employee"
             << "\n3. Delete Employee"
             << "\n4. Display Ascending"
             << "\n5. Display Descending"
             << "\n6. Height"
             << "\n7. Max Comparisons"
             << "\n8. Exit\n";

        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            T.root = T.insert(T.root, id, name);
            break;

        case 2:
            cout << "Enter ID to search: ";
            cin >> id;
            count = 0;
            {
                AVLNode *res = T.search(T.root, id, count);
                if (res)
                    cout << "Found: " << res->name << endl;
                else
                    cout << "Employee not found!" << endl;
                cout << "Comparisons: " << count << endl;
            }
            break;

        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            T.root = T.deleteNode(T.root, id);
            cout << "Deleted if existed.\n";
            break;

        case 4:
            cout << "Employees (Ascending Order):\n";
            T.inorder(T.root);
            break;

        case 5:
            cout << "Employees (Descending Order):\n";
            T.descending(T.root);
            break;

        case 6:
            cout << "Height of AVL Tree: " << T.height(T.root) << endl;
            break;

        case 7:
            cout << "Max comparisons for searching: " << T.height(T.root) << endl;
            break;

        case 8:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (ch != 8);

    return 0;
}
