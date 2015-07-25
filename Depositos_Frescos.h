/* 
 * File:   Depositos_Frescos.h
 * Author: Tiago
 *
 * Created on 14 de Outubro de 2014, 14:35
 */

#ifndef DEPOSITOS_FRESCOS_H
#define	DEPOSITOS_FRESCOS_H


#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
#include "Depositos.h"

template <class T>
class Depositos_Frescos : public Depositos<T> {
private:
    vector<queue<T>> VectorPaletes;
    vector<T> vecProdutos;
    vector<queue<T>> vecaux;
    int i = 0;

    
public:
    Depositos_Frescos(int id, int num_palets, int capac_max, int area_total);
    Depositos_Frescos(const Depositos_Frescos<T> &d);
    ~Depositos_Frescos();

    Depositos_Frescos<T>* clone() const;
    void write(ostream & out) const;
    void getDescricao() const;
    
    bool inserirProduto(const T& p);
    int expedirProdutos(int quant);
    void listarProduto();
    vector<T> getProduto();

    Depositos_Frescos<T> & operator=(const Depositos_Frescos<T> & dep);
    bool operator==(const Depositos_Frescos<T> &p) const;
};

template <class T>
Depositos_Frescos<T>::Depositos_Frescos(int id, int num_palets, int capac_max, int area_total) : Depositos<T>(id, num_palets, capac_max, area_total) {
    for (int i = 0; i < this->getNumero_paletes(); i++) {
        VectorPaletes.push_back(queue <T>());
    }
}
template <class T>
Depositos_Frescos<T>::Depositos_Frescos(const Depositos_Frescos<T> &d) : Depositos<T>(d), VectorPaletes(d.VectorPaletes) { }
template <class T>
Depositos_Frescos<T>::~Depositos_Frescos() { }
template <class T>
Depositos_Frescos<T>* Depositos_Frescos<T>::clone() const {
    return new Depositos_Frescos<T>(*this);
}

template <class T>
void Depositos_Frescos<T>::write(ostream &out) const {
    Depositos<T>::write(out);
}
template <class T>
void Depositos_Frescos<T>::getDescricao() const {
    cout << "    Depósito Fresco:" << endl;
    Depositos<T>::getDescricao();
}
template <class T>
ostream & operator<<(ostream & out, const Depositos_Frescos<T> &df) {
    df.write(out);
    return out;
}
template <class T>
ostream & operator<<(ostream & out, const Depositos_Frescos<T> *df) {
    df->write(out);
    return out;
}
//metodos

template <class T>
bool Depositos_Frescos<T>::inserirProduto(const T& p) {
    bool flag = false;
    if (VectorPaletes[i].size() < this->getCapacidade_maxima()) {
        VectorPaletes[i].push(p);
        flag = true;
//        cout << "Palete: " << i << endl;
        vecProdutos.push_back(p);
    }
    i++;

    if (i == this->getNumero_paletes()) {
        i = 0;
    }
    return flag;
}

template <class T>
int Depositos_Frescos<T>::expedirProdutos(int quant) {
    //PRIMEIRO A ENTRAR É PRIMEIRO A SAIR
    int j=0;
    int aux = 0;
    while (aux != quant && !VectorPaletes[j].empty()) {
                cout << "Expediu no Depósito Fresco " << VectorPaletes[j].front() << endl;
                VectorPaletes[j].pop();      
                if (j != (this->getNumero_paletes()-1)) {
                    j++;
                } else {
                    j = 0;
                }
                aux++;
    }  
    return aux;
}

template <class T>
void Depositos_Frescos<T>::listarProduto() {
    T p;
    vecaux=VectorPaletes;
    int i = 0;
    for (int i = 0; i < vecaux.size(); i++) {
        while (!vecaux[i].empty()) {
            p = vecaux[i].front();
            cout << p << endl;
            vecaux[i].pop();
        }
    }
}

template <class T>
vector<T> Depositos_Frescos<T>::getProduto() {
    return this->vecProdutos;
}

template <class T>
Depositos_Frescos<T> & Depositos_Frescos<T>::operator=(const Depositos_Frescos<T> & dep) {
    if (this != &dep) {
        Depositos<T>::operator=(dep);
    }
    return (*this);
}

template <class T>
bool Depositos_Frescos<T>::operator==(const Depositos_Frescos<T> &d) const {
    bool a;
    if (Depositos<T>::operator=(d)) {
        return a = true;
    }
    return a = false;
}

#endif	/* DEPOSITOS_FRESCOS_H */

