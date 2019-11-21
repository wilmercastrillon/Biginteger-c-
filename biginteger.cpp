#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ulli;
typedef long long int tdato; //no debe ser unsigned para la resta!!!
tdato base = 1000000000;

class biginteger{
    private:

    vector<tdato> num;
    mutable bool signo;

    void quitar_zeros_izq(){
        while(num.size() > 1 && !num.back()) num.pop_back();
        if(num.size() == 0 && num[0] == 0) signo = true;
    }

    bool par(){ return num[0] % 2 == 0; }

    void dividirDos(){
        tdato carry = 0;
        ulli aux;
        for (int i = num.size() - 1; i >= 0; --i) {
            aux = num[i] + carry * base;
            num[i] = aux / 2;
            carry = aux % 2;
        }
        quitar_zeros_izq();
    }

    public:

    bool getSigno() const {  return signo;  }
    void setSigno(bool s) const {  signo = s;  }

    void iniciar(tdato n){
        num.clear();
        signo = n >= 0;
        n = abs(n);
        do{
            num.push_back((n >= base)? n % base: n);
            n /= base;
        }while(n);
    }
    void iniciar(string n){
        num.clear();
        signo = n[0] != '-';
        if(n[0] == '-') n = n.substr(1);
        for(int i = n.size(); i > 0; i -= 9){
            if(i < 9) num.push_back(atoi(n.substr(0, i).c_str()));
            else num.push_back(atoi(n.substr(i-9, 9).c_str()));
        }
        quitar_zeros_izq();
    }
    void iniciar(biginteger b){
        num.assign(b.num.begin(), b.num.end());
        signo = b.signo;
    }

    void imprimir(){
        if(!signo) printf("-");
        printf("%d", num.back());
        for(int i = num.size() - 2; i >= 0; i--)
            printf("%09d", num[i]);
        printf("\n");
    }

