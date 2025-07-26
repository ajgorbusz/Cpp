#include <iostream>
#include <cctype>
#include <string.h>
using namespace std;
int * dataInput(int&);
void dataOutput(int *, int);
void dataAvg(int *, int);

int main(){
    int size = 0;
    int *results = dataInput(size);
    dataOutput(results, size);
    dataAvg(results, size);
    delete [] results;
    return 0;
}

int * dataInput(int& size){
    cout<<"Input the results: (enter 'q', to finish)\n";
    int *golf_results = new int[10];
    string input;
    size = 0;
    for(int i =0; i < 10; i++){

        cin >> input;
        if(input == "q"){
            cout<<"Input finished by user.\n";
            break;
        }

        try {
            golf_results[i] = stoi(input);
            size++;
        } catch (...) {
            cout << "Incorrect data type (int expected). Try again:\n";
            --i;
        }
    }
    
    return golf_results;
}

void dataOutput(int *table, int size){
    for(int i = 0; i<size; i++){
        cout << table[i] << ", ";
    }
}

void dataAvg(int *table, int size){
    int sum = 0;
    double avg = 0.0;
    for(int i = 0; i < size; i++){
        sum += table[i];
    }
    avg = static_cast<double>(sum)/size;
    cout << "\nAvarage: " << avg << endl;
}