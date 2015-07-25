/* 
 * File:   Armazem.h
 * Author: Tiago
 *
 * Created on 25 de Outubro de 2014, 17:53
 */

#ifndef ARMAZEM_H
#define	ARMAZEM_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <array>
#include <time.h>
using namespace std;
#include "Depositos.h"
#include "Depositos_Normais.h"
#include "Depositos_Frescos.h"
#include "GraphStlPath.h"

template <class T>
class Armazem : public graphStlPath<Depositos<T>*, int> {
private:
    int depos_normais;
    int depos_frescos;
    int paletes_DN;
    int paletes_DF;
    int max;
    int min;
    vector<Depositos<T>*> depositos;
    int ** distancia;

    void mostracaminho(int vi, const vector<int> &path);
    void menorcaminho(Depositos<T>* &ci, Depositos<T>* &cf);


public:
    Armazem();
    Armazem(int dep_normais, int dep_frescos, int paletes_depnor, int paletes_depfre);
    Armazem(const Armazem &ware);
    ~Armazem();

    Armazem* clone() const;
    int getDepos_normais() const;
    int getDepos_frescos() const;
    int getPaletes_deposnormais() const;
    int getPaletes_deposfrescos() const;
    int getSize() const;
    //int [] getDistancia() const;
    void setDepos_normais(int dep_norm);
    void setDepos_frescos(int dep_fres);
    void setPaletes_deposnormais(int paletes_dn);
    void setPaletes_deposfrescos(int paletes_df);
    void setMax(int max);
    void setMin(int min);
    //    void setDistancia(int limSup, int limInf);

    Armazem<T> & operator=(const Armazem & arm);

    void adicionarDepositos();
    void listar();
    void listarProduto() const;
    void inserirProduto(const T& p);
    void expedirProduto(int quant);
    void criarFicheiro() const;
    void distanciaDepositos();
    void listardistanciaDepositos();
    void getProduto() const;
    void write(ostream &out) const;
    /*2™parte*/
    void leituraFicheiro();
    /*a*/
    void criarGrafo();
    void listarGrafo();

    /*b**/
    void todospercursospossiveis();

    /*c*/
    void tipodepositos();

    /*d*/
    void menorcaminhodistancia();

};

template <class T>
Armazem<T>::Armazem() : graphStlPath<Depositos<T>*, int>(), depos_normais(0), depos_frescos(0), paletes_DN(0), paletes_DF(0), depositos() {
};

template<class T>
Armazem<T>::Armazem(int dep_normais, int dep_frescos, int paletes_depnor, int paletes_depfre) : graphStlPath<Depositos<T>*, int>() {
    this->depos_normais = dep_normais;
    this->depos_frescos = dep_frescos;
    this->paletes_DN = paletes_depnor;
    this->paletes_DF = paletes_depfre;

    distancia = new int*[dep_normais + dep_frescos];
    for (int i = 0; i < (dep_normais + dep_frescos); i++) {
        distancia[i] = new int[dep_normais + dep_frescos];
    }
};

template <class T>
Armazem<T>::Armazem(const Armazem & arm) : graphStlPath<Depositos<T>*, int>(arm) {
    this->depos_normais = arm.depos_normais;
    this->depos_frescos = arm.depos_frescos;
    this->paletes_DN = arm.paletes_DN;
    this->paletes_DF = arm.paletes_DF;
    this->depositos = arm.depositos;
    this->distancia = arm.distancia;
};

template <class T>
Armazem<T>::~Armazem() {
};

template <class T>
Armazem<T> * Armazem<T>::clone() const {
    return new Armazem<T>(*this);
}

template <class T>
Armazem<T> & Armazem<T>::operator=(const Armazem<T> &arm) {
    if (this != &arm) {
        this->depos_normais = arm.depos_normais;
        this->depos_frescos = arm.depos_frescos;
        this-> paletes_DN = arm.paletes_DN;
        this->paletes_DF = arm.paletes_DF;
        this-> max = arm.max;
        this-> min = arm.min;
        this->depositos = arm.depositos;
        this->distancia = arm.distancia;
    }
    return (*this);
}

