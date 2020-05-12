# Biginteger library for C++
Includes all basic operations and multiple algorithms, easy to use.

Some implemented algorithms:
* karatsuba algorithm (Fast multiplication)
* Euclidean algorithm
* Extended Euclidean algorithm
* Binary exponentiation
* Modular exponentiation

##supports
* Operators: +, -, *, /, %, +=, -=, *=, /=, %=, ++, --
* Comparators: <, >, <=, >=, ==, !=
* Functions: max, min, gcd, lcm, pow, log, sqrt, gcd_ex, expmod

##Example

```c++
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
```
