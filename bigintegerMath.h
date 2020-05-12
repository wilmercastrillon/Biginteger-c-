#ifndef BIGINTEGERMATH_H_INCLUDED
#define BIGINTEGERMATH_H_INCLUDED

#include "biginteger.h"

biginteger max(biginteger a, biginteger b);
biginteger min(biginteger a, biginteger b);
biginteger gcd(biginteger a, biginteger b);
biginteger lcm(biginteger &a, biginteger &b);
biginteger pow(biginteger a, biginteger n);
biginteger pow(biginteger a, long long n);
long long log(long long n, biginteger a);
biginteger sqrt(biginteger &n);
biginteger gcd_ex(biginteger &a, biginteger &b, biginteger &x, biginteger &y);
biginteger expmod(biginteger a, biginteger b, biginteger m);
biginteger expmod(biginteger a, biginteger b, long long m);

#endif // BIGINTEGERMATH_H_INCLUDED
