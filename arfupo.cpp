#include <iostream>

const double * f1(const double ar[], int n);
const double * f2(const double [], int);
const double * f3(const double *, int);

int main(){
    using namespace std;
    double av[3] = {1112.2, 1345.56, 1999.69};
    const double * (*p1)(const double *, int) = f1;
    const double * (*p2)(const double *, int) = f2;

    cout << "Uzywanie wskaznikow do funkcji: \n";
    cout << "Adres\tWartość Zwracana\n";
    cout << (*p1)(av, 3) << ":\t" << *(*p1)(av, 3) << endl;
    cout << (*p2)(av, 3) << ":\t" << *(*p2)(av, 3) << endl;

    const double* (*pa[3])(const double *, int) = {f1, f2, f3};

    const double* (**pb)(const double *, int) = pa;

    cout << "\nUzywanie tablicy wskaznikow do funkcji:\n";
    cout << "Adres\t Wartosc Zwracana\n";
    for(int i = 0; i < 3; i++){
        cout << pa[i](av, 3) << ":\t" << *pa[i](av, 3) << endl;
    }
    cout << "\nUzywanie wskaźnika do wskaznika do funkcji:\n";
    cout << "Adres\t Wartosc Zwracana\n";
    for(int i = 0; i < 3; i++){
        cout << pb[i](av, 3) << ":\t" << *pb[i](av, 3) << endl;
    }

    cout << "\nUzywanie wskaźnika do tablicy wskaznikow do funkcji:\n";
    cout << "Adres\t Wartosc Zwracana\n";

    const double * (*(*pc)[3])(const double *, int) = &pa;

    cout << (*pc)[0](av, 0) << ":\t" << *(*pc)[0](av, 3) << endl;

    const double* (*(*pd)[3])(const double *, int) = &pa;

    const double * pdb = (*pd)[1](av, 3);
    cout << pdb << ":\t" << *pdb << endl;
    cout << (*(*pd)[2])(av, 3) << ":\t" << *(*(*pd)[2])(av, 3) << endl;
    return 0;
}

const double * f1(const double * ar, int n){
    return ar;
}

const double * f2(const double ar[], int n){
    return ar+1;
}

const double * f3(const double ar[], int n){
    return ar+2;
}
