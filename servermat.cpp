#include <iostream>
#include <string>
using namespace std;

class ServerNetwork {
private:
    int speed[100][100];
    int latency[100][100];
    string servers[100];
    int n;

public:
    void read();
    void display();
    void checkReachability();
    void dfs(int v, bool visited[]);
};

void ServerNetwork::read() {
    cout << "Enter the number of servers: ";
    cin >> n;

    cout << "Enter the names of the servers: ";
    for (int i = 0; i < n; i++) {
        cin >> servers[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            speed[i][j] = -1;
            latency[i][j] = -1;
        }
    }

    char choice;
    int s, l;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Is there a direct cable between " << servers[i]
                 << " and " << servers[j] << "? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                cout << "Enter data transfer speed (Mbps): ";
                cin >> s;
                cout << "Enter latency (ms): ";
                cin >> l;
                speed[i][j] = speed[j][i] = s;
                latency[i][j] = latency[j][i] = l;
            }
        }
    }
}

void ServerNetwork::display() {
    cout << "\nServers: ";
    for (int i = 0; i < n; i++) {
        cout << servers[i] << " ";
    }
    cout << endl;

    cout << "\nSpeed Matrix (in Mbps):\n\t";
    for (int i = 0; i < n; i++) {
        cout << servers[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << servers[i] << "\t";
        for (int j = 0; j < n; j++) {
            if (speed[i][j] == -1)
                cout << "0\t";
            else
                cout << speed[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nLatency Matrix (in ms):\n\t";
    for (int i = 0; i < n; i++) {
        cout << servers[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << servers[i] << "\t";
        for (int j = 0; j < n; j++) {
            if (latency[i][j] == -1)
                cout << "0\t";
            else
                cout << latency[i][j] << "\t";
        }
        cout << endl;
    }
}

void ServerNetwork::dfs(int v, bool visited[]) {
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (speed[v][i] != -1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

void ServerNetwork::checkReachability() {
    string src;
    cout << "Enter the source server: ";
    cin >> src;

    int srcIndex = -1;
    for (int i = 0; i < n; i++) {
        if (servers[i] == src)
            srcIndex = i;
    }

    if (srcIndex == -1) {
        cout << "Invalid server name.\n";
        return;
    }

    bool visited[100] = {false};
    dfs(srcIndex, visited);

    cout << "\nChecking reachability from " << src << "...\n";

    bool allReachable = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << servers[i] << " is NOT reachable from " << src << endl;
            allReachable = false;
        }
    }

    if (allReachable)
        cout << "All servers are reachable from " << src << "." << endl;
}

int main() {
    ServerNetwork network;
    int choice;

    do {
        cout << "\n----- Server Network System -----" << endl;
        cout << "1. Read and Display Network" << endl;
        cout << "2. Check Server Reachability" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                network.read();
                network.display();
                break;
            case 2:
                network.checkReachability();
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
