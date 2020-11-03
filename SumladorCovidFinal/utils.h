/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: treys
 *
 * Created on 25 de maio de 2020, 06:15
 */

#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAXNOME 20
#define BASEDIASDOENTE  5




// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int randomInt(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);


//erro durante alguma fase do programa
void Abort(char * msg);

void warning(char * msg);

void getEnter();

int *alocaArray(int * novo, int num);

int *acrescentaAArray(int * novo, int num);

void imprimeGrafico(int *a, int *b, int *c, int num);

int contemIguais(int tab[], int tam);

int diasMax(int idade);
#endif /* UTILS_H */



