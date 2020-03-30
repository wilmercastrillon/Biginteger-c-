#include <bits/stdc++.h>
#include "biginteger.h"

using namespace std;
typedef unsigned long long int ulli;
typedef long long tdato; //no debe ser unsigned para la resta!!!
tdato base = 1000000000;

//typedef biginteger bigint;

void biginteger::quitar_zeros_izq(){
    while(num.size() > 1 && !num.back()) num.pop_back();
}

bool biginteger::par(){ return num[0] % 2 == 0; }

void biginteger::dividirDos(){
    tdato carry = 0;
    ulli aux;
    for (int i = num.size() - 1; i >= 0; --i) {
        aux = num[i] + carry * base;
        num[i] = aux / 2;
        carry = aux % 2;
    }
    quitar_zeros_izq();
}

bool biginteger::getSigno() const {  return signo;  }
void biginteger::setSigno(bool s) const {  signo = s;  }

void biginteger::iniciar(tdato n){
    num.clear();
    signo = n >= 0;
    n = abs(n);
    do{
        num.push_back((n >= base)? n % base: n);
        n /= base;
    }while(n);
}
void biginteger::iniciar(string n){
    num.clear();
    signo = n[0] != '-';
    if(n[0] == '-') n = n.substr(1);
    for(int i = n.size(); i > 0; i -= 9){
        if(i < 9) num.push_back(atoi(n.substr(0, i).c_str()));
        else num.push_back(atoi(n.substr(i-9, 9).c_str()));
    }
    quitar_zeros_izq();
}
void biginteger::iniciar(biginteger b){
    num.assign(b.num.begin(), b.num.end());
    signo = b.signo;
}

void biginteger::imprimir(){
    if(!signo) printf("-");
    printf("%d", num.back());
    for(int i = num.size() - 2; i >= 0; i--)
        printf("%09d", num[i]);
    printf("\n");
}

string biginteger::toString(){
    string s = "", x;
    char cad[12];
    if(!signo) s.push_back('-');
    sprintf(cad, "%d", num.back());
    x = (string) cad;
    s = s + x;
    for(int i = num.size() - 2; i >= 0; i--){
        sprintf(cad, "%09d", num[i]);
        x = (string) cad;
        s = s + x;
    }
    return s;
}

int biginteger::comparar(biginteger b) const {//este es: 1 mayor, 0 igal, -1 menor
    if(num.size() > b.num.size()){
        return 1;
    }else if(num.size() < b.num.size()){
        return -1;
    }else{
        for(int i = num.size() - 1; i >= 0; i--){
            if(num[i] > b.num[i]) return 1;
            else if(num[i] < b.num[i]) return -1;
        }
        return 0;
    }
}

biginteger biginteger::suma(biginteger b) const {
    ulli carry = 0, aux;
    int l = max(b.num.size(), num.size());
    biginteger c;

    for(int i = 0; i < l || carry; i++){
        aux = carry;
        if(i < b.num.size()) aux += b.num[i];
        if(i < num.size()) aux += num[i];

        if(aux >= base){
            c.num.push_back(aux % base);
            carry = aux / base;
        }else{
            c.num.push_back(aux);
            carry = 0;
        }
    }
    return c;
}

biginteger biginteger::resta(biginteger b) const {//asumimos que b es menor
    tdato carry = 0;//no debe ser unsigned
    biginteger c;

    for(int i = 0; i < num.size(); i++){
        c.num.push_back(num[i]);
        c.num[i] -= ((i < b.num.size())? b.num[i]: 0) + carry;
        if(c.num[i] < 0){
            c.num[i] += base;
            carry = 1;
        }else carry = 0;
    }
    c.quitar_zeros_izq();
    return c;
}

biginteger biginteger::multiplicar(biginteger b) const {
    ulli aux = 0, carry;
    biginteger c;
    c.num.assign(num.size() + b.num.size(), 0);

    for(int i = 0; i < num.size(); i++){
        carry = 0;
        for(int j = 0; j < b.num.size() || carry; j++){
            aux = c.num[i + j] + carry + (num[i] * ((j < b.num.size())? b.num[j] : 0));
            carry = aux / base;
            c.num[i + j] = aux % base;
        }
    }
    c.quitar_zeros_izq();
    return c;
}

biginteger biginteger::karatsuba(biginteger y) const {
    biginteger xy;
    biginteger x = *this;
    if(min(x.num.size(), y.num.size()) < 83){
        xy = x.multiplicar(y);  xy.signo = true;
        return xy;
    }
    int m = max(x.num.size(), y.num.size()) / 2;//punto optimo en el rango [66-100]

    biginteger x1, x0, y1, y0, z0, z1, z2;
    if(x.num.size() > m) x1.num.assign(x.num.begin()+m,x.num.end());
    else x1.num.assign(1,0);
    if(y.num.size() > m) y1.num.assign(y.num.begin()+m,y.num.end());
    else y1.num.assign(1,0);
    if(x.num.size() > m) x0.num.assign(x.num.begin(),x.num.begin()+m);
    else x0.num.assign(x.num.begin(),x.num.end());
    if(y.num.size() > m) y0.num.assign(y.num.begin(),y.num.begin()+m);
    else y0.num.assign(y.num.begin(),y.num.end());

    z2 = x1.karatsuba(y1);//z2 = x1.multiplicar(y1);
    z0 = x0.karatsuba(y0);//z0 = x0.multiplicar(y0);
    x1 = x1.suma(x0);
    y1 = y1.suma(y0);
    z1 = ((x1.karatsuba(y1)).resta(z2)).resta(z0);//z1 = ((x1.multiplicar(y1)).resta(z2)).resta(z0);

    vector<tdato> v(2*m,0);
    z2.num.insert(z2.num.begin(),v.begin(),v.end());
    z1.num.insert(z1.num.begin(),v.begin(),v.begin()+m);
    xy = (z2.suma(z1)).suma(z0);
    xy.signo = true;
    return xy;
}

