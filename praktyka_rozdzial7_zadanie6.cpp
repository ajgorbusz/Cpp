#include <iostream>
#include <string>
using namespace std;

int fill_array(double*, int);
void show_array(double*, int);

int main(){
    int size;
    cout << "Please input size of the table: ";
    cin >> size;
    while(size<=0){
        cout<<"Incorrect value. Try again: ";
        cin >> size;
    }
    double *name = new double[size];
    int result = fill_array(name, size);
    cout << "Liczba wprowadzonych wartosci: " << result << endl;
    show_array(name, result);
    delete [] name;
}

int fill_array(double *ptr, int size){
    int cnt = 0;
    double value;
    cout << "Podawaj wartości double (przerwanie przy wypełnieniu tablicy || podaniu nieprawidłowej wartości): \n";
    while(cnt < size && (cin >> value)){
        ptr[cnt] = value;
        cnt++;
    }   
    return cnt;
}

void show_array(double *ptr, int size){
    cout<<"Wpisane wartości: "<<endl;
    for(int i = 0; i<size; i++){
        cout<<ptr[i]<<endl;
    }
}
