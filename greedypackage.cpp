#include <iostream>
#include <algorithm>
using namespace std;

struct package{
    int weight;
    int benefit;
};

bool compare(package a,package b){
    double ratio1 = (double)a.benefit/a.weight;
    double ratio2 = (double)b.benefit/b.weight;
    return ratio1 > ratio2;
}

double distributePackages(int capacity,package packages[],int n){
    sort(packages,packages + n,compare);

    double totalbenefit = 0.00;
    int currentWeight = 0;

    cout<<"\nPackages Selected\n";
    cout<<"Package\tWeight\tbenefit\tfraction taken\n";

    for(int i = 0;i<n;i++){
        if(currentWeight + packages[i].weight <= capacity){
            currentWeight += packages[i].weight;
            totalbenefit += packages[i].benefit;
            cout<<i+1<<"\t"<<packages[i].weight<<"\t\t"<<packages[i].benefit<<"\t"<<"1.0"<<endl;
            
        }else{
            double remaining = capacity - currentWeight;
            double fraction = (double)remaining/packages[i].weight;
            totalbenefit +=  packages[i].benefit * fraction;
            currentWeight += packages[i].weight * fraction;
            cout<<i+1<<"\t"<<packages[i].weight<<"\t\t"<<packages[i].benefit<<"\t"<<fraction<<endl;
            break;
        }
    }
    return totalbenefit;
}
int main(){
    int n,capacity;
    cout<<"Enter the no. of packages: ";
    cin>> n;
    cout<<"Enter the capacity: ";
    cin>> capacity;

    package packages[n];
    cout<<"Enter the benefit and the weight: "<<endl;
    for(int i = 0;i < n;i++){
        cin>>packages[i].benefit>>packages[i].weight;
    }
    double result = distributePackages(capacity,packages,n);
    cout<<"Total benefit obtained: "<<result<<endl;
    return 0;
}