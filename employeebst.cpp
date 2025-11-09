#include <iostream>
#include <stack>
using namespace std;

struct node{
public:
    int id;
    int salary;
    node *left,*right;
};

class bstree{
private:
    node* root;
public:
    bstree(){
        root = nullptr;
    }
    void insert();
    void search();
    void findmin();
    void findmax();
    void ascend();
    void descend(node* temp);
    int height(node* temp);
    void countNodes(node* temp);
    node* getroot(){return root;}
};

void bstree::insert(){
    node* p = new node;
    cout<<"Enter the id of employee: ";
    cin>>p->id;
    cout<<"Enter the salary of employee: ";
    cin>> p->salary;
    p->left = p->right = nullptr;

    if(root == nullptr){
        root = p;
        cout<<"root record inserted.."<<endl;
        return;
    }

    node* temp = root;
    while(true){
        if(p->id < temp->id){
            if(temp->left == nullptr){
                temp ->left = p;
                return;
            }else{
                temp = temp ->left;
            }
        }else if(p -> id > temp -> id){
            if(temp -> right == nullptr){
                temp -> right = p;
                return;
            }else{
                temp = temp -> right;
            }
        }else{
            cout<<"Duplicate records are not allowed"<<endl;
            delete p;
            return;
        }
    }
}

void bstree::search(){
    int key;
    cout<<"Enter the employees id: ";
    cin>>key;

    node* temp = root;
    while(temp!=nullptr){
        if(key == temp -> id){
            cout<<"Employee found! salary: "<<temp->salary<<endl;
            return;
        }else if(key < temp -> id){
            temp = temp -> left;
        }else{
            temp = temp -> right;
        }
    }
    cout<<"employee not found"<<endl;
}

void bstree::findmin(){
    node* temp = root;
    while(temp -> left != nullptr){
        temp = temp->left;
    }
    cout<<"Employee with min salary :"<< temp->id << " salary: "<<temp->salary<<endl;
}

void bstree::findmax(){
    node* temp = root;
    while(temp -> right != nullptr){
        temp = temp->right;
    }
    cout<<"Employee with max salary :"<< temp->id << " salary: "<<temp->salary<<endl;
}

void bstree::ascend(){
    stack<node*>s;
    node* temp = root;
    while(true){
        while(temp != nullptr){
            s.push(temp);
            temp = temp -> left;
        }
        if(s.empty()) return;
        temp = s.top();
        s.pop();
        cout<<"ID: "<<temp->id<<" Salary: "<<temp->salary<<endl;
        temp = temp -> right;
    }
}

void bstree::descend(node* temp){
    if (temp == nullptr)
        return;
    
    descend(temp->right);
    cout<<"ID: "<<temp->id<<" Salary: "<<temp->salary<<endl;
    descend(temp -> left);
    
}

int bstree::height(node* temp){

    if(temp == nullptr)
        return 0;
    int leftHeight = height(temp ->left);
    int rightHeight = height(temp->right);
    if(leftHeight>rightHeight){
        return 1+leftHeight;
    }else{
        return 1+rightHeight;
    }
}

void bstree::countNodes(node* temp){
    stack<node*>s;
    s.push(root);

    int totalnode = 0;
    int leaf = 0;
    while(!s.empty()){
        node* curr = s.top();
        s.pop();
        totalnode++;

        if(curr -> left == nullptr && curr -> right==nullptr){
            leaf++;
        }

        if(curr ->left) s.push(curr->left);
        if(curr ->right) s.push(curr->right);
    }
    cout<<"Total no. of nodes : "<<totalnode<<endl;
    cout<<"Total leaf nodes: "<<leaf<<endl;
}

int main(){
    bstree T;
    int choice;
    do{
        cout<<"1.Insert the employee data"<<endl;
        cout<<"2.search"<<endl;
        cout<<"3.min sal"<<endl;
        cout<<"4.max sal"<<endl;
        cout<<"5.ascending"<<endl;
        cout<<"6.descending"<<endl;
        cout<<"7.height"<<endl;
        cout<<"8.total nodes"<<endl;
        cout<<"11.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
        case 1:
            T.insert();
            break;
        case 2:
            T.search();
            break;
        case 3:
            T.findmin();
            break;
        case 4:
            T.findmax();
            break;
        case 5:
            T.ascend();
            break;
        case 6:
            T.descend(T.getroot());
            break;
        case 7:
            cout << "Height of tree: " << T.height(T.getroot()) << endl;
            break;
        case 8:
            T.countNodes(T.getroot());
            break;
        case 11:
            cout<<"Exiting the code"<<endl;

        }
    }while(choice!=11);
}


