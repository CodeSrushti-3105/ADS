#include <iostream>
using namespace std;

struct flight {
    string src;
    string dest;
    int time;
    int fuel;
    flight* next;
};

class graph {
private:
    string cities[10];
    int n;
    flight* head;

public:
    graph() {
        head = nullptr;
    }

    void read();
    void display();
    void checkflight();
    void displayTour();
    void indirectFlight();
};

void graph::read() {
    cout << "Enter the number of cities: ";
    cin >> n;

    cout << "Enter the names of cities: ";
    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }

    cout << "\nEnter the time and fuel matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            char choice;
            cout << "Is there any flight from " << cities[i] << " to " << cities[j] << "? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                int t, f;
                cout << "Enter the time required from " << cities[i] << " to " << cities[j] << ": ";
                cin >> t;
                cout << "Enter the fuel required from " << cities[i] << " to " << cities[j] << ": ";
                cin >> f;

                flight* newflight = new flight{cities[i], cities[j], t, f, head};
                head = newflight;
            }
        }
    }
    cout << "\nFlight data recorded successfully.\n\n";
}

void graph::display() {
    if (!head) {
        cout << "No flight data available.\n";
        return;
    }

    cout << "\n--- Flight Details ---\n";
    flight* temp = head;
    while (temp) {
        cout << temp->src << " -> " << temp->dest
             << " | Time: " << temp->time << " hrs"
             << " | Fuel: " << temp->fuel << " L\n";
        temp = temp->next;
    }
    cout << endl;
}

void graph::checkflight() {
    if (!head) {
        cout << "No flight data available.\n";
        return;
    }

    string srcName, destName;
    cout << "Enter source city: ";
    cin >> srcName;
    cout << "Enter destination city: ";
    cin >> destName;

    flight* temp = head;
    while (temp) {
        if (temp->src == srcName && temp->dest == destName) {
            cout << "\nFlight is Available!\n";
            cout << "From: " << temp->src << " → " << temp->dest << endl;
            cout << "Time required: " << temp->time << " hrs" << endl;
            cout << "Fuel required: " << temp->fuel << " L\n";
            return;
        }
        temp = temp->next;
    }

    cout << "No direct flight found from " << srcName << " to " << destName << ".\n";
}

void graph::displayTour() {
    if (!head) {
        cout << "No flight data available.\n";
        return;
    }

    string srcName;
    cout << "Enter the source city: ";
    cin >> srcName;

    flight* temp = head;
    bool found = false;

    cout << "\nAvailable flights from " << srcName << ":\n";
    while (temp) {
        if (temp->src == srcName) {
            found = true;
            cout << "→ To " << temp->dest
                 << " | Time: " << temp->time << " hrs"
                 << " | Fuel: " << temp->fuel << " L\n";
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No flights available from " << srcName << ".\n";
    }
    cout << endl;
}

void graph::indirectFlight() {
    if (!head) {
        cout << "No flight data available.\n";
        return;
    }

    string srcName, destName;
    cout << "Enter source city: ";
    cin >> srcName;
    cout << "Enter destination city: ";
    cin >> destName;

    bool found = false;
    flight* temp = head;

    while (temp) {
        if (temp->src == srcName) {
            string midcity = temp->dest;
            flight* temp2 = head;

            while (temp2) {
                if (temp2->src == midcity && temp2->dest == destName) {
                    found = true;
                    cout << "Indirect Flight available: "
                         << srcName << " -> " << midcity << " -> " << destName << endl;
                }
                temp2 = temp2->next;
            }
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No indirect flight found between " << srcName << " and " << destName << ".\n";
    }
    cout << endl;
}

int main() {
    graph g;
    int choice;

    do {
        cout << "\n----- Flight Management System -----" << endl;
        cout << "1. Read and Display" << endl;
        cout << "2. Check Flight" << endl;
        cout << "3. Display Tours" << endl;
        cout << "4. Check Indirect Flight" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.read();
                g.display();
                break;
            case 2:
                g.checkflight();
                break;
            case 3:
                g.displayTour();
                break;
            case 4:
                g.indirectFlight();
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