template<class T>
void Armazem<T>::write(ostream & out) const {
    out << "    O armazem e constituido por:" << endl;
    out << "Depositos Normais: " << this->depos_normais << "    Depositos frescos com refrigeracao: " << this->depos_frescos << endl;
    out << "Paletes Depositos normais: " << this->paletes_DN << "    Paletes DepÛsitos Frescos: " << this->paletes_DF << endl;
    //    out << "Distancia entre paletes: " << distancia << endl;
    if (depositos.size() == 0) {
        out << "Nao existem depositos criados!" << endl;
    } else {
        out << endl;
        out << "    Depositos Armazenados" << endl;
        for (int i = 0; i < depositos.size(); i++) {
            (*depositos[i]).getDescricao();
            out << "      Produtos Armazenados no deposito " << depositos[i]->getID() << endl;
            (*depositos[i]).listarProduto();
        }
    }
}

template <class T>
ostream & operator<<(ostream &out, const Armazem<T> & arm) {
    arm.write(out);
    return out;
}

template <class T>
int Armazem<T>::getDepos_normais() const {
    return (this->depos_normais);
}

template <class T>
int Armazem<T>::getDepos_frescos() const {
    return (this->depos_frescos);
}

template <class T>
int Armazem<T>::getPaletes_deposnormais() const {
    return (this->paletes_DN);
}

template <class T>
int Armazem<T>::getPaletes_deposfrescos() const {
    return (this->paletes_DF);
}

template <class T>
int Armazem<T>::getSize() const {
    return depositos.size();
}

template <class T>
void Armazem<T>::setDepos_normais(int dep_norm) {
    this->depos_normais = dep_norm;
}

template <class T>
void Armazem<T>::setDepos_frescos(int dep_fres) {
    this->depos_frescos = dep_fres;
}

template <class T>
void Armazem<T>::setPaletes_deposnormais(int paletes_dn) {
    this->paletes_DN = paletes_dn;
}

template <class T>
void Armazem<T>::setPaletes_deposfrescos(int paletes_df) {
    this->paletes_DF = paletes_df;
}

template <class T>
void Armazem<T>::setMax(int max) {
    this->max = max;
}

template <class T>
void Armazem<T>::setMin(int min) {
    this->min = min;
}

template <class T>
void Armazem<T>::adicionarDepositos() {
    int id = 0;
    for (int i = 0; i < depos_normais; i++) {
        depositos.push_back(new Depositos_Normais<T>(id, paletes_DN, rand() % (max - min + 1) + min, rand() % (max - min + 1) + min));
        id++;
    }
    for (int i = 0; i < depos_frescos; i++) {
        depositos.push_back(new Depositos_Frescos<T>(id, paletes_DF, rand() % (max - min + 1) + min, rand() % (max - min + 1) + min));
        id++;
    }
}

template <class T>
void Armazem<T>::listar() {
    for (Depositos<T>* d : depositos)
        (*d).getDescricao();
}

template <class T>
void Armazem<T>::inserirProduto(const T& p) {
    bool flag = false;
    for (int i = 0; i < depositos.size(); i++) {
        if (flag == false) {
            if (typeid (*depositos[i]) == typeid (Depositos_Normais<T>)) { //&& (*it)->getTipo() == "Normal"
                flag = depositos[i]->inserirProduto(p);
                if (flag == true) cout << "Inseriu o produto " << p << " no deposito normal" << endl;
            }
            if (typeid (*depositos[i]) == typeid (Depositos_Frescos<T>)) { //&& (*it)->getTipo() == "Fresco"
                if (flag == false) {
                    flag = depositos[i]->inserirProduto(p);
                    if (flag == true) cout << "Inseriu o produto " << p << " no deposito fresco" << endl;
                }
            }
        }
    }
    if (flag == false) cout << "Depositos cheios!" << endl;
    flag = false;
}

template <class T>
void Armazem<T>::expedirProduto(int quant) {
    cout << "   Produtos Expedidos:" << endl;
    for (int i = 0; i < depositos.size(); i++) {
        if (quant != 0) {
            cout << "DEPÓSITO NR:" << depositos[i] << endl;
            quant -= depositos[i]->expedirProdutos(quant);
        }
    }
}