biginteger biginteger::dividir(biginteger b) const {
    if(comparar(b) < 0){
        biginteger cero; cero.iniciar(0);
        return cero;
    }
    biginteger may, men, med, m;
    m.iniciar(1);
    may = suma(m); may.signo = true;
    men.iniciar(0);
    int cmp;

    while(true){
        med = may.suma(men); med.signo = true;
        med.dividirDos();
        m = med.karatsuba(b); m.signo = true;

        cmp = comparar(m);
        if(cmp == 0) break;
        else if(cmp < 0) may.iniciar(med);
        else{
            if(resta(m).comparar(b) < 0) break;
            else men.iniciar(med);
        }
    }
    return med;
}

biginteger &biginteger::operator=(tdato b){
    iniciar(b);
    return *this;
}


bool operator>(const biginteger &a, const biginteger &b){
    if(a.getSigno() == b.getSigno()){
        if(a.getSigno()) return a.comparar(b) > 0;
        else return b.comparar(a) > 0;
    }else return a.getSigno();
}
bool operator<(const biginteger &a, const biginteger &b){
    return (b > a);
}
bool operator==(const biginteger &a, const biginteger &b){
    if(a.getSigno() != b.getSigno()) return false;
    else return a.comparar(b) == 0;
}
bool operator!=(const biginteger &a, const biginteger &b){
    return !(a==b);
}
bool operator>=(const biginteger &a, const biginteger &b){
    if(a.getSigno() == b.getSigno()){
        if(a.getSigno()) return a.comparar(b) >= 0;
        else return b.comparar(a) >= 0;
    }else return a.getSigno();
}
bool operator<=(const biginteger &a, const biginteger &b){
    return (b >= a);
}


biginteger operator+(const biginteger&a, const biginteger&b){
    biginteger c;
    if(a.getSigno() == b.getSigno()){
        c = a.suma(b);
        c.setSigno(a.getSigno());
    }else if(a > b){
        c = a.resta(b);
        c.setSigno(a.getSigno());
    }else{
        c = b.resta(a);
        c.setSigno(b.getSigno());
    }
    return c;
}
biginteger operator-(const biginteger&a, const biginteger&b){
    biginteger c;
    if(a.comparar(b) > 0){
        if(a.getSigno() == b.getSigno()) c = a.resta(b);
        else c = a.suma(b);
        c.setSigno(a.getSigno());
    }else{
        if(a.getSigno() == b.getSigno()) c = b.resta(a);
        else c = a.suma(b);
        c.setSigno(!b.getSigno());
    }
    return c;
}
biginteger operator*(const biginteger&a, const biginteger&b){
    biginteger c = a.karatsuba(b);
    c.setSigno(a.getSigno() == b.getSigno());
    return c;
}
biginteger operator/(const biginteger&a, const biginteger&b){
    bool s = a.getSigno() == b.getSigno();
    a.setSigno(true); b.setSigno(true);
    biginteger c = a.dividir(b);
    c.setSigno(s);
    return c;
}
biginteger operator%(const biginteger&a, const biginteger&b){
    biginteger c = a/b;
    return a - (b*c);
}

biginteger operator+(const biginteger&a, tdato b){
    biginteger c;
    c.iniciar(b);
    return a+c;
}
biginteger operator-(const biginteger&a, tdato b){
    biginteger c;  c.iniciar(b);
    return a-c;
}
biginteger operator*(const biginteger&a, tdato b){
    biginteger c;  c.iniciar(b);
    return a*c;
}
biginteger operator/(const biginteger&a, tdato b){
    biginteger c;  c.iniciar(b);
    return a/c;
}
biginteger operator%(const biginteger&a, tdato b){
    biginteger c;  c.iniciar(b);
    return a%c;
}


biginteger operator+(tdato b, const biginteger&a){
    biginteger c;  c.iniciar(b);
    return a+c;
}
biginteger operator-(tdato b, const biginteger&a){
    biginteger c;  c.iniciar(b);
    return a-c;
}
biginteger operator*(tdato b, const biginteger&a){
    biginteger c;  c.iniciar(b);
    return a*c;
}
biginteger operator/(tdato b, const biginteger&a){
    biginteger c;  c.iniciar(b);
    return a/c;
}
biginteger operator%(tdato b, const biginteger&a){
    biginteger c;  c.iniciar(b);
    return a%c;
}

biginteger operator+=(biginteger &a, const biginteger &b){return a = a + b;}
biginteger operator-=(biginteger &a, const biginteger &b){return a = a - b;}
biginteger operator*=(biginteger &a, const biginteger &b){return a = a * b;}
biginteger operator/=(biginteger &a, const biginteger &b){return a = a / b;}
biginteger operator%=(biginteger &a, const biginteger &b){return a = a % b;}

biginteger operator+=(biginteger &a, tdato b){return a = a + b;}
biginteger operator-=(biginteger &a, tdato b){return a = a - b;}
biginteger operator*=(biginteger &a, tdato b){return a = a * b;}
biginteger operator/=(biginteger &a, tdato b){return a = a / b;}
biginteger operator%=(biginteger &a, tdato b){return a = a % b;}

biginteger operator++(biginteger &a) { return a = a + 1; }
biginteger operator--(biginteger &a) { return a = a - 1; }

istream& operator >> (istream &in, biginteger &a) {
    string s;
    if(in >> s)
        a.iniciar(s);
    return in;
}
ostream& operator << (ostream &out, biginteger &a) {
    out << a.toString();
    return out;
}