    string toString(){
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

    int comparar(biginteger b) const {//este es: 1 mayor, 0 igal, -1 menor
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

    biginteger suma(biginteger b) const {
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

    biginteger resta(biginteger b) const {//asumimos que b es menor
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

    biginteger multiplicar(biginteger b) const {
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

    biginteger dividir(biginteger b) const {
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
            m = med.multiplicar(b); m.signo = true;

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


    biginteger &operator=(tdato b);

    friend bool operator<(const biginteger&a, const biginteger&b);
    friend bool operator>(const biginteger&a, const biginteger&b);
    friend bool operator>=(const biginteger&a, const biginteger&b);
    friend bool operator<=(const biginteger&a, const biginteger&b);
    friend bool operator==(const biginteger&a, const biginteger&b);
    friend bool operator!=(const biginteger&a, const biginteger&b);

    friend biginteger operator+(const biginteger&a, const biginteger&b);
    friend biginteger operator-(const biginteger&a, const biginteger&b);
    friend biginteger operator*(const biginteger&a, const biginteger&b);
    friend biginteger operator/(const biginteger&a, const biginteger&b);
    friend biginteger operator%(const biginteger&a, const biginteger&b);

    friend biginteger operator+(const biginteger&a, tdato b);
    friend biginteger operator-(const biginteger&a, tdato b);
    friend biginteger operator*(const biginteger&a, tdato b);
    friend biginteger operator/(const biginteger&a, tdato b);
    friend biginteger operator%(const biginteger&a, tdato b);

    friend biginteger operator+(tdato a, const biginteger&b);
    friend biginteger operator-(tdato a, const biginteger&b);
    friend biginteger operator*(tdato a, const biginteger&b);
    friend biginteger operator/(tdato a, const biginteger&b);
    friend biginteger operator%(tdato a, const biginteger&b);

    friend biginteger operator+=(biginteger&a, const biginteger&b);
    friend biginteger operator-=(biginteger&a, const biginteger&b);
    friend biginteger operator*=(biginteger&a, const biginteger&b);
    friend biginteger operator/=(biginteger&a, const biginteger&b);
    friend biginteger operator%=(biginteger&a, const biginteger&b);

    friend biginteger operator+=(biginteger&a, tdato b);
    friend biginteger operator-=(biginteger&a, tdato b);
    friend biginteger operator*=(biginteger&a, tdato b);
    friend biginteger operator/=(biginteger&a, tdato b);
    friend biginteger operator%=(biginteger&a, tdato b);
};
typedef biginteger bigint;


bigint &bigint::operator=(tdato b){
    iniciar(b);
    return *this;
}


bool operator>(const bigint &a, const bigint &b){
    if(a.getSigno() == b.getSigno()){
        if(a.getSigno()) return a.comparar(b) > 0;
        else return b.comparar(a) > 0;
    }else return a.getSigno();
}
bool operator<(const bigint &a, const bigint &b){
    return (b > a);
}
bool operator==(const bigint &a, const bigint &b){
    if(a.getSigno() != b.getSigno()) return false;
    else return a.comparar(b) == 0;
}
bool operator!=(const bigint &a, const bigint &b){
    return !(a==b);
}
bool operator>=(const bigint &a, const bigint &b){
    if(a.getSigno() == b.getSigno()){
        if(a.getSigno()) return a.comparar(b) >= 0;
        else return b.comparar(a) >= 0;
    }else return a.getSigno();
}
bool operator<=(const bigint &a, const bigint &b){
    return (b >= a);
}


bigint operator+(const bigint&a, const bigint&b){
    bigint c;
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
bigint operator-(const bigint&a, const bigint&b){
    bigint c;
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
bigint operator*(const bigint&a, const bigint&b){
    bigint c = a.multiplicar(b);
    c.setSigno(a.getSigno() == b.getSigno());
    return c;
}
bigint operator/(const bigint&a, const bigint&b){
    bool s = a.getSigno() == b.getSigno();
    a.setSigno(true); b.setSigno(true);
    bigint c = a.dividir(b);
    c.setSigno(s);
    return c;
}
bigint operator%(const bigint&a, const bigint&b){
    bigint c = a/b;
    return a - (b*c);
}


bigint operator+(const bigint&a, tdato b){
    bigint c;
    c.iniciar(b);
    return a+c;
}
bigint operator-(const bigint&a, tdato b){
    bigint c;  c.iniciar(b);
    return a-c;
}
bigint operator*(const bigint&a, tdato b){
    bigint c;  c.iniciar(b);
    return a*c;
}
bigint operator/(const bigint&a, tdato b){
    bigint c;  c.iniciar(b);
    return a/c;
}
bigint operator%(const bigint&a, tdato b){
    bigint c;  c.iniciar(b);
    return a%c;
}


bigint operator+(tdato b, const bigint&a){
    bigint c;  c.iniciar(b);
    return a+c;
}
bigint operator-(tdato b, const bigint&a){
    bigint c;  c.iniciar(b);
    return a-c;
}
bigint operator*(tdato b, const bigint&a){
    bigint c;  c.iniciar(b);
    return a*c;
}
bigint operator/(tdato b, const bigint&a){
    bigint c;  c.iniciar(b);
    return a/c;
}
bigint operator%(tdato b, const bigint&a){
    bigint c;  c.iniciar(b);
    return a%c;
}

bigint operator+=(bigint &a, const bigint &b){return a = a + b;}
bigint operator-=(bigint &a, const bigint &b){return a = a - b;}
bigint operator*=(bigint &a, const bigint &b){return a = a * b;}
bigint operator/=(bigint &a, const bigint &b){return a = a / b;}
bigint operator%=(bigint &a, const bigint &b){return a = a % b;}

bigint operator+=(bigint &a, tdato b){return a = a + b;}
bigint operator-=(bigint &a, tdato b){return a = a - b;}
bigint operator*=(bigint &a, tdato b){return a = a * b;}
bigint operator/=(bigint &a, tdato b){return a = a / b;}
bigint operator%=(bigint &a, tdato b){return a = a % b;}

bigint operator++(bigint &a) { return a = a + 1; }
bigint operator--(bigint &a) { return a = a - 1; }

void operator >> (istream &in, bigint &a) {
    string s;
    cin >> s;
    a.iniciar(s);
}
ostream& operator << (ostream &out, bigint &a) {
    out << a.toString();
    return out;
}

bigint max(bigint a, bigint b) {
    return (a > b)? a: b;
}
bigint min(bigint a, bigint b) {
    return (a < b)? a: b;
}
bigint gcd(bigint a, bigint b) {
    bigint c, x;
    c = 0;
    while (b > c) {
        x = a%b;
        a = b;  b = x;
    }
    return a;
}
bigint lcm(bigint &a, bigint &b) {
    return (a*(b/gcd(a,b)));
}
bigint sqrt(bigint &a) {
    bigint dos, uno;
    dos = 2;  uno = 1;
    bigint x0 = a, x1 = (a+uno)/dos;
    while (x1 < x0) {
        x0 = x1;
        x1 = (x1+a/x1)/dos;
    }
    return x0;
}
bigint pow(bigint a, bigint n) {
    bigint res, dos, cero;
    res = 1;  dos = 2;  cero = 0;
    while(n > cero) {
        if((n % dos) > cero) res *= a;
        a *= a;  n /= dos;
    }
    return res;
}
bigint pow(bigint a, tdato n) {
    bigint c;  c = n;
    return pow(a, c);
}
tdato log(tdato n, bigint a) { // log_n(a)
    tdato res = 0;
    bigint uno, c; uno = 1; c = n;
    while (a > uno) {
        res++;
        a /= c;
    }
    return res;
}

int main(){
    string n, m;
    bigint a, b, c, f;
    cin >> f;
    //cin >> a;

    //b = pow(f, a);
    cout << log(2,f) << endl;

    //b.imprimir();

    return 0;
}