template<class T>
void Armazem<T>::criarFicheiro() const {
    ofstream outfile;
    vector<T> aux;
    int id = 0;
    if (!outfile) {
        cout << "ERRO AO ABRIR O FICHEIRO" << endl;
        exit(1);
    }
    outfile.open("Armazem.txt");
    outfile << this->depos_normais << "," << this->depos_frescos << "," << this->paletes_DN << "," << this->paletes_DF << "\r\n";
    for (Depositos<T>* it : depositos) {
        outfile << (*it).getID() << "," << (*it).getNumero_paletes() << ","
                << (*it).getCapacidade_maxima() << "," << (*it).getArea_Maxima() << "\r\n";
        aux = (*it).getProduto();
        if (!aux.empty()) {
            //            outfile << "\t";
            for (T prod : aux) {
                outfile << prod << ";";
            }
            outfile << "\r\n";
        }
    }
    for (int i = 0; i < depositos.size(); i++) {
        for (int j = 0; j < depositos.size(); j++) {
            if (i != j) {
                outfile << distancia[i][j] << ";";
            } else {
                outfile << "-1;";
            }
        }
        outfile << "\r\n";
    }
    outfile.close();
}

template <class T>
void Armazem<T>::distanciaDepositos() {
    srand(time(NULL));
    int minimo = 0;
    for (int i = 0; i < depositos.size(); i++) {
        for (int j = i + 1; j < depositos.size(); j++) {
            distancia[i][j] = rand() % (max - minimo + 1) + minimo;
            distancia[j][i] = distancia[i][j];
        }
    }
}

template <class T>
void Armazem<T>::listardistanciaDepositos() {
    for (int i = 0; i < depositos.size(); i++) {
        cout << "Depositos " << i << ": \t";
        for (int j = 0; j < depositos.size(); j++) {
            if (i != j) {
                cout << distancia[i][j] << "\t";
            } else
                cout << "-\t";
        }
        cout << "\n";
    }
}

template<class T>
void Armazem<T>::listarProduto() const {
    for (Depositos<T>* it : depositos) {
        if (typeid (*it) == typeid (Depositos_Normais<T>)) {
            (*it).listarProduto();
        }
        if (typeid (*it) == typeid (Depositos_Frescos<T>)) {
            (*it).listarProduto();
        }
    }
}

template <class T>
void Armazem<T>::getProduto() const {
    for (int i = 0; i < depositos.size(); i++) {
        depositos[i]->getProduto();
    }
}

/*2™ Parte*/

