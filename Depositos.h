/* 
 * File:   Depositos.h
 * Author: Tiago
 *
 * Created on 14 de Outubro de 2014, 14:35
 */

#ifndef DEPOSITOS_H
#define	DEPOSITOS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class Depositos {
private:
    int ID, numero_paletes, capacidade_maxima;
    int area_total;
public:
    Depositos();
    Depositos(int id, int num_palets, int capac_max, int area_total);
    Depositos(const Depositos &d);
    virtual ~Depositos();

    int getID() const;
    int getNumero_paletes() const;
    int getCapacidade_maxima() const;
    int getArea_Maxima() const;

    void setID(int id);
    void setNumero_paletes(int num_palet);
    void setCapacidade_maxima(int cap_max);
    void setArea_Total(int area_max);

    //virtuais puros
    virtual Depositos<T>* clone() const = 0;
    virtual bool inserirProduto(const T& p) = 0; //const T& c
    virtual int expedirProdutos(int quant) = 0;
    virtual void listarProduto() = 0;
    virtual vector<T> getProduto() = 0; //vector <T*>


    //Sobrecarga de operadores
    virtual void write(ostream & out) const;
    Depositos<T> & operator=(const Depositos<T> &dep);
    bool operator<=(const Depositos<T> &d);
    bool operator>(const Depositos<T> &d);
    bool operator==(const Depositos<T> &d);

    virtual void getDescricao()const=0;

};

template <class T>
Depositos<T>::Depositos() : ID(0), numero_paletes(0), capacidade_maxima(0), area_total(0) {
}

template <class T>
Depositos<T>::Depositos(int id, int num_palets, int capac_max, int area_total) {
    this -> ID = id;
    this -> numero_paletes = num_palets;
    this -> capacidade_maxima = capac_max;
    this -> area_total = area_total;
}

template <class T>
Depositos<T>::Depositos(const Depositos &d) {
    this -> ID = d.ID;
    this -> numero_paletes = d.numero_paletes;
    this -> capacidade_maxima = d.capacidade_maxima;
    this -> area_total = d.area_total;
}

template <class T>
Depositos<T>::~Depositos() {
}

template <class T>
int Depositos<T>::getID() const {
    return (this -> ID);
}

template <class T>
int Depositos<T>::getNumero_paletes() const {
    return (this -> numero_paletes);
}

template <class T>
int Depositos<T>::getCapacidade_maxima() const {
    return (this -> capacidade_maxima);
}

template <class T>
int Depositos<T>::getArea_Maxima() const {
    return (this -> area_total);
}

template <class T>
void Depositos<T>::setID(int id) {
    this -> ID = id;
}

template <class T>
void Depositos<T>::setNumero_paletes(int num_palet) {
    this -> numero_paletes = num_palet;
}

template <class T>
void Depositos<T>::setCapacidade_maxima(int cap_max) {
    this -> capacidade_maxima = cap_max;
}

template <class T>
void Depositos<T>::setArea_Total(int area_tot) {
    this -> area_total = area_tot;
}
/*KEY -vertices*/
template <class T>
void Depositos<T>::write(ostream & out) const {
    //     "    numero de paletes: " << this->numero_paletes << endl;
    //    out << "Capacidade maxima: " << this->capacidade_maxima << "    Area Total: " << this->area_total << endl;
    out << this->ID;
}

template <class T>
void Depositos<T>::getDescricao() const {
    cout << "Chave: " << this->ID << "    numero de paletes: " << this->numero_paletes << endl;
    cout << "Capacidade maxima: " << this->capacidade_maxima << "    Area Total: " << this->area_total << endl;
}

template <class T>
ostream & operator<<(ostream & out, const Depositos<T> &dep) {
    dep.write(out);
    return out;
}

template <class T>
ostream & operator<<(ostream & out, const Depositos<T> *dep) {
    dep->write(out);
    return out;
}

template <class T>
Depositos<T> & Depositos<T>::operator=(const Depositos<T> &dep) {
    if (this != &dep) {
        this->ID = dep.ID;
        this->numero_paletes = dep.numero_paletes;
        this->capacidade_maxima = dep.capacidade_maxima;
        this->area_total = dep.area_total;
    }
    return (*this);
}

template <class T>
bool Depositos<T>::operator<=(const Depositos<T> &d) {
    return this->capacidade_maxima <= d.capacidade_maxima;
}

template <class T>
bool Depositos<T>::operator>(const Depositos<T> &d) {
    return this->capacidade_maxima > d.capacidade_maxima;
}

template <class T>
bool Depositos<T>::operator==(const Depositos<T> &d) {
    return this->capacidade_maxima = d.capacidade_maxima;
}


#endif	/* DEPOSITOS_H */

