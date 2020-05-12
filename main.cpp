#include <iostream>
#include "biginteger.h"
#include "bigintegerMath.h"

using namespace std;

int main(){
    string str = "1000";
    biginteger a = 1, b = str;
    biginteger mod, result;
    while(cin >> mod){
		a = a + 1;
        result = expmod(a, b, mod);//modular exponentiation
        cout << result << endl;
    }
    return 0;
}
