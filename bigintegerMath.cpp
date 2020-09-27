#include <stdexcept>
//#include <iostream>
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
    if(a <= 0){
        throw std::invalid_argument("received negative or zero value");
    }
    long long res = 0;
    biginteger uno(1), c(n);
    while (a >= uno) {
        res++;
        a /= c;
    }
    return res - 1;
}
biginteger sqrt(biginteger &n) {
    if(n < 0){
        throw std::invalid_argument("received negative value");
    }
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

biginteger gcd_ext(biginteger &a, biginteger &b, biginteger &x, biginteger &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	biginteger x1, y1, mod = a%b;
	biginteger d = gcd_ext(b, mod, x1, y1);
	x = y1;
	y = x1 - (a/b)*y1;
	return d;//GCD
}

biginteger mod_pow(biginteger a, biginteger b, biginteger m){//O(log b)
	if(b == 0){
        return biginteger(1);
	}
	biginteger q = mod_pow(a,b/2,m);
	q = (q*q)%m;
	return b%2>0? (a*q)%m : q;
}

biginteger mod_pow(biginteger a, biginteger b, long long m){//O(log b)
	if(b == 0){
        return biginteger(1);
	}
	biginteger q = mod_pow(a,b/2,m);
	q = (q*q)%m;
	return b%2>0? (a*q)%m : q;
}

biginteger abs(biginteger a){
    biginteger b = a+0;
    b.set_sign(true);
    return b;
}

long long bit_length(biginteger a){
    long long res = (!a.get_sign());
    a.set_sign(true);
    biginteger uno(1), dos(2);
    bool alwaysEven = a.isEven();

    while (a > uno) {
        res++;
        a /= dos;
        alwaysEven = alwaysEven&&a.isEven();
    }
    return res + (!alwaysEven);
}

biginteger negate_sign(biginteger a){
    biginteger cero(0);
    biginteger b = a+0;
    b.imprimir();
    b.set_sign(!a.get_sign());
    return b;
}


