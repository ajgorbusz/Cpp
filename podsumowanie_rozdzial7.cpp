#include <iostream>
#include <string>
/*
Zadanie 1: Jakie są trzy etapy tworzenia i uzycia funkcji?
    1 - prototyp funkcji (co zwraca, jakie argumenty przyjmuje)
    2 - wywolanie funkcji (przyjecie argumentow)
    3 - cialo funkcji (jej zawartosc)

    Zadanie 2
    void igor();
    float tofu(int);
    double mpg(double, double);
    double summation(long [], int);
    double doctor(const char*);
    void oczywiscie(szef);
    char* plot(map *);

    Zadanie 3
    void function(int name[], int size, int n){
        for(int i = 0; i < size, i++){
            name[i] = n;
        }
    }

    Zadanie 4

    void function(int * first, int * last, int n){
        for(int * pr = first; pr != last; pr ++){
            *pr = n;
        }
    }


    Zadanie 5

    double return_highest(double tab[], int size){
        double max = tab[0];
        for(int i = 0; i < size; i++){
            if (tab[i] > max){
                max = tab[i];
            }
        }
        return max;
    }

    Zadanie 8

    int replace(char *str, char c1, char c2){
        int cnt = 0;
        while(*str){

            if(c1 == *str){
                cnt++;
                *str = c2;
            }
            str++;
        }
        return cnt;
    }

    Zadanie 9
    *"pizza" = "pizza"[0] = 'p'
    "taco"[2] = 'c'

    Zadanie 10
    &glitz <- przez adres (nie chroni oryginału, oszczędza czas i pamięć)
    glitz <- przez wartość ( chroni oryginał, czasochłonny i pamięciochłonny
    
    Zadanie 11
    int judge(int (*p1)(const char *));

    Zadanie 12
    struct applicant{
        char name[30];
        int credit_ratings[3];
    };
    
    a) 
    void structure_listing(applicant s){
        std::cout<<"Imie: "<<s.name<<endl;
        for(int i = 0; i < 3; i++){
        std::cout<<"Credit ratings: "<<s.credit_ratings[i]<<endl;
        }
    }
    b)
    void structureAddress_listing(applicant * s){
        std::cout<<"Imie: "<<s->name<<endl;
        for(int i = 0; i< 3; i++){
        std::cout<<"Credit ratings: "<<s->credit_ratings[i]<<endl;
        }
    }

    Zadanie 13
    void f1(applicant *a);
    const char * f2(const applicant *a1, const applicant *a2);
    void (*p1)(applicant *a) = f1;
    const char *(*p2)(const applicant *a1, const applicant *a2) = f2;
    void (*ap)[2](applicant *a) = {f1, f2};
    void (*(*pa)[3])(applicant *a) = &ap;

*/

