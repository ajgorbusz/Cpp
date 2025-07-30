#include <iostream>
#include <cstring>
using namespace std;
struct stringy{
    char * str;
    int ct;
};

void set(stringy&, const char*);
void show(const stringy&, int = 1);
void show(const char*, int = 1);

int main(){
    stringy beany;
    char testing [] = "Rzeczywistosc to juz nie to, co kiedys.";
    set(beany, testing);
    show(beany);
    show(beany, 2);
    testing[0] = 'D';
    testing[1] = 'U';
    show(testing);
    show(testing,3);
    show("Gotowe!");
    delete [] beany.str;
    return 0;
}

void set(stringy& structure, const char* chara){
    int len = strlen(chara);
    char * ps = new char [len+1];
    strcpy(ps, chara);
    structure.str = ps;
    structure.ct = len;
}

void show(const stringy& structure, int n){
    for(int i = 0; i<n; i++){
        cout<<structure.str<<endl;
    }
    cout<<structure.ct<<endl;
}

void show(const char* m, int n){
    for(int i = 0; i<n; i++){
        cout<<m<<endl;
    }
}
