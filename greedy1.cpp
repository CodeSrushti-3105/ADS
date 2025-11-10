#include <iostream>
#include <algorithm>
using namespace std;

struct package{
    double weight;
    double benefit;
};

bool compare(package a,package b){
    double ratio1 = (double)a.benefit/a.weight;
    double ratio2 = (double)b.benefit/b.weight;
    return ratio1 > ratio2;
}

double distributedPackages(int capacity,package packages[],int n){
    sort(packages,packages+n,compare);
    double totalbenefit = 0.00;
    int currentweight = 0;
    cout<<"\nPackages Selected\n";
    cout<<"Package\tWeight\tbenefit\tfraction taken\n";

    for(int i = 0;i < n;i++){
        if(currentweight + packages[i].weight <= capacity){
            currentweight +=packages[i].weight;
            totalbenefit += packages[i].benefit;
            cout<<i+1<<"\t"<<packages[i].weight<<"\t"<<packages[i].benefit<<"\t"<<"1.0"<<endl;
        }else{
            double remaining = capacity - packages[i].weight;
            double fraction = (double)remaining/packages[i].weight;
            totalbenefit += fraction*packages[i].benefit;
            currentweight += packages[i].weight * fraction;
            cout<<i+1<<"\t"<<packages[i].weight<<"\t"<<packages[i].benefit<<"\t"<<fraction<<endl;
            break;
        }
    }
    return totalbenefit;
}

int main(){
    int n,capacity;
    cout<<"Enter no, of packages: "<<endl;
    cin>>n;

    cout<<"Capacity: ";
    cin>>capacity;
    package packages[n];

    cout<<"Enter the benefit and weight of each package: "<<endl;
    for(int i = 0;i<n;i++){
        cin>>packages[i].weight>>packages[i].benefit;
    }
    double result = distributedPackages(capacity,packages,n);
    cout<<"Total benefit of: "<<result<<endl;
    return 0;
}