#include <iostream>
#include <string>

const int Seasons = 4;
using namespace std;
const char * Snames = {"Wiosna", "Lato", "Jesień", "Zima"};
void fill(array<double, Seasons> * pa);
void show(array<double, Seasons> da);

int main(){
    double expenses = [];
    fill(&expenses);
    show(expenses);
    return 0;
}

void fill(const char * pa){
    for(int i = 0; i<Seasons; i++){
        cout<< "Podaj wydatki za okres " << Snames[i] << " : ";
        cin>>(*pa)[i];
    }
}

void show(const char * da){
    double total = 0.0;
    cout << "\nWydatki\n";
    for(int i = 0; i < Seasons; i++){
        cout<<Snames[i]<<": "<<da[i]<<" zł\n";
        total+=da[i];
    }
    cout<<"Łączne wydatki roczne: "<<total<<" zł\n";
}
