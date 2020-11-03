/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulacao.h
 * Author: treys
 *
 * Created on 25 de maio de 2020, 07:50
 */

#ifndef SIMULACAO_H
#define SIMULACAO_H
#include "Espaco.h"
#define TDISSEMINACAO 0.2
#define TAXAIMUNIDADE 0.2

typedef struct dado{
    int numDoentes;
    int numSaudaveis;
    int numImundes;
    int populacao;
    int dias;
    int *numInfetadosDia, *numRecuperadosDia, *numImunesDia;
}dados, *pdados;

typedef struct simulator{
    dados dados;
    espaco espaco;
    struct simulator* anterior;
    
}simulacao, *pSimulacao;





pSimulacao fase1(pSimulacao simulacao);

void fase2(pSimulacao simulacao);
#endif /* SIMULACAO_H */

