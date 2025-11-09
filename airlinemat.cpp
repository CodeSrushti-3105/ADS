#include <iostream>
#include <string>
using namespace std;

class AirlineNetwork {
private:
    int partnership[100][100];
    string airlines[100];
    int n;

public:
    void read();
    void display();
    void checkPartnership();
    void displayConnectedAirlines();
};

void AirlineNetwork::read() {
    cout << "Enter the number of airlines: ";
    cin >> n;

    cout << "Enter the names of the airlines: ";
    for (int i = 0; i < n; i++) {
        cin >> airlines[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            partnership[i][j] = 0;
        }
    }

    char choice;
    int strength;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Do " << airlines[i] << " and " << airlines[j]
                 << " have a partnership? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                cout << "Enter partnership strength or number of shared routes: ";
                cin >> strength;
                partnership[i][j] = partnership[j][i] = strength;
            }
        }
    }
}

void AirlineNetwork::display() {
    cout << "\nAirlines: ";
    for (int i = 0; i < n; i++) {
        cout << airlines[i] << " ";
    }
    cout << endl;

    cout << "\nAdjacency Matrix (Partnership Strength / Shared Routes):\n\t";
    for (int i = 0; i < n; i++) {
        cout << airlines[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << airlines[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << partnership[i][j] << "\t";
        }
        cout << endl;
    }
}

void AirlineNetwork::checkPartnership() {
    string a1, a2;
    cout << "Enter first airline: ";
    cin >> a1;
    cout << "Enter second airline: ";
    cin >> a2;

    int index1 = -1, index2 = -1;
    for (int i = 0; i < n; i++) {
        if (airlines[i] == a1) index1 = i;
        if (airlines[i] == a2) index2 = i;
    }

    if (index1 == -1 || index2 == -1) {
        cout << "Invalid airline name(s)." << endl;
        return;
    }

    if (partnership[index1][index2] != 0) {
        cout << a1 << " and " << a2 << " have a partnership." << endl;
        cout << "Partnership Strength / Shared Routes: " << partnership[index1][index2] << endl;
    } else {
        cout << a1 << " and " << a2 << " do NOT have a direct partnership." << endl;
    }
}

void AirlineNetwork::displayConnectedAirlines() {
    string a1;
    cout << "Enter the airline name: ";
    cin >> a1;

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (airlines[i] == a1) index = i;
    }

    if (index == -1) {
        cout << "Invalid airline name." << endl;
        return;
    }

    cout << "\nAirlines partnered with " << a1 << ":\n";
    bool found = false;

    for (int j = 0; j < n; j++) {
        if (partnership[index][j] != 0) {
            cout << "- " << airlines[j]
                 << " | Partnership Strength / Shared Routes: "
                 << partnership[index][j] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << a1 << " has no partnerships with any other airline." << endl;
    }
}

int main() {
    AirlineNetwork network;
    int choice;

    do {
        cout << "\n----- Airline Partnership Network -----" << endl;
        cout << "1. Read and Display Airline Network" << endl;
        cout << "2. Check Partnership Between Two Airlines" << endl;
        cout << "3. Display All Airlines Connected to a Given Airline" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                network.read();
                network.display();
                break;
            case 2:
                network.checkPartnership();
                break;
            case 3:
                network.displayConnectedAirlines();
                break;
            case 9:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
