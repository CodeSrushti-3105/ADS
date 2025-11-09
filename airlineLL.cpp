#include <iostream>
using namespace std;

struct node {
    string src;
    string dest;
    int partnership;
    node *next;
};

class graph {
private:
    string airlines[20];
    node *head;
    int n;

public:
    graph() {
        head = nullptr;
    }
    void read();
    void display();
    void checkair();
    void allair();
};

void graph::read() {
    cout << "Enter the number of airlines: ";
    cin >> n;

    cout << "Enter the names of the airlines: ";
    for (int i = 0; i < n; i++) {
        cin >> airlines[i];
    }

    char choice;
    int s;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "\nDo " << airlines[i] << " and " << airlines[j]
                 << " have a partnership? (Y/N): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cout << "Enter partnership strength or number of shared routes: ";
                cin >> s;

                node *newNode1 = new node{airlines[i], airlines[j], s, head};
                head = newNode1;

                node *newNode2 = new node{airlines[j], airlines[i], s, head};
                head = newNode2;
            }
        }
    }
    cout << "\nAll partnership data recorded successfully.\n";
}

void graph::display() {
    cout << "\nList of Airlines: ";
    for (int i = 0; i < n; i++) {
        cout << airlines[i] << " ";
    }
    cout << "\n\nPartnership Details:\n";

    node *temp = head;
    while (temp) {
        cout << temp->src << " to " << temp->dest
             << " | Partnership Strength: " << temp->partnership << endl;
        temp = temp->next;
    }
    cout << endl;
}

void graph::checkair() {
    string a, b;
    cout << "Enter the first airline: ";
    cin >> a;
    cout << "Enter the second airline: ";
    cin >> b;

    node *temp = head;
    bool found = false;

    while (temp) {
        if (temp->src == a && temp->dest == b) {
            cout << "\nPartnership found between " << a << " and " << b << endl;
            cout << "Partnership Strength: " << temp->partnership << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "\nNo direct partnership exists between " << a << " and " << b << endl;
}

void graph::allair() {
    string a;
    cout << "Enter the airline name: ";
    cin >> a;

    node *temp = head;
    bool found = false;

    cout << "\nPartnerships for " << a << ":\n";
    while (temp) {
        if (temp->src == a) {
            cout << temp->dest
                 << " | Partnership Strength: " << temp->partnership << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "No partnerships found for " << a << endl;
}

int main() {
    graph g;
    int choice;

    do {
        cout << "\nAirline Partnership Management System\n";
        cout << "1. Record and Display Partnership Network\n";
        cout << "2. Check Partnership Between Two Airlines\n";
        cout << "3. Display All Partnerships for a Specific Airline\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.read();
                g.display();
                break;
            case 2:
                g.checkair();
                break;
            case 3:
                g.allair();
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
