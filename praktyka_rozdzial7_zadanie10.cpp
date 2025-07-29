#include <iostream>
using namespace std;
const int SIZE = 4;

double calculate(double, double, const double *);

double add(double a, double b){
    return a + b;
}
double divide(double a, double b){
    return b != 0 ? a / b : 0;
}
double multiply(double a, double b){
    return b != 0 ? a * b : 0;
}
double substract(double a, double b){
    return a - b;
}

int main(){
    double (*pf[SIZE])(double, double) = {add, divide, multiply, substract};
    char* description[SIZE] = {"Dodawanie", "Dzielenie", "Mnozenie", "Odejmowanie"};
    double a, b;
    cout << "Wpisz dwie cyfry, ja wykonam na nich podstawowe działania matematyczne: ";
    cin >> a >> b;
    for(int i = 0; i < SIZE; i++){
        cout << description[i] << ": " << pf[i](a, b) <<endl;
    }
    return 0;
}