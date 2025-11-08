#include <iostream>
#include <string.h>
using namespace std;

class AVLnode {
public:
    char keyword[20], meaning[20];
    AVLnode *left, *right;
    int ht;
};

class AVLtree {
public:
    AVLnode *root;
    AVLtree() {
        root = nullptr;
    }
    AVLnode *rotate_right(AVLnode *x);
    AVLnode *rotate_left(AVLnode *x);
    AVLnode *LL(AVLnode *x);
    AVLnode *RR(AVLnode *x);
    AVLnode *LR(AVLnode *x);
    AVLnode *RL(AVLnode *x);
    int height(AVLnode *x);
    int BF(AVLnode *x);
    AVLnode *insert(AVLnode*, char newkey[20], char mean[20]);
    void inorder(AVLnode *x);
};

AVLnode *AVLtree::rotate_right(AVLnode *x) {
    AVLnode *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

AVLnode *AVLtree::rotate_left(AVLnode *x) {
    AVLnode *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

int AVLtree::height(AVLnode *T) {
    int hl, hr;
    if (T == nullptr)
        return 0;
    hl = height(T->left);
    hr = height(T->right);
    if (hl < hr) {
        return hr + 1;
    } else {
        return hl + 1;
    }
}

int AVLtree::BF(AVLnode *T) {
    int lh, rh;
    if (T == nullptr) {
        return 0;
    } else {
        if (T->left == nullptr)
            lh = 0;
        else
            lh = 1 + T->left->ht;
        if (T->right == nullptr)
            rh = 0;
        else
            rh = 1 + T->right->ht;
    }
    return lh - rh;
}

AVLnode *AVLtree::RR(AVLnode *T) {
    T = rotate_left(T);
    return T;
}

AVLnode *AVLtree::LL(AVLnode *T) {
    T = rotate_right(T);
    return T;
}

AVLnode *AVLtree::RL(AVLnode *T) {
    T->right = rotate_right(T->right);
    T = rotate_left(T);
    return T;
}

AVLnode *AVLtree::LR(AVLnode *T) {
    T->left = rotate_left(T->left);
    T = rotate_right(T);
    return T;
}

AVLnode *AVLtree::insert(AVLnode *root, char newkey[20], char means[20]) {
    if (root == nullptr) {
        AVLnode *curr = new AVLnode;
        strcpy(curr->keyword, newkey);
        strcpy(curr->meaning, means);
        curr->ht = 0;
        curr->left = nullptr;
        curr->right = nullptr;
        root = curr;
        return root;
    }

    if (strcmp(newkey, root->keyword) < 0) {
        root->left = insert(root->left, newkey, means);
        if (BF(root) == 2) {
            if (strcmp(newkey, root->left->keyword) < 0) {
                root = LL(root);
            } else {
                root = LR(root);
            }
        }
    } else if (strcmp(newkey, root->keyword) > 0) {
        root->right = insert(root->right, newkey, means);
        if (BF(root) == -2) {
            if (strcmp(newkey, root->right->keyword) > 0) {
                root = RR(root);
            } else {
                root = RL(root);
            }
        }
    } else {
        cout << "Duplicate" << endl;
    }
    root->ht = height(root);
    return root;
}

void AVLtree::inorder(AVLnode *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->keyword << "(" << root->meaning << ")" << endl;
        inorder(root->right);
    }
}

int main() {
    AVLtree AT;
    int choice;
    char keyword[20], meaning[20];
    do {
        cout << "1.Insert keyword" << endl;
        cout << "2.Display" << endl;
        cout << "4.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the keyword: ";
            cin >> keyword;
            cin.ignore();
            cout << "Enter meaning: ";
            cin.getline(meaning, 20);
            AT.root = AT.insert(AT.root, keyword, meaning);
            break;

        case 2:
            cout << "\nDictionary words (Inorder Traversal):\n";
            AT.inorder(AT.root);
            cout << endl;
            break;

        case 4:
            cout << "Exiting the program..." << endl;
        }
    } while (choice != 4);
}
