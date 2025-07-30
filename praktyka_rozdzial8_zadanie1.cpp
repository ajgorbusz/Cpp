#include <iostream>
using namespace std;

const int SIZE = 50; //table size
int shown = 0; //how many times the funciton was called
void show_string(const char*, int n = 0); //function prototype

int main(){
    
    char *var = new char[SIZE];//dynamic table
    cout<<"Wpisuj znaki: ";
    cin.get(var, SIZE).get(); //collect user's data .get() at the end to collect '\n'

    show_string(var);
    show_string(var); //two function calls with second argument being common

    for(int i = 1; i <= 5; i++){
        show_string(var, 5); // 4 function calls with second argument being a no-zero
    }
    delete [] var; //free the memory
    return 0;

}

void show_string(const char* character, int n){

    if (n != 0){ //check if the second argument is common or not
        for(int i = 0; i < shown; i++){ //for loop based on how many times the function was called
            cout<<i+1<<". "<<character<<endl;
        }
    }
    else{
        cout<<character<<endl;
    }
    shown++; //adds +1 to the shown value (because the function was called)
}
