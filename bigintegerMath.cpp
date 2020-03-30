#include "bigintegerMath.h"

biginteger max(biginteger a, biginteger b) {
    return (a > b)? a: b;
}
biginteger min(biginteger a, biginteger b) {
    return (a < b)? a: b;
}
biginteger gcd(biginteger a, biginteger b) {
    biginteger c, x;
    c = 0;
    while (b > c) {
        x = a%b;
        a = b;  b = x;
    }
    return a;
}
biginteger lcm(biginteger &a, biginteger &b) {
    return (a*(b/gcd(a,b)));
}
biginteger pow(biginteger a, biginteger n) {
    biginteger res, dos, cero;
    res = 1;  dos = 2;  cero = 0;
    while(n > cero) {
        if((n % dos) > cero) res *= a;
        a *= a;  n /= dos;
    }
    return res;
}
biginteger pow(biginteger a, long long n) {
    biginteger c;  c = n;
    return pow(a, c);
}
long long log(long long n, biginteger a) { // log_n(a)
    long long res = 0;
    biginteger uno, c; uno = 1; c = n;
    while (a > uno) {
        res++;
        a /= c;
    }
    return res;
}
biginteger sqrt(biginteger &n) {
    biginteger a, b, m, w;
    a = n;
    b = 1;
    while(1) {
        m = a+b;
        m.dividirDos();
        if(m == a || m == b) return m;
        w = m*m;
        if(w > n) a = m;
        else b = m;
    }
    biginteger q;  q = 0;
    return q;
}


