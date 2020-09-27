#include <stdexcept>
#include "biginteger.h"

using namespace std;

typedef unsigned long long int ulli;
typedef long long tdato; //no debe ser unsigned para la resta!!!
tdato base = 1000000000;
const int ceros = log10(base);

void biginteger::quitar_zeros_izq(){
    while(num.size() > 1 && !num.back()) num.pop_back();
    //if(num.size()==1 && num[0]==0) set_sign(true);
}

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

bool biginteger::isEven(){ return (num[0]%2LL == 0LL); }
bool biginteger::get_sign() const {  return signo;  }
void biginteger::set_sign(bool s) const {  signo = s;  }

biginteger::biginteger(){}
biginteger::biginteger(tdato n){
    iniciar(n);
}
biginteger::biginteger(string n){
    iniciar(n);
}

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
    for(int i = n.size(); i > 0; i -= ceros){
        if(i < ceros) num.push_back(atoi(n.substr(0, i).c_str()));
        else num.push_back(atoi(n.substr(i-ceros, ceros).c_str()));
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
        printf("%0*d", ceros, num[i]);
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
        sprintf(cad, "%0*d", ceros, num[i]);
        x = (string) cad;
        s = s + x;
    }
    return s;
}

//this is: 1 more than b, 0 iqual, -1 less than b, ignoring the sign
int biginteger::compare(biginteger b) const {
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
    if(compare(b) < 0){
        biginteger cero(0);
        return cero;
    }else{
        biginteger cero(0);
        if(b.compare(cero) == 0){
            throw std::invalid_argument("received zero value");
        }
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

        cmp = compare(m);
        if(cmp == 0) break;
        else if(cmp < 0) may.iniciar(med);
        else{
            if(resta(m).compare(b) < 0) break;
            else men.iniciar(med);
        }
    }
    return med;
}


/*
    COMPARE
*/
bool operator>(const biginteger &a, const biginteger &b){
    if(a.get_sign() == b.get_sign()){
        if(a.get_sign()) return a.compare(b) > 0;
        else return b.compare(a) > 0;
    }else return a.get_sign();
}
bool operator<(const biginteger &a, const biginteger &b){
    return (b > a);
}
bool operator==(const biginteger &a, const biginteger &b){
    if(a.get_sign() != b.get_sign()) return false;
    else return a.compare(b) == 0;
}
bool operator!=(const biginteger &a, const biginteger &b){
    return !(a==b);
}
bool operator>=(const biginteger &a, const biginteger &b){
    if(a.get_sign() == b.get_sign()){
        if(a.get_sign()) return a.compare(b) >= 0;
        else return b.compare(a) >= 0;
    }else return a.get_sign();
}
bool operator<=(const biginteger &a, const biginteger &b){
    return (b >= a);
}

/*
    OPERATORS
*/
biginteger operator+(const biginteger&a, const biginteger&b){
    biginteger c;
    if(a.get_sign() == b.get_sign()){
        c = a.suma(b);
        c.set_sign(a.get_sign());
    }else{
        if(a.compare(b) > 0){
            c = a.resta(b);
            c.set_sign(a.get_sign());
        }else{
            c = b.resta(a);
            c.set_sign(b.get_sign());
        }
    }
    return c;
}
biginteger operator-(const biginteger&a, const biginteger&b){
    biginteger c;
    if(a.compare(b) >= 0){
        if(a.get_sign() == b.get_sign()) c = a.resta(b);
        else c = a.suma(b);
        c.set_sign(a.get_sign());
    }else{
        if(a.get_sign() == b.get_sign()) c = b.resta(a);
        else c = a.suma(b);
        c.set_sign(!b.get_sign());
    }
    return c;
}
biginteger operator*(const biginteger&a, const biginteger&b){
    biginteger c = a.karatsuba(b);
    //biginteger c = a.fft_multiply(b);
    c.set_sign(a.get_sign() == b.get_sign());
    return c;
}
biginteger operator/(const biginteger&a, const biginteger&b){
    bool s = a.get_sign() == b.get_sign();
    a.set_sign(true); b.set_sign(true);
    biginteger c = a.dividir(b);
    c.set_sign(s);
    return c;
}
biginteger operator%(const biginteger&a, const biginteger&b){
    biginteger c = a/b;
    return a - (b*c);
}

/*
    OTHER OPERATORS
*/
biginteger operator+=(biginteger &a, const biginteger &b){return a = a + b;}
biginteger operator-=(biginteger &a, const biginteger &b){return a = a - b;}
biginteger operator*=(biginteger &a, const biginteger &b){return a = a * b;}
biginteger operator/=(biginteger &a, const biginteger &b){return a = a / b;}
biginteger operator%=(biginteger &a, const biginteger &b){return a = a % b;}

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

biginteger &biginteger::operator=(tdato b){
    iniciar(b);
    return *this;
}

int biginteger::toInt(){
    int res = num[0];
    if(signo) return res;
    return res*-1;
}

long long biginteger::toLong(){
    long long res = num[1]*base + num[0];
    if(signo) return res;
    return res*-1LL;
}


