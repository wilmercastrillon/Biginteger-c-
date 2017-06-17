#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
typedef vector<short> vs;

struct biginteger{
	int tam;
    vector<short> num;

	void iniciar(string c){
		tam = c.length();
		num.clear();
		for(int i = tam - 1; i > -1; i--) num.push_back(c[i] - '0');
	}

	void iniciar(int c){
		num.clear();
		tam = 0;
		while(c > 0){
			num.push_back(c % 10);
			c /= 10;
			tam++;
		}
	}

	void imprimir(){
		for(int i = tam - 1; i > -1; i--) printf("%d", num[i]);
		printf("\n");
	}

	void suma2(vector<short> b){
		int aux = 0, pos = b.size();

		for(int i = 0; i < pos; i++){
			if(i < tam){
				aux += num[i] + b[i];
				num[i] = aux % 10;
			}else{
				aux += b[i];
				num.push_back(aux % 10);
			}
			aux /= 10;
		}

		while(aux > 0){
			if(pos >= tam)
				num.push_back(aux % 10);
			else{
				aux += num[pos];
				num[pos++] = aux % 10;
			}

			aux /= 10;
		}

		tam = num.size();
	}

	biginteger suma(biginteger big){
		vs b = big.num;
		int aux = 0, pos = max(big.tam, tam);
		biginteger a;

		for(int i = 0; i < pos || aux > 0; i++){
			if(i < tam) aux += num[i];
			if(i < b.size()) aux += b[i];

            a.num.push_back(aux % 10);
			aux /= 10;
		}

		a.tam = a.num.size();
		return a;
	}

	biginteger multiplicar(biginteger b){
		int l = b.num.size();
		vector<vs>  vvs(l);

		for(int i = 0; i < l; i++){
			int aux = 0;
			for(int j = 0; j < i; j++) vvs[i].push_back(0);

			for(int j = 0; j < num.size(); j++){
				aux = aux + (b.num[i] * num[j]);
				vvs[i].push_back(aux % 10);
				aux /= 10;
			}

			while(aux > 0){
				vvs[i].push_back(aux % 10);
				aux /= 10;
			}
		}

        biginteger res;
		res.iniciar("0");
		for(int i = 0; i < l; i++) res.suma2(vvs[i]);

		return res;
	}

	biginteger bits_der(int c){
	    biginteger big;
	    big.num.clear();
	    for(int i = c; i < tam; i++){
	        big.num.push_back(num[i]);
	    }

	    if(!big.num.size()) big.num.push_back(0);
	    big.tam = big.num.size();
	    return big;
	}

	biginteger bits_izq(int a){
	    biginteger big;
	    big.num.clear();
	    a--;
	    for(int i = 0; i <= a && i < tam; i++){
	        big.num.push_back(num[i]);
	    }

	    if(!big.num.size()) big.num.push_back(0);
	    big.tam = big.num.size();
	    return big;
	}

	void quitar_zeros_izq(){
	    while(!num.back() && num.size() > 1){
	        num.pop_back();
	    }
	    tam = num.size();
	}

	biginteger resta(biginteger big){ //asumimos que el numero que llega es menor
	    big.quitar_zeros_izq();
        vs b = big.num;

		int aux = 0, pos = max(big.tam, tam);
		biginteger a;
		if(b.size() == 1 && b[0] == 0){
		    a = bits_der(0);
		    return a;
		}

		bool cero = false;

		for(int i = 0; i < pos || aux > 0; i++){
			if(i < tam) aux += num[i];
			if(i < b.size()){
			    if (cero){
			        aux += 9 - b[i];
			    }else{
			        if(b[i]){
			            cero = 1;
			            aux += 10 - b[i];
			        }
			    }
			}else{
			    if(i < pos) aux += 9;
			}
            a.num.push_back(aux % 10);
			aux /= 10;
		}

        a.num[a.num.size() - 1]--;
        a.quitar_zeros_izq();
		return a;
	}

	void mover_izq(int n){
	    for(int i = n; i > 0; i--) num.insert(num.begin(), 0);
	    tam = num.size();
	}

	biginteger karatsuba(biginteger b){
	    int n = max(b.tam, tam);
	    if(n < 4){
	        return multiplicar(b);
	    }
	    int k = n >> 1;

	    biginteger a1 = bits_der(k);
	    biginteger a0 = bits_izq(k);
        biginteger b1 = b.bits_der(k);
	    biginteger b0 = b.bits_izq(k);

	    biginteger p2 = a1.karatsuba(b1);
	    p2.quitar_zeros_izq();
	    biginteger p1 = (a0.suma(a1)).karatsuba(b0.suma(b1));
	    p1.quitar_zeros_izq();
	    biginteger p0 = a0.karatsuba(b0);
	    p0.quitar_zeros_izq();

	    /*a0.imprimir();
	    a1.imprimir();
	    b0.imprimir();
	    b1.imprimir();
	    cout << endl;
	    p0.imprimir();
	    p1.imprimir();
	    p2.imprimir();
        */
        //cout << "auxiliar 1 " << endl;
	    biginteger aux1 = p1.resta(p2.suma(p0));
	    //aux1.imprimir();
        aux1.mover_izq(k);
        //aux1.imprimir();
        //cout << "final" << endl;
	    p2.mover_izq(2*k);

        /*cout << "resultados para sumar" << endl;
	    p2.imprimir();
	    aux1.imprimir();
	    p0.imprimir();
        */
	    return p2.suma(aux1.suma(p0));
	}
};

int main(){
	biginteger n, m, o;
	string n1, n2;
	int f;

	while(cin >> f){
	    f++;
	    n.iniciar(1);
        for(int i = 1; i < f; i++){
            m.iniciar(i);
            n = n.multiplicar(m);
        }
        n.imprimir();
        cout << endl;
	}

	/*while(cin >> n1 >> n2){
	    n.iniciar(n1);
	    m.iniciar(n2);

        n = n.karatsuba(m);
        //n = n.resta(m);
        n.imprimir();
        cout << endl;
    }*/

	return 0;
}
