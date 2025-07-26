#include <iostream>
#include <string>
using namespace std;

const int SLEN = 30;
struct student{
    char fullname[SLEN];
    char hobby[SLEN];
    int ooplevel;
};
int getinfo(student pa[], int n);
void display1(student st);
void display2(const student * ps);
void display3(const student pa[], int n);

int main(){
    cout<<"Podaj wielkosc grupy: ";
    int class_size;
    cin>>class_size;
    while(cin.get() != '\n'){
        continue;
    }
    student * ptr_stu = new student[class_size];
    int entered = getinfo(ptr_stu, class_size);
    for(int i = 0; i < entered; i++){
        display1(ptr_stu[i]);
        display2(&ptr_stu[i]);
    }
    display3(ptr_stu, entered);
    delete [] ptr_stu;
    cout << "Gotowe\n";
    return 0;
}

int getinfo(student pa[], int n){
    int cnt = 0;
    for(int i = 0; i < n; i++){
        cout<<"Podaj imie "<<i+1<<". studenta: \n";
        cin.getline((pa+i)->fullname, SLEN);
        if ((pa+i)->fullname[0] == '\0'){
            break;
        }
        cout<<"Podaj hobby "<<i+1<<". studenta: \n";
        cin.getline((pa+i)->hobby, SLEN);
        cout<<"Podaj object-oriented programming level (1-3) "<<i+1<<". studenta: \n";
        cin >> (pa+i)->ooplevel;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cnt += 1;
    }
    return cnt;
}

void display1(student st){
    cout << st.fullname << ", " << st.hobby << ", " << st.ooplevel << endl;
    cout<<"\n";
}
void display2(const student* ps){
    cout << ps->fullname << ", " << ps->hobby << ", " << ps->ooplevel << endl;
    cout<<"\n";
}
void display3(const student pa[], int n){
    for(int i = 0; i < n; i++){
        cout << "Student nr "<<i+1<<". :\n";
        cout << pa[i].fullname << ", " << pa[i].hobby << ", " << pa[i].ooplevel << endl;
        cout<<"\n";
    }
}

