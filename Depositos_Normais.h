/* 
 * File:   Depositos_Normais.h
 * Author: Tiago
 *
 * Created on 14 de Outubro de 2014, 14:35
 */

#ifndef DEPOSITOS_NORMAIS_H
#define	DEPOSITOS_NORMAIS_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;
#include "Depositos.h"

template <class T>
class Depositos_Normais : public Depositos<T> {
private:
    vector <stack<T>> VectorPaletes;
    vector<T> vecProdutos;
    vector<stack<T>> vecaux;
public:
    Depositos_Normais(int id, int num_palets, int capac_max, int area_total);
    Depositos_Normais(const Depositos_Normais<T> &d);
    ~Depositos_Normais();

    Depositos_Normais<T>* clone() const;
    void write(ostream &out) const;
    void getDescricao() const;

    bool inserirProduto(const T &p); //
    int expedirProdutos(int quant);
    void listarProduto();

    Depositos_Normais<T> & operator=(const Depositos_Normais<T> & dep);
    bool operator==(const Depositos_Normais<T> &p) const;

    vector<T> getProduto();
};

template <class T>
Depositos_Normais<T>::Depositos_Normais(int id, int num_palets, int capac_max, int area_total) : Depositos<T>(id, num_palets, capac_max, area_total) {
    for (int i = 0; i < this->getNumero_paletes(); i++) {
        VectorPaletes.push_back(stack <T>());
    }
}

template <class T>
Depositos_Normais<T>::Depositos_Normais(const Depositos_Normais<T> &d) : Depositos<T>(d), VectorPaletes(d.VectorPaletes) {
}

template <class T>
Depositos_Normais<T>::~Depositos_Normais() {
}

template <class T>
Depositos_Normais<T>* Depositos_Normais<T>::clone() const {
    return new Depositos_Normais<T>(*this);
}

template <class T>
void Depositos_Normais<T>::write(ostream &out) const {
    Depositos<T>::write(out);
}

template <class T>
void Depositos_Normais<T>::getDescricao() const {
    cout << "    Depósito Normal:" << endl;
    Depositos<T>::getDescricao();
}

template <class T>
ostream & operator<<(ostream &out, const Depositos_Normais<T> &dn) {
    dn.write(out);
    return out;
}
template <class T>
ostream & operator<<(ostream & out, const Depositos_Normais<T> *dn) {
    dn->write(out);
    return out;
}

//Metodos

template <class T>
bool Depositos_Normais<T>::inserirProduto(const T &p) {
    bool flag = false;
    int impar = (int) this->getCapacidade_maxima() / 2;
    for (int i = 0; i < this->getNumero_paletes(); i++) {
        if (i % 2 == 0) {
            if (VectorPaletes[i].size() < this->getCapacidade_maxima() && flag == false) {
                
                VectorPaletes[i].push(p);
                flag = true;
                vecProdutos.push_back(p);
            }
        }
    }
    if (flag == false) {
        for (int i = 0; i < this->getNumero_paletes(); i++) {
            if (i % 2 != 0) {
                if (VectorPaletes[i].size() < impar && flag == false) {
                    VectorPaletes[i].push(p);
                    flag = true;
                    vecProdutos.push_back(p);
                }
            }
        }
    }
    return flag;
}

template <class T>
int Depositos_Normais<T>::expedirProdutos(int quant) {
    //ULTIMO A ENTRAR PRIMEIRO A SAIR
    //PRIMEIRO IMPARES E DEPOIS PARES
    bool flag = false;
    int x=0;
    //retira impares
    while (quant > 0) {
        for (int i = this->getNumero_paletes() - 1; i >= 0; i--) {
            if ((i % 2) != 0 && flag == false) {
                if (!VectorPaletes[i].empty()) {
                    //                cout << "NR: PALETE IMPAR" << i << endl;
                    cout << "Expediu no Deposito Normal " << VectorPaletes[i].top() << endl;
                    x++;
                    VectorPaletes[i].pop();
                    flag = true;
                    quant--;
                }
            }
        }
        //retira pares
        if (flag == false) {
            for (int i = this->getNumero_paletes() - 1; i >= 0; i--) {
                if ((i % 2) == 0 && flag == false) {
                    if (!VectorPaletes[i].empty()) {
                        cout << "Expediu no Deposito Normal " << VectorPaletes[i].top() << endl;
                        x++;
                        VectorPaletes[i].pop();
                        flag = true;
                        quant--;
                    }
                }
            }
        }
        if (flag == false) {
            //cout << "Todos produtos foram expedidos" << endl;
            break;
        }
        flag = false;
    }
    flag = false;
    
    return x;
}

template <class T>
void Depositos_Normais<T>::listarProduto() {
    
    vecaux = VectorPaletes;
    for (int i = 0; i < vecaux.size(); i++) {
        
        while (!vecaux[i].empty()) {
            //imprime o primeiro valor da stack LIFO
            cout << vecaux[i].top() << endl;
            //remove elemento da stack
            vecaux[i].pop();
          
        }

    }
    
}

template <class T>
vector<T> Depositos_Normais<T>::getProduto() {
    return this->vecProdutos;
}

template <class T>
Depositos_Normais<T> & Depositos_Normais<T>::operator=(const Depositos_Normais<T> & dep) {
    if (this != &dep) {
        Depositos<T>::operator=(dep);
    }
    return (*this);
}

template <class T>
bool Depositos_Normais<T>::operator==(const Depositos_Normais<T> &d) const {
    bool a;
    if (Depositos<T>::operator=(d)) {
        return a = true;
    }
    return a = false;
}

#endif	/* DEPOSITOS_NORMAIS_H */