/*
    A company receives multiple job requests, each with a priority value.
    The manager wants to process the most important (highest priority) job first and also identify the least
    priority one for deferred execution.
    Write a menu-driven C++ program using Max Heap and Min Heap to perform the following
    operations:

    1. Insert a new job with its priority.

    2. Find and display the highest and lowest priority jobs.

    3. Delete the job with the highest priority.

    4. Display all jobs in order of priority.
    Also, analyze the time complexity of each operation (Insert, Delete, Find-Min/Find-Max).
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//-------------------- MAX HEAP CLASS --------------------//
class max_heap {
    vector<pair<string, int>> heap; // {jobName, priority}
    int getLeftChild(int);
    int getRightChild(int);
    int getParent(int);
    void heap_up(int);
    void heap_down(int);
public:
    void insert(string, int);
    pair<string, int> delete_max();
    pair<string, int> get_max();
    void display();
    bool empty() { return heap.empty(); }
};

int max_heap::getLeftChild(int i) { return 2 * i + 1; }
int max_heap::getRightChild(int i) { return 2 * i + 2; }
int max_heap::getParent(int i) { return (i - 1) / 2; }

void max_heap::heap_up(int i) {
    while (i > 0 && heap[getParent(i)].second < heap[i].second) {
        swap(heap[getParent(i)], heap[i]);
        i = getParent(i);
    }
}

void max_heap::heap_down(int i) {
    int largest = i;
    int left = getLeftChild(i);
    int right = getRightChild(i);

    if (left < heap.size() && heap[left].second > heap[largest].second) largest = left;
    if (right < heap.size() && heap[right].second > heap[largest].second) largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heap_down(largest);
    }
}

void max_heap::insert(string job, int priority) {
    heap.push_back({job, priority});
    heap_up(heap.size() - 1);
}

pair<string, int> max_heap::delete_max() {
    if (heap.empty()) {
        cout << "No jobs available.\n";
        return {"", -1};
    }
    swap(heap[0], heap.back());
    pair<string, int> res = heap.back();
    heap.pop_back();
    if (!heap.empty()) heap_down(0);
    return res;
}

pair<string, int> max_heap::get_max() {
    if (heap.empty()) return {"", -1};
    return heap[0];
}

void max_heap::display() {
    for (auto &job : heap)
        cout << job.first << " (Priority: " << job.second << ")  ";
    cout << endl;
}

//-------------------- MIN HEAP CLASS --------------------//
class min_heap {
    vector<pair<string, int>> heap;
    int getLeftChild(int);
    int getRightChild(int);
    int getParent(int);
    void heap_up(int);
    void heap_down(int);
public:
    void insert(string, int);
    pair<string, int> delete_min();
    pair<string, int> get_min();
    void display();
    bool empty() { return heap.empty(); }
};

int min_heap::getLeftChild(int i) { return 2 * i + 1; }
int min_heap::getRightChild(int i) { return 2 * i + 2; }
int min_heap::getParent(int i) { return (i - 1) / 2; }

void min_heap::heap_up(int i) {
    while (i > 0 && heap[getParent(i)].second > heap[i].second) {
        swap(heap[getParent(i)], heap[i]);
        i = getParent(i);
    }
}

void min_heap::heap_down(int i) {
    int smallest = i;
    int left = getLeftChild(i);
    int right = getRightChild(i);

    if (left < heap.size() && heap[left].second < heap[smallest].second) smallest = left;
    if (right < heap.size() && heap[right].second < heap[smallest].second) smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heap_down(smallest);
    }
}

void min_heap::insert(string job, int priority) {
    heap.push_back({job, priority});
    heap_up(heap.size() - 1);
}

pair<string, int> min_heap::delete_min() {
    if (heap.empty()) {
        cout << "No jobs available.\n";
        return {"", -1};
    }
    swap(heap[0], heap.back());
    pair<string, int> res = heap.back();
    heap.pop_back();
    if (!heap.empty()) heap_down(0);
    return res;
}

pair<string, int> min_heap::get_min() {
    if (heap.empty()) return {"", -1};
    return heap[0];
}

void min_heap::display() {
    for (auto &job : heap)
        cout << job.first << " (Priority: " << job.second << ")  ";
    cout << endl;
}

//-------------------- MAIN PROGRAM --------------------//
int main() {
    max_heap maxH;
    min_heap minH;

    int choice, priority;
    string job;

    cout << "\n--- Job Priority Manager ---\n";

    while (true) {
        cout << "\n1. Insert a new Job";
        cout << "\n2. Display Highest and Lowest Priority Jobs";
        cout << "\n3. Delete Highest Priority Job";
        cout << "\n4. Display All Jobs (Max Heap)";
        cout << "\n5. Display All Jobs (Min Heap)";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Job Name: ";
                cin >> job;
                cout << "Enter Job Priority: ";
                cin >> priority;
                maxH.insert(job, priority);
                minH.insert(job, priority);
                cout << "Job inserted successfully.\n";
                break;

            case 2: {
                if (maxH.empty()) {
                    cout << "No jobs available.\n";
                } else {
                    auto high = maxH.get_max();
                    auto low = minH.get_min();
                    cout << "\nHighest Priority Job: " << high.first << " (Priority: " << high.second << ")";
                    cout << "\nLowest Priority Job: " << low.first << " (Priority: " << low.second << ")\n";
                }
                break;
            }

            case 3: {
                if (maxH.empty()) cout << "No jobs to delete.\n";
                else {
                    auto removed = maxH.delete_max();
                    cout << "\nDeleted Job with Highest Priority: " << removed.first << " (Priority: " << removed.second << ")\n";
                }
                break;
            }

            case 4:
                cout << "\nAll Jobs in Max Heap: ";
                maxH.display();
                break;

            case 5:
                cout << "\nAll Jobs in Min Heap: ";
                minH.display();
                break;

            case 6:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

/*
-------------------- ALGORITHM ANALYSIS --------------------

1. Insert (insert()):
   - Adds job at the end and heapifies upward.
   - Time Complexity: O(log n)
   - Space Complexity: O(1)

2. Delete (delete_max() / delete_min()):
   - Swaps root with last element, removes it, then heapifies downward.
   - Time Complexity: O(log n)
   - Space Complexity: O(1)

3. Find Highest / Lowest Priority:
   - Root of Max Heap = Highest priority
   - Root of Min Heap = Lowest priority
   - Time Complexity: O(1)
   - Space Complexity: O(1)

4. Display:
   - Traverses the heap vector.
   - Time Complexity: O(n)
   - Space Complexity: O(1)

Overall:
   - Building Heap (n insertions): O(n log n)
   - Efficient for job scheduling systems.
*/
