#include <iostream>
#include "biginteger.h"
#include "bigintegerMath.h"

using namespace std;

int main(){
    //freopen("salida.txt", "w", stdout);
    string n, m;
    biginteger a;

    while(cin >> a){
        biginteger r = sqrt(a);
        biginteger p = pow(a, 1000LL);
        cout << "sqrt: " << r << endl;
        cout << "power: " << p << endl;
    }

    return 0;
}
