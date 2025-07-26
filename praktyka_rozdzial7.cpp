#include <iostream>

double srednia_harmoniczna(int, int);

int main(){

    int guess1;
    int guess2;
    std::cout<<"Your guess: \n";
    std::cin >> guess1;
    std::cout<<"Your guess: \n";
    std::cin >> guess2;
    while(true){

        if(guess1 == 0 || guess2 ==0){
            break;
        }

    double anw = srednia_harmoniczna(guess1, guess2);

    std::cout << anw << std::endl;
    std::cout<<"Your guess: \n";
    std::cin >> guess1;
    std::cout<<"Your guess: \n";
    std::cin >> guess2;
    }

    return 0;
}

double srednia_harmoniczna(int x, int y){
    return 2.0*x*y/(x+y);
}