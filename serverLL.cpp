#include <iostream>
using namespace std;

struct node {
    string src;
    string dest;
    int distance;
    node *next;
};

class graph {
private:
    string intersections[20];
    int n;
    node *head;

public:
    graph() {
        head = nullptr;
    }

    void read();
    void display();
    void directroad();
    void allroad();
};

void graph::read() {
    cout << "Enter the number of intersections: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter the name of intersection " << i + 1 << ": ";
        cin >> intersections[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char choice;
            cout << "Is there any road present from " << intersections[i]
                 << " to " << intersections[j] << "? (Y/N): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                int d;
                cout << "Enter the distance (in km): ";
                cin >> d;

                // Add both directions since roads are bidirectional
                node *newRoad1 = new node{intersections[i], intersections[j], d, head};
                head = newRoad1;

                node *newRoad2 = new node{intersections[j], intersections[i], d, head};
                head = newRoad2;
            }
        }
    }
    cout << "\n Road data recorded successfully.\n";
}

void graph::display() {
    if (!head) {
        cout << "\n No road data available.\n";
        return;
    }

    cout << "\n--- City Road Connections ---\n";
    node *temp = head;
    while (temp) {
        cout << temp->src << " -> " << temp->dest
             << " | Distance: " << temp->distance << " km\n";
        temp = temp->next;
    }
    cout << endl;
}

void graph::directroad() {
    if (!head) {
        cout << "\n No road data available.\n";
        return;
    }

    string a, b;
    cout << "\nEnter two intersections to check direct road:\n";
    cout << "From: ";
    cin >> a;
    cout << "To: ";
    cin >> b;

    node *temp = head;
    while (temp) {
        if (temp->src == a && temp->dest == b) {
            cout << " Direct road exists between " << a << " and " << b
                 << " (" << temp->distance << " km)\n";
            return;
        }
        temp = temp->next;
    }

    cout << " No direct road exists between " << a << " and " << b << ".\n";
}

void graph::allroad() {
    if (!head) {
        cout << "\nNo road data available.\n";
        return;
    }

    string a;
    cout << "\nEnter intersection name to display all connecting roads: ";
    cin >> a;

    node *temp = head;
    bool found = false;

    cout << "\nRoads connected to " << a << ":\n";
    while (temp) {
        if (temp->src == a) {
            found = true;
            cout << "->" << temp->dest << " (" << temp->distance << " km)\n";
        }
        temp = temp->next;
    }

    if (!found)
        cout << "No connecting roads found for " << a << ".\n";
}

int main() {
    graph g;
    int choice;

    do {
        cout << "\n=====  City Road Map Menu =====\n";
        cout << "1. Enter Road Data\n";
        cout << "2. Display All Roads\n";
        cout << "3. Check Direct Road\n";
        cout << "4. Display Roads from a Specific Intersection\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.read();
                break;
            case 2:
                g.display();
                break;
            case 3:
                g.directroad();
                break;
            case 4:
                g.allroad();
                break;
            case 5:
                cout << " Exiting the program... Goodbye!\n";
                break;
            default:
                cout << " Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
