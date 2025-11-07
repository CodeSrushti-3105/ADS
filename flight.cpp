#include <iostream>
#include <string>
using namespace std;

class graph {
private:
    int time[100][100];
    int fuel[100][100];
    string cities[100];
    int n;

public:
    void read();
    void display();
    void checkFlight();
    void displayTour();
    void checkindirectFlight();
};

void graph::read() {
    cout << "Enter the number of the cities: ";
    cin >> n;

    cout << "Enter the names of the cities: ";
    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }

    cout << "Enter the time and fuel matrix..." << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            time[i][j] = -1;
            fuel[i][j] = -1;
        }
    }

    char choice;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "Is there any flight between " << cities[i]
                     << " and " << cities[j] << " (Y or N): ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    cout << "Enter the time required from " << cities[i]
                         << " to " << cities[j] << ": ";
                    cin >> time[i][j];

                    cout << "Enter the fuel required from " << cities[i]
                         << " to " << cities[j] << ": ";
                    cin >> fuel[i][j];
                }
            }
        }
    }
    cout << endl;
}

void graph::display() {
    cout << "Cities list: ";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << " ";
    }
    cout << endl;

    cout << "\nTime Matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;

    for (int j = 0; j < n; j++) {
        cout << cities[j] << "\t";
        for (int i = 0; i < n; i++) {
            if (time[j][i] == -1)
                cout << "0\t";
            else
                cout << time[j][i] << "\t";
        }
        cout << endl;
    }

    cout << "\nFuel Matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;

    for (int j = 0; j < n; j++) {
        cout << cities[j] << "\t";
        for (int i = 0; i < n; i++) {
            if (fuel[j][i] == -1)
                cout << "0\t";
            else
                cout << fuel[j][i] << "\t";
        }
        cout << endl;
    }
}

void graph::checkFlight() {
    if (n == 0) {
        cout << "Data is not available!" << endl;
        return;
    }

    string src, dest;
    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    int srcIndex = -1, destIndex = -1;
    for (int i = 0; i < n; i++) {
        if (cities[i] == src) srcIndex = i;
        if (cities[i] == dest) destIndex = i;
    }

    if (srcIndex == -1 || destIndex == -1) {
        cout << "Invalid source or destination city.\n";
        return;
    }

    if (time[srcIndex][destIndex] != -1) {
        cout << "Flight exists between " << src << " and " << dest << endl;
        cout << "Time required: " << time[srcIndex][destIndex] << endl;
        cout << "Fuel required: " << fuel[srcIndex][destIndex] << endl;
    } else {
        cout << "There is no direct flight between " << src << " and " << dest << "." << endl;
    }
}

void graph::displayTour() {
    string src;
    cout << "Enter the source city: ";
    cin >> src;

    int srcIndex = -1;
    for (int i = 0; i < n; i++) {
        if (cities[i] == src) srcIndex = i;
    }

    if (srcIndex == -1) {
        cout << "Invalid source city.\n";
        return;
    }

    cout << "\nAvailable flights from " << src << ":\n";
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (time[srcIndex][i] != -1) {
            cout << "To " << cities[i]
                 << " | Time: " << time[srcIndex][i]
                 << " | Fuel: " << fuel[srcIndex][i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No flights available from " << src << "." << endl;
    }

    cout << endl;
}

void graph::checkindirectFlight() {
    string src, dest;
    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    int srcIndex = -1, destIndex = -1;

    for (int i = 0; i < n; i++) {
        if (cities[i] == src) srcIndex = i;
        if (cities[i] == dest) destIndex = i;
    }

    if (srcIndex == -1 || destIndex == -1) {
        cout << "Invalid source or destination city.\n";
        return;
    }

    bool found = false;
    for (int j = 0; j < n; j++) {
        if (time[srcIndex][j] != -1 && time[j][destIndex] != -1) {
            found = true;
            cout << "Indirect flight available: "
                 << src << " -> " << cities[j] << " -> " << dest << endl;
        }
    }

    if (!found) {
        cout << "No indirect flight available between "
             << src << " and " << dest << "." << endl;
    }
}

int main() {
    graph g;
    int choice;

    do {
        cout << "\n----- Flight Management System -----" << endl;
        cout << "1. Read and Display" << endl;
        cout << "2. Check Flight" << endl;
        cout << "3. Check Tour" << endl;
        cout << "4. Check Indirect Flight" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.read();
                g.display();
                break;
            case 2:
                g.checkFlight();
                break;
            case 3:
                g.displayTour();
                break;
            case 4:
                g.checkindirectFlight();
                break;
            case 9:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);
}