template <class T>
void Armazem<T>::leituraFicheiro() {
    ifstream infile;
    string linha, linha2, linha3;

    int inic = 0, cont = 0, pos2, j = 0;
    int capacidademaxima = 0;
    bool flag = false;

    infile.open("Armazem.txt");
    if (!infile) {
        cout << "Armazem.txt nao existe!" << endl;
    } else {
        //vai buscar os dados do armazem na 1∫ linha;
        getline(infile, linha, '\n');
        if (linha.size() > 0) {
            int pos = linha.find(',', inic);
            string depos_normaisTXT(linha.substr(inic, pos - inic));
            pos++;

            inic = pos;
            pos = linha.find(',', inic);
            string depos_frescosTXT(linha.substr(inic, pos - inic));
            pos++;

            inic = pos;
            pos = linha.find(',', inic);
            string paletes_DNTXT(linha.substr(inic, pos - inic));
            pos++;

            inic = pos;
            pos = linha.find(',', inic);
            string paletes_DFTXT(linha.substr(inic, pos - inic));
            pos++;

            this->depos_normais = atoi(depos_normaisTXT.c_str());
            this->depos_frescos = atoi(depos_frescosTXT.c_str());
            this->paletes_DN = atoi(paletes_DNTXT.c_str());
            this->paletes_DF = atoi(paletes_DFTXT.c_str());
        }
        getline(infile, linha2, '\n');
        //Depositos : ID(0), numero_paletes(0), capacidade_maxima(0), area_total(0)
        for (int i = 0; i < (depos_normais + depos_frescos); i++) {
            if (flag == true) getline(infile, linha2, '\n');
            flag = false;
            inic = 0;
            int pos = linha2.find(',', inic);
            string ID(linha2.substr(inic, pos - inic));
            int id = atoi(ID.c_str());
            pos++;

            inic = pos;
            pos = linha2.find(',', inic);
            string Num_paletes(linha.substr(inic, pos - inic));
            int num_pal = atoi(Num_paletes.c_str());
            pos++;

            inic = pos;
            pos = linha2.find(',', inic);
            string capac_maxima(linha2.substr(inic, pos - inic));
            int cap_max = atoi(capac_maxima.c_str());
            capacidademaxima += cap_max;
            pos++;

            inic = pos;
            pos = linha2.find(',', inic);
            string areatotal(linha2.substr(inic, pos - inic));
            int are_tot = atoi(areatotal.c_str());

            if (i < depos_normais) {
                depositos.push_back(new Depositos_Normais<T>(id, paletes_DN, cap_max, are_tot));
            } else {
                depositos.push_back(new Depositos_Frescos<T>(id, paletes_DF, cap_max, are_tot));
            }
            getline(infile, linha2, '\n');
            while (pos2 != -1) {
                if (cont == 0) {
                    inic = 0;
                    pos2 = linha2.find(';', inic);
                    if (pos2 == -1) break;
                    flag = true;
                    string prod(linha2.substr(inic, pos2 - inic)); //pos
                    int produto = atoi(prod.c_str());
                    depositos[i]->inserirProduto(produto);
                    pos2++;
                    inic = pos2;
                } else {
                    pos2 = linha2.find(';', inic);
                    if (pos2 == -1) break;
                    flag = true;
                    string prod(linha2.substr(inic, pos2 - inic));
                    int produto = atoi(prod.c_str());
                    depositos[i]->inserirProduto(produto);
                    pos2++;
                    inic = pos2;
                }
                cont++;
            }; //0
            cont = 0;
            //            if (flag == true) getline(infile, linha2, '\n');
            //flag=false;
        }
        //        getline(infile, linha3, '\n');
        distancia = new int*[(depos_normais + depos_frescos)];
        for (int i = 0; i < (depos_normais + depos_frescos); i++) {
            distancia[i] = new int[(depos_normais + depos_frescos)];
        }
        for (int i = 0; i < depositos.size(); i++) {
            for (j = 0; j < depositos.size(); j++) {
                if (j == 0) {
                    inic = 0;
                    pos2 = linha2.find(';', inic);
                    string dist(linha2.substr(inic, pos2 - inic));
                    int distanc = atoi(dist.c_str());
                    if (distanc == -1)
                        distancia[i][j] = 0;
                    else
                        distancia[i][j] = distanc;
                    //                    cout << distancia[i][j] << "-->" << dist << endl;
                    pos2++;
                    inic = pos2;
                } else {
                    pos2 = linha2.find(';', inic);
                    string dist(linha2.substr(inic, pos2 - inic));
                    int distanc = atoi(dist.c_str());
                    if (distanc == -1)
                        distancia[i][j] = 0;
                    else
                        distancia[i][j] = distanc;
                    pos2++;
                    inic = pos2;
                }
                distancia[j][i] = distancia[i][j];
            }
            getline(infile, linha2, '\n');
        }
    }
    infile.close();
}

template <class T>
void Armazem<T>::criarGrafo() {
    for (int i = 0; i < depositos.size(); i++) {
        for (int j = 0; j < depositos.size(); j++) {
            if (distancia[i][j] != 0 && i != j)
                this->addGraphEdge(distancia[i][j], (depositos[i]), (depositos[j]));
        }
    }
}

template <class T>
void Armazem<T>::listarGrafo() {
    graphStl<Depositos<T>*, int>::write(cout);
}

template<class T>
void Armazem<T>::todospercursospossiveis() {
    srand(time(NULL));
    int cidep, cfdep;
    do {
        cidep = rand() % (depositos.size() - 0 + 1) + 0;
        cfdep = rand() % (depositos.size() - 0 + 1) + 0;
    } while (cidep == cfdep);

    Depositos <T>* ci;
    Depositos <T>* cf;

    ci = depositos[cidep];
    cf = depositos[cfdep];

    cout << "Distancia entre Deposito " << depositos[cidep]->getID() << " e Deposito " << depositos[cfdep]->getID() << endl;
    Depositos <T>* auxStop;
    int ramo;

    queue <stack < Depositos<T>*>> qr = this->distinctPaths(ci, cf);
    stack <Depositos<T>*> s;

    int tamQr = qr.size();
    int tamS = 0;
    for (int i = 0; i < tamQr; i++) {
        s = qr.front();
        qr.pop();
        tamS = s.size();
        for (int j = 0; j < tamS; j++) {
            if (j == tamS - 1) {
                cout << s.top();
            } else {
                cout << s.top() << " ";
                auxStop = s.top();
                s.pop();
                this->getEdgeByVertexContents(ramo, s.top(), auxStop);
                cout << "(" << ramo << ") -> ";
            }
        }
        cout << endl;
    }
}

