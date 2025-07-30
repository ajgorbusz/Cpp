#include <iostream>
#include <string.h>
#include <cctype>
using namespace std;
void upper_string(string&); //function prototype with reference as argument
int main(){
    string text;
    cout<<"Podaj łańcuch (q, zeby zakończyć): ";
    getline(cin, text); //collect the string (with spaces etc.)
    while(text != "q"){ //while the user doesnt input 'q', the program will run
        upper_string(text);
        cout<<text<<endl;
        cout<<"Następny łańcuch (q, zeby zakończyć): ";
        getline(cin,text);
    }
    cout<<"Do widzenia"<<endl;
    return 0;
}

void upper_string(string& input){

    int str_size = input.size(); //collects the lenghts of inputed string
    for(int i = 0; i < str_size; i++){
        input[i] = toupper(input[i]); //changes every character to uppercase
    }

}