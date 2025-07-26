#include <iostream>

using namespace std;

double silnia(int);

int main(){
    int num;
    cout << "Podaj liczbę, z ktorej chcesz obliczyc silnie: ";
    cin >> num;
    cout << num << "! = " << silnia(num) << endl;
    return 0;
}

double silnia(int n){
    if (n == 1 || n == 0){
        return 1;
    }
    else{
        return n*silnia(n-1);
    }
}