template<class T>
void Armazem<T>::menorcaminhodistancia() {
    srand(time(NULL));
    int cidep, cfdep;
    do {
        cidep = rand() % (depositos.size() - 0 + 1) + 0;
        cfdep = rand() % (depositos.size() - 0 + 1) + 0;
    } while (cidep == cfdep);

    Depositos <T>* ci;
    Depositos <T>* cf;

    ci = depositos[cidep];
    cf = depositos[cfdep];

    cout << "Menor distancia entre " << ci << " e " << cf << " -> ";
    menorcaminho(ci, cf);
}

template <class T>
void Armazem<T>::menorcaminho(Depositos<T>* &ci, Depositos<T>* &cf) {
    vector<int> path;
    vector<int> dist;
    int key;

    this->getVertexKeyByContent(key, cf);
    this->dijkstrasAlgorithm(ci, path, dist);
    cout << dist[key] << " m " << endl;
    cout << ci;
    mostracaminho(key, path);
}

template <class T>
void Armazem<T>::mostracaminho(int vi, const vector<int>& path) {
    if (path[vi] == -1) return;
    mostracaminho(path[vi], path);
    int e;
    this->getEdgeByVertexKeys(e, path[vi], vi);
    Depositos<T>* c;
    this->getVertexContentByKey(c, vi);
    cout << "(" << e << ")" << " -> " << c;
}

template <class T>
void Armazem<T>::tipodepositos() {
    srand((unsigned) time(NULL));
    int cidep, cfdep;
    Depositos <T>* ci;
    Depositos <T>* cf;
    do {
        cidep = rand() % (depositos.size() - 0 + 1) + 0;
        cfdep = rand() % (depositos.size() - 0 + 1) + 0;
    } while (cidep == cfdep);

    ci = depositos[cidep];
    cf = depositos[cfdep];
    cout << "Distancia entre Deposito " << depositos[cidep]->getID() << " e Deposito " << depositos[cfdep]->getID() << endl;

    queue<stack < Depositos<T>*>> caminhosdistintos = this->distinctPaths(ci, cf);
    stack<Depositos<T>*> caminho;
    stack<Depositos<T>*> caminhoFinal;
    int tamanho = caminhosdistintos.size();

    int ramo;
    int count = 0;
    bool flag = false;
    Depositos<T>* auxStop;

    for (int i = 0; i < tamanho; i++) {
        caminho = caminhosdistintos.front();

        int taman = caminho.size();
        count = 0;
        while (!caminhoFinal.empty() && flag == false)
            caminhoFinal.pop();

        for (int i = 0; i < taman; i++) {
            Depositos<T>* aux = caminho.top();
            if (typeid (*aux) == typeid (*ci)) { /*Verifica se é do mesmo tipo que o 1 deposito*/
                if (typeid (*aux) == typeid (Depositos_Normais<T>) && flag == false) {
                    caminhoFinal.push(caminho.top());
                    count++;
                } else {
                    if (typeid (*aux) == typeid (Depositos_Frescos<T>) && flag == false) {
                        caminhoFinal.push(caminho.top());
                        count++;
                    }
                }
            }
            caminho.pop();
        }
        int tam = caminhoFinal.size();
        if (tam == count && count > 0) {
            flag = true;
            for (int i = 0; i < tam; i++) {
                if (i == tam - 1) {
                    cout << caminhoFinal.top();
                } else {
                    cout << caminhoFinal.top() << " -> ";
                    auxStop = caminhoFinal.top();
                    caminhoFinal.pop();
                    this->getEdgeByVertexContents(ramo, caminhoFinal.top(), auxStop);
                    cout << "(" << ramo << ") -> ";
                }
            }
        } else {
            caminhosdistintos.pop();
        }


    }
    if (flag == false)
        cout << "Não existem ligações entre " << depositos[cidep]->getID() << " e " << depositos[cfdep]->getID() << endl;
    /*Apresentar um percurso entre dois depósitos que envolva apenas um tipo de depósito (fresco/normal)*/
}

#endif	/* ARMAZEM */