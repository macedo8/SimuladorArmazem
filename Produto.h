/* 
 * File:   Produto.h
 * Author: Tiago
 *
 * Created on 14 de Outubro de 2014, 14:35
 */

#ifndef PRODUTO_H
#define	PRODUTO_H

#include <iostream>
#include <string>
using namespace std;

class Produto {
private:
    string nome;
    string tipo;
public:
    Produto();
    Produto(string nome, string tipo);
    Produto(const Produto &p);
    virtual ~Produto();
    virtual Produto * clone() const;

    string getNome() const;
    void setNome(string nome);
    string getTipo() const;
    void setTipo(string tipo);

    //sobrecarga
    virtual void write(ostream & out) const;
    Produto & operator=(const Produto &p);
    bool &  operator == (const Produto &p);
};

Produto::Produto() : nome(""), tipo("") {
}

Produto::Produto(string nome, string tipo) : nome(nome), tipo(tipo) {
}

Produto::Produto(const Produto & p) : nome(p.nome), tipo(p.tipo) {
}

Produto::~Produto() {
}

Produto * Produto::clone() const {
    return new Produto(*this);
}

string Produto::getNome() const {

    return (this -> nome);
}

void Produto::setNome(string nome) {
    this -> nome = nome;
}

string Produto::getTipo() const {

    return (this -> tipo);
}

void Produto::setTipo(string tipo) {
    this -> tipo = tipo;
}

void Produto::write(ostream & out) const {
    out << "    Produto:" << endl;
    out << " Nome:" << nome << "    Tipo: " << tipo << endl;
}

ostream & operator<<(ostream & out, const Produto &prod) {
    prod.write(out);
    return out;
}

Produto & Produto::operator =(const Produto& p) {
    if (this != &p) {
        nome = p.nome;
        tipo = p.tipo;
    }
    return (*this);
}
bool & Produto:: operator == (const Produto &p) {
    bool a;
    if(p.getNome() ==nome && p.getTipo() == tipo ) {
        return a = true;
    }
    return a=false;
}

#endif	/* PRODUTOS_H */

