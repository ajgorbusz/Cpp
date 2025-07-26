#include <iostream>
double fun1(int);
double fun2(int);
void estimate(int lines, double (*pf)(int));


int main() {
    using namespace std;
    int code;
    cout << "Ile wierszy kodu nalezy napisać?: ";
    cin >> code;
    cout << "Fun1: " << endl;
    estimate(code, fun1);
    cout << "Fun2: " << endl;
    estimate(code, fun2);

    return 0;
}

double fun1(int lines) {
    return 0.05 * lines;
}

double fun2(int lines) {
    return 0.03 * lines + 0.0004 * lines * lines;
}

void estimate(int lines, double (*pf)(int)) {
    using namespace std;
    cout << lines << " Wierszy wymaga " << (*pf)(lines) << " godzin \n";
}
