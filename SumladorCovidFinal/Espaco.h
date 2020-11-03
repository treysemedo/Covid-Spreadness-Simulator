/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Espaco.h
 * Author: treys
 *
 * Created on 25 de maio de 2020, 06:20
 */

#ifndef ESPACO_H
#define ESPACO_H

#include "Pessoa.h"
#include <ctype.h>
#define MAXLIGACAO 3
typedef struct sala{
 int id; // id numérico do local
 int capacidade; // capacidade máxim
 int liga[3]; // id das ligações (-1 nos casos não usados)
 
}local, *plocal;


typedef struct espacos{
    plocal salas;
    ppessoa *pessoas;
    int numSalas;
}espaco, *pespaco;


//le e guarda ficheiro binario em vetor dinamico de estruturas
pespaco leFichEspaco(char* nomeFich,pespaco e1);
int verificaEspaco(pespaco e);
//liberta a memoria alocada para as salas
void libertaMEspaco(pespaco e);
void imprimeEspaco(pespaco e);
pespaco associaPessoasSala(pespaco e, ppessoa pessoa);
void imprimeReunioes(pespaco e);
pespaco adcionaDoente(pespaco e);
pespaco move(pespaco e);
void guardaPessoas(pespaco e);


//void imprimereunioes(preuniao espaco, int tam);
//preuniao libertaMreunioes(preuniao espaco, int tam);
//preuniao adcionaDoente(preuniao espaco, int tam);
//preuniao move(preuniao espaco, int tam);
//void guardaPessoas(preuniao espaco, int tam);

#endif /* ESPACO_H */

