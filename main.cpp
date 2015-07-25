/* 
 * File:   main.cpp
 * Author: Tiago
 *
 * Created on 25 de Outubro de 2014, 17:43
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
//#include "Produto.h"
#include "Depositos.h"
#include "Depositos_Frescos.h"
#include "Depositos_Normais.h"
#include "Armazem.h"
#include "GraphStlPath.h"

Armazem<int> armazem;
Armazem<int> armazemLeitura;

void Submenu1parte(int max, int min);
void Submenu2parte();
void menu();

int main(int argc, char** argv) {
    menu();
    return 0;
}

void menu() {
    int selection, max, min;
    cout << "**************************************" << endl;
    cout << "*  Bem vindo ao simulador de armazem *" << endl;
    cout << "*                                    *" << endl;
    cout << "*                                    *" << endl;
    cout << "* 1- Criar Armazem                   *" << endl;
    cout << "* 2- Leitura do Ficheiro             *" << endl;
    cout << "* 0- Sair                            *" << endl;
    cout << "*                                    *" << endl;
    cout << "**************************************" << endl;
    cout << "Introduzir opção: ";
    cin >> selection;

    switch (selection) {
        case 1:
        {
            do {
                cout << "Introduza o limite maximo de depositos: ";
                cin>> max;
                cout << "Introduza o limite minimo de depositos: ";
                cin>> min;
            } while (min > max || min == max || min == 0 || max == 0);

            srand(time(NULL));
            Armazem<int> arm(rand() % (max - min + 1) + min, rand() % (max - min + 1) + min, rand() % (max - min + 1) + min, rand() % (max - min + 1) + min);
            armazem = arm;
            armazem.setMax(max);
            armazem.setMin(min);
            cout << endl;
            cout << "   **Conteúdo do Armazém *" << endl;
            cout << armazem << endl;
            
            Submenu1parte(max, min);
            break;
        }
        case 2:
            Submenu2parte();
            break;
        case 0:
            cout << "© 2014 by Tiago Macedo & Diogo Almeida " << endl;
            exit(0);
            break;
        default:
            cout << "Opção invalida!!" << endl;
            menu();
    }
}

void Submenu1parte(int max, int min) {
    int selection, numProd, expProd;
    /*SubMenu-CriarArmazem*/
    cout << "**************************************" << endl;
    cout << "*        Simulador de Armazem        *" << endl;
    cout << "*                                    *" << endl;
    cout << "*                                    *" << endl;
    cout << "* 1- Adicionar Depositos             *" << endl;
    cout << "* 2- Inserir Produtos                *" << endl;
    cout << "* 3- Expedir Produtos                *" << endl;
    cout << "* 4- Distancias entre os depositos   *" << endl;
    cout << "* 5- Criar Ficheiro                  *" << endl;
    cout << "* 6- Listar Armazem                  *" << endl;
    cout << "* 7- Voltar ao menu anterior         *" << endl;
    cout << "* 0- Sair                            *" << endl;
    cout << "*                                    *" << endl;
    cout << "**************************************" << endl;
    cout << "Introduzir opção: ";
    cin>> selection;
    switch (selection) {
        case 1:
            cout << "   **A criar depositos**" << endl;
            armazem.adicionarDepositos();
            cout << endl;
            cout << "   **Depositos criados** " << endl;
            armazem.listar();
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 2:
            numProd = rand() % (max - min + 1) + min;
            cout << "   **A inserir produtos**" << endl;
            cout << "   Quantidade de produtos a inserir: " << numProd << endl;
            for (int i = 0; i < numProd; i++) {
                armazem.inserirProduto(i);
            }
            cout << "   **Produtos inseridos**" << endl;
            cout << endl;
            armazem.listarProduto();
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 3:
            expProd = rand() % (max - min + 1) + min;
            cout << "   Quantidade de produtos a expedir: " << expProd << endl;
            armazem.expedirProduto(expProd);
            cout << "   **Produtos expedido**" << endl;
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 4:
            cout << "   **Calcular distancias entre os depositos**" << endl;
            armazem.distanciaDepositos();
            cout << "   **Distancia criada**" << endl;
            cout << endl;
            armazem.listardistanciaDepositos();
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 5:
            cout << "   **Enviar dados para ficheiro de texto** " << endl;
            armazem.criarFicheiro();
            cout << "   **Ficheiro criado**" << endl;
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 6:
            cout << armazem << endl;
            cout << endl << endl;
            Submenu1parte(max, min);
            break;
        case 7:
            menu();
            break;
        case 0:
            cout << "© 2014 by Tiago Macedo & Diogo Almeida " << endl;
            exit(0);
            break;
        default:
            cout << "Opção invalida!!" << endl;
            Submenu1parte(max, min);
    }
}

void Submenu2parte() {
    int selection;
    /*SubMenu-Lerficheiro*/
    cout << "****************************************************************" << endl;
    cout << "*                  Simulador de Armazem                        *" << endl;
    cout << "*                                                              *" << endl;
    cout << "*                                                              *" << endl;
    cout << "* 1- Leitura do Ficheiro Armazem                               *" << endl;
    cout << "* 2- Criar Grafo                                               *" << endl;
    cout << "* 3- Listar todos os caminhos possiveis entre dois depositos   *" << endl;
    cout << "* 4- Listar percurso entre dois depositos do mesmo tipo        *" << endl;
    cout << "* 5- Calcular o percurso mais curto entre dois depositos       *" << endl;
    cout << "* 6- Voltar ao menu anterior                                   *" << endl;
    cout << "* 0- Sair                                                      *" << endl;
    cout << "*                                                              *" << endl;
    cout << "****************************************************************" << endl;
    cout << "Introduzir opção: ";
    cin>> selection;

    switch (selection) {
        case 1:
            armazemLeitura.leituraFicheiro();
            cout << armazemLeitura << endl;
            cout << endl;
            Submenu2parte();
        case 2:
            armazemLeitura.criarGrafo();
            cout << "Grafo criado" << endl;
            armazemLeitura.listarGrafo();
            cout << endl;
            Submenu2parte();
        case 3:
            srand(time(NULL));
            armazemLeitura.todospercursospossiveis();
            cout << endl;
            Submenu2parte();
        case 4:
            srand(time(NULL));
            armazemLeitura.tipodepositos();
            cout << endl;
            Submenu2parte();
        case 5:
            srand(time(NULL));
            armazemLeitura.menorcaminhodistancia();
            cout << endl;
            Submenu2parte();
        case 6:
            menu();
        case 0:
            cout << "© 2014 by Tiago Macedo & Diogo Almeida " << endl;
            exit(0);
            break;
        default:
            cout << "Opção invalida!!" << endl;
            Submenu2parte();
    }
}