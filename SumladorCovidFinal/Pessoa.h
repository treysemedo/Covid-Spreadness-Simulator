/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pessoa.h
 * Author: treys
 *
 * Created on 25 de maio de 2020, 06:14
 */


#include"utils.h"
#include <ctype.h>
#ifndef PESSOA_H
#define PESSOA_H



typedef struct pessoas{
    char *id;
    int idade;
    char estado;
    int diasInfetado;
    struct pessoas* prox;
}pessoa, *ppessoa;


//le e guarda ficheiro de texto em lista ligada, retorna ponteiro para inico da lista
ppessoa leFichPessoa(char *nomeFich);

int existeId(ppessoa p, char * id);
//liberta a memoria alocada para as pessoas
void libertaMPessoas(ppessoa p);

//valida os dados das pessoas, retorna -1, caso for invalidado
int verificaPessoas(ppessoa p);
//devolve numero totatl de pessoas
int contaPessoas(ppessoa p);

void imprimePessoas(ppessoa cabecalho);

ppessoa getPessoa(ppessoa p, int pos);

void setEstado(ppessoa p, char e);

char getEstado(ppessoa p);

void getDados(ppessoa cabecalho, int *numD, int *numS, int *numI, int *total);


#endif /* PESSOA_H */