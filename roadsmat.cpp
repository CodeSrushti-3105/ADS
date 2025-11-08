#include <iostream>
using namespace std;

class graph {
private:
    int length[100][100];
    int time[100][100];
    string interconnections[20];
    int n;
public:
    void read();
    void display();
    void directRoad();
    void allroads();
};

void graph::read() {
    cout << "Enter number of interconnections: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter the name of intersection " << i + 1 << ": ";
        cin >> interconnections[i];
    }

    // Initialize all roads with -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            length[i][j] = -1;
            time[i][j] = -1;
        }
    }

    char choice;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "Is there any direct road from " 
                     << interconnections[i] << " to " 
                     << interconnections[j] << "? (y/n): ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    cout << "Enter the length (in km): ";
                    cin >> length[i][j];
                    cout << "Enter the time (in min): ";
                    cin >> time[i][j];
                }
            }
        }
    }
    cout << "\nData recorded successfully!\n\n";
}

void graph::display() {
    cout << "\n--- Interconnections List ---\n";
    for (int i = 0; i < n; i++) {
        cout << interconnections[i] << " ";
    }
    cout << "\n\n--- Length Matrix (km) ---\n\t";

    for (int i = 0; i < n; i++) {
        cout << interconnections[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << interconnections[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << (length[i][j] == -1 ? 0 : length[i][j]) << "\t";
        }
        cout << endl;
    }

    cout << "\n--- Time Matrix (min) ---\n\t";
    for (int i = 0; i < n; i++) {
        cout << interconnections[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << interconnections[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << (time[i][j] == -1 ? 0 : time[i][j]) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void graph::directRoad() {
    string src_int, dest_int;
    cout << "\nEnter the source intersection: ";
    cin >> src_int;
    cout << "Enter the destination intersection: ";
    cin >> dest_int;

    int srcIndex = -1, destIndex = -1;
    for (int i = 0; i < n; i++) {
        if (interconnections[i] == src_int) srcIndex = i;
        if (interconnections[i] == dest_int) destIndex = i;
    }

    if (srcIndex == -1 || destIndex == -1) {
        cout << "Invalid intersection name(s)!\n\n";
        return;
    }

    if (length[srcIndex][destIndex] != -1) {
        cout << "\n Road is available!\n";
        cout << "Length: " << length[srcIndex][destIndex] << " km\n";
        cout << "Time: " << time[srcIndex][destIndex] << " min\n";
    } else {
        cout << "\n No direct road found between these intersections.\n";
    }
    cout << endl;
}

void graph::allroads() {
    string src_int;
    cout << "\nEnter source intersection: ";
    cin >> src_int;

    int srcIndex = -1;
    for (int i = 0; i < n; i++) {
        if (interconnections[i] == src_int)
            srcIndex = i;
    }

    if (srcIndex == -1) {
        cout << "Invalid intersection name!\n\n";
        return;
    }

    cout << "\nRoads from " << src_int << ":\n";
    bool found = false;
    for (int j = 0; j < n; j++) {
        if (length[srcIndex][j] != -1) {
            cout << "→ To " << interconnections[j]
                 << " | Length: " << length[srcIndex][j] << " km"
                 << " | Time: " << time[srcIndex][j] << " min\n";
            found = true;
        }
    }

    if (!found)
        cout << "No direct roads found from this intersection.\n";

    cout << endl;
}

int main() {
    graph g;
    int choice;
    do {
        cout << "---- Intersection Management ----" << endl;
        cout << "1. Read and display" << endl;
        cout << "2. Direct connection" << endl;
        cout << "3. All connections" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            g.read();
            g.display();
            break;
        case 2:
            g.directRoad();
            break;
        case 3:
            g.allroads();
            break;
        case 4:
            cout << "Exiting the code..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}
