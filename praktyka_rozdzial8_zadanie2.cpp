#include <iostream>
using namespace std;

const int SIZE = 30; //initialize size of mark table

struct Batonik{ //structure with 3 elements
    char marka[SIZE];
    float waga;
    int kalorie;
};

void str_fun(Batonik&, const char* = "Millenium Munch", double = 2.85, int = 350); //function prototype with common arguments

int main(){
    Batonik moj_baton; //declare structure
    str_fun(moj_baton); //call function with arguments being the common ones
    return 0;
}

void str_fun(Batonik& structure, const char* mark, double weight, int calories){ //function definition
    strcpy(structure.marka, mark); //copy the mark string into the structure.marka
    structure.kalorie = calories; //set calories
    structure.waga = weight; // set weight

    //print the values
    cout<<"MARKA: "<<structure.marka<<endl;
    cout<<"KALORIE: "<<structure.kalorie<<endl;
    cout<<"WAGA: "<<structure.waga<<endl;
}