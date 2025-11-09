#include <iostream>
#include <algorithm>
using namespace std;

struct Task {
    double executionTime;
    double profit;
};

bool compare(Task a, Task b) {
    double ratio1 = (double)a.profit / a.executionTime;
    double ratio2 = (double)b.profit / b.executionTime;
    return ratio1 > ratio2;
}

double maximizeProfit(int totalTime, Task tasks[], int n) {
    sort(tasks, tasks + n, compare);
    double totalProfit = 0.00;
    int currentTime = 0;

    cout << "\nTasks scheduled:\n";
    cout << "Task\tExecution Time\tProfit\tFraction Taken\n";

    for (int i = 0; i < n; i++) {
        if (currentTime + tasks[i].executionTime <= totalTime) {
            currentTime += tasks[i].executionTime;
            totalProfit += tasks[i].profit;
            cout << i + 1 << "\t" << tasks[i].executionTime << "\t\t"
                 << tasks[i].profit << "\t" << "1.0" << endl;
        } else {
            int remaining = totalTime - currentTime;
            double fraction = (double)remaining / tasks[i].executionTime;
            totalProfit += tasks[i].profit * fraction;
            cout << i + 1 << "\t" << tasks[i].executionTime << "\t\t"
                 << tasks[i].profit << "\t" << fraction << endl;
            break;
        }
    }

    return totalProfit;
}

int main() {
    int n, totalTime;
    cout << "Enter number of tasks: ";
    cin >> n;

    cout << "Enter total available processing time (T): ";
    cin >> totalTime;

    Task tasks[n];
    cout << "Enter profit and execution time of each task:\n";
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].profit >> tasks[i].executionTime;
    }

    double result = maximizeProfit(totalTime, tasks, n);
    cout << "\nTotal profit achieved = " << result << endl;

    return 0;
}
