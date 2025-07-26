#include <iostream>

using namespace std;
long double probability(unsigned numbers, unsigned pick, unsigned meganum);

int main(){
    double total, choices, meganumber;
    cout << "Podaj liczby (total, choices, meganumber) z przedziału (1-47): \n";
    while ((cin >> total >> choices >> meganumber) && choices <= total && meganumber <= total){
        cout << "Szansa wygranej to 1/";
        cout << probability(total, choices, meganumber) << endl;
        cout << "Podaj następne trzy liczby (q to quit): \n";
    }
    cout << "Goodbye\n";
    return 0;
}

long double probability(unsigned numbers, unsigned picks, unsigned meganum){

    long double result = 1.0;
    long double n;
    unsigned p;
    for(n=numbers, p=picks; p > 0; n--, p--){
        result = result*n/p;
    }

    return result*meganum;

}