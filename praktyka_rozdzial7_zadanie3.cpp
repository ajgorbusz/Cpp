#include <iostream>
using namespace std;

struct pudlo{
    char producent[40];
    float wysokosc;
    float szerokosc;
    float dlugosc;
    float objetosc;
};

void AshowStruct(pudlo stucture);
void BshowStruct(pudlo * pstruct);

int main(){
    pudlo p1 = {"Skibidi Rizzler", 30.0, 40.0, 10.5};
    pudlo p2 = {"Adolfus Hitlerus", 69.6, 420.89, 10.54};
    p1.objetosc = p1.wysokosc * p1.dlugosc * p1.szerokosc;
    AshowStruct(p1);
    BshowStruct(&p2);
    return 0;
}

void AshowStruct(pudlo structure){
    cout<<"Producent: " << structure.producent << endl;
    cout<<"Wysokosc: " << structure.wysokosc << endl;
    cout<<"Szerokosc: " << structure.szerokosc << endl;
    cout<<"Dlugosc: " << structure.dlugosc << endl;
    cout<<"Objetosc: " << structure.objetosc << endl;

}

void BshowStruct(pudlo * pstruct){
    pstruct->objetosc = pstruct->dlugosc * pstruct->szerokosc * pstruct->wysokosc;
    cout << "Objetosc p2: " << pstruct->objetosc << endl;

}