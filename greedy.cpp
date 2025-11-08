#include <iostream>
#include <algorithm>
using namespace std;

struct Item{
    double weight;
    double value;
};

bool compare(Item a,Item b){
    double ratio1 = (double)a.value/a.weight;
    double ratio2 = (double)b.value/b.weight;
    return ratio1 > ratio2;
}

double fractionalKnapsack(int capacity,Item items[],int n){
    sort(items,items + n,compare);
    double totalValue = 0.00;
    int currentWeight = 0;

     for(int i = 0;i<n;i++){
        if(currentWeight + items[i].weight <= capacity){
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        }else{
            int remaining = capacity - currentWeight;
            totalValue += items[i].value *((double)remaining/items[i].weight);
            break;
        }
     }
     return totalValue;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    Item items[n];
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }

    double result = fractionalKnapsack(capacity, items, n);
    cout << "Maximum value we can obtain = " << result << endl;

    return 0;
}
