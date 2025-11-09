#include <iostream>
using namespace std;

class graph {
private:
    int friends[100][100];
    string users[100];
    int n;
public:
    void read();
    void display();
    void directconnect();
    void allconnected();
};

void graph::read() {
    cout << "Enter the number of users: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter the name of user " << i + 1 << ": ";
        cin >> users[i];
    }

    // Initialize all connections to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            friends[i][j] = 0;
        }
    }

    char choice;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Are " << users[i] << " and " << users[j] << " friends? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                friends[i][j] = friends[j][i] = 1;
            }
        }
    }
    cout << "\nFriend data recorded successfully!\n\n";
}

void graph::display() {
    cout << "\nAll users: ";
    for (int i = 0; i < n; i++) {
        cout << users[i] << " ";
    }
    cout << "\n\n-- Friends Matrix --\n\t";

    for (int i = 0; i < n; i++) {
        cout << users[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << users[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << friends[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void graph::directconnect() {
    string a, b;
    cout << "\nEnter the two users to check friendship: ";
    cin >> a >> b;

    int a_index = -1, b_index = -1;
    for (int i = 0; i < n; i++) {
        if (users[i] == a) a_index = i;
        if (users[i] == b) b_index = i;
    }

    if (a_index == -1 || b_index == -1) {
        cout << " Invalid user name(s) entered.\n";
        return;
    }

    if (friends[a_index][b_index] == 1) {
        cout <<  a << " and " << b << " are friends.\n";
    } else {
        cout <<  a << " and " << b << " are not friends.\n";
    }
    cout << endl;
}

void graph::allconnected() {
    string a;
    cout << "\nEnter the name of the user: ";
    cin >> a;

    int a_index = -1;
    for (int i = 0; i < n; i++) {
        if (users[i] == a) a_index = i;
    }

    if (a_index == -1) {
        cout << " Invalid user name entered.\n";
        return;
    }

    cout << "\nFriends of " << a << ":\n";
    bool hasFriends = false;
    for (int j = 0; j < n; j++) {
        if (friends[a_index][j] == 1) {
            cout << "→ " << users[j] << endl;
            hasFriends = true;
        }
    }

    if (!hasFriends)
        cout << "No friends found for " << a << ".\n";

    cout << endl;
}

int main() {
    graph g;
    int choice;
    do {
        cout << "---- Social Network Menu ----" << endl;
        cout << "1. Read users & display friend matrix" << endl;
        cout << "2. Check if two users are friends" << endl;
        cout << "3. Display all friends of a user" << endl;
        cout << "4. Exit" << endl;
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
            g.allconnected();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}
