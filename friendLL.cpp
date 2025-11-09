#include <iostream>
using namespace std;

struct friends {
public:
    string friend1;
    string friend2;
    friends* next;
};

class graph {
private:
    string users[20];
    friends* head;
    int n;

public:
    graph() {
        head = nullptr;
    }

    void read();
    void display();
    void directconnect();
    void allconnect();
};

void graph::read() {
    cout << "Enter the number of users: ";
    cin >> n;

    cout << "Enter the names of the users: ";
    for (int i = 0; i < n; i++) {
        cin >> users[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char choice;
            cout << "Is there a connection between " << users[i] << " and " << users[j] << "? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                friends* newNode1 = new friends{users[i], users[j], head};
                head = newNode1;

                friends* newNode2 = new friends{users[j], users[i], head};
                head = newNode2;
            }
        }
    }
    cout << "Data recorded..." << endl;
}

void graph::display() {
    cout << "Users list: ";
    for (int i = 0; i < n; i++) {
        cout << users[i] << " ";
    }
    cout << endl;

    friends* temp = head;
    while (temp != nullptr) {
        cout << temp->friend1 << " and " << temp->friend2 << " are friends." << endl;
        temp = temp->next;
    }
    cout << endl;
}

void graph::directconnect() {
    string src, dest;
    cout << "Enter first user: ";
    cin >> src;
    cout << "Enter second user: ";
    cin >> dest;

    friends* temp = head;
    bool found = false;

    while (temp) {
        if (temp->friend1 == src && temp->friend2 == dest) {
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (found)
        cout << "Both are friends." << endl;
    else
        cout << "Both are not friends." << endl;

    cout << endl;
}

void graph::allconnect() {
    string src;
    cout << "Enter user name: ";
    cin >> src;

    friends* temp = head;
    bool found = false;

    while (temp) {
        if (temp->friend1 == src) {
            cout << temp->friend1 << " is friend of " << temp->friend2 << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No connections found for " << src << endl;
    }
    cout << endl;
}

int main() {
    graph g;
    int choice;

    do {
        cout << "\n---- Social Network Menu ----\n";
        cout << "1. Record and Display Connections\n";
        cout << "2. Check Friendship Between Two Users\n";
        cout << "3. Display All Friends of a User\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.read();
                g.display();
                break;

            case 2:
                g.directconnect();
                break;

            case 3:
                g.allconnect();
                break;

            case 5:
                cout << "\nExiting the program.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
