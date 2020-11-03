/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: treys
 *
 * Created on 25 de maio de 2020, 06:14
 */

#include <stdio.h>
#include <stdlib.h>
#include "Simulacao.h"

/*
 * 
 */
int main(int argc, char** argv) {

    simulacao simula;
    simula.anterior=NULL;
    pSimulacao simulacao=&simula;

    
    simulacao=fase1(simulacao);

    fase2(simulacao);

 
   
}

