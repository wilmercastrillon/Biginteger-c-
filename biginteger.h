#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

class biginteger{
    private:

    std::vector<long long> num;
    mutable bool signo;

    void quitar_zeros_izq();
    bool par();

    public:

    void dividirDos();
    bool getSigno()const;
    void setSigno(bool s) const;

    void iniciar(long long n);
    void iniciar(std::string n);
    void iniciar(biginteger b);

    void imprimir();
    std::string toString();

    int comparar(biginteger b) const;
    biginteger suma(biginteger b) const;
    biginteger resta(biginteger b) const;
    biginteger multiplicar(biginteger b) const;
    biginteger karatsuba(biginteger y) const;
    biginteger dividir(biginteger b) const;

    biginteger &operator=(long long b);

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

    friend biginteger operator+(const biginteger&a, long long b);
    friend biginteger operator-(const biginteger&a, long long b);
    friend biginteger operator*(const biginteger&a, long long b);
    friend biginteger operator/(const biginteger&a, long long b);
    friend biginteger operator%(const biginteger&a, long long b);

    friend biginteger operator+(long long a, const biginteger&b);
    friend biginteger operator-(long long a, const biginteger&b);
    friend biginteger operator*(long long a, const biginteger&b);
    friend biginteger operator/(long long a, const biginteger&b);
    friend biginteger operator%(long long a, const biginteger&b);

    friend biginteger operator+=(biginteger&a, const biginteger&b);
    friend biginteger operator-=(biginteger&a, const biginteger&b);
    friend biginteger operator*=(biginteger&a, const biginteger&b);
    friend biginteger operator/=(biginteger&a, const biginteger&b);
    friend biginteger operator%=(biginteger&a, const biginteger&b);

    friend biginteger operator+=(biginteger&a, long long b);
    friend biginteger operator-=(biginteger&a, long long b);
    friend biginteger operator*=(biginteger&a, long long b);
    friend biginteger operator/=(biginteger&a, long long b);
    friend biginteger operator%=(biginteger&a, long long b);

    friend biginteger operator++(biginteger &a);
    friend biginteger operator--(biginteger &a);

    friend bool operator<(const biginteger&a, const biginteger&b);
    friend std::istream& operator >> (std::istream &in, biginteger &a);
    friend std::ostream& operator << (std::ostream &out, biginteger &a);
};


#endif // BIGINTEGER_H_INCLUDED
