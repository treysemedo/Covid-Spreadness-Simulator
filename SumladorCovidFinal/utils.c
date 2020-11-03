/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.h"
#include <time.h>
#include <ctype.h>
#include <string.h> 

void initRandom() {
    srand(time(NULL));
}

int randomInt(int a, int b) {
    return a + rand() % (b - a + 1);
}

int probEvento(float prob) {
    float aux = (float) rand() / RAND_MAX;
    return prob > aux;
}

void Abort(char * msg) {
    printf("\t\t\t\tERRO:%s\nPrograma Terminado\n", msg);
    exit(-1);
}

void warning(char * msg) {
    printf("\n\n\t\t\t\tWarning:%s\n\n\n", msg);

}

void getEnter() {
    char prev = 0;
    printf("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR");
    while (1) {
        char c = getchar();

        if (c == '\n' && prev == c) {
            // double return pressed!
            break;
        }

        prev = c;
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int *alocaArray(int * novo, int num) {


    if (num == 0) {
        return NULL;
    }
    novo = malloc(sizeof (int)*num);
    if (novo == NULL) {
        Abort("ALOCA erro criacao array");
    }
    return novo;

}

int *acrescentaAArray(int * novo, int num) {
    int *aux = NULL;

    if (num == 1) {
        novo = malloc(sizeof (int));
        if (novo == NULL) {
            Abort("ACRESCENTA erro criacao array");
        }
    } else {
        aux = realloc(novo, sizeof (int)*num);
        if (aux == NULL) {
            Abort("ACRESCENTA erro realocacao array");
        } else {
            novo = aux;
        }
    }

    return novo;

}

int contemIguais(int tab[], int tam) {
    int i = 0, j = 0;
    for (i = 0; i < tam; i++) {
        for (j = i + 1; j < tam; j++) {
            if (tab[i] == tab[j]) {
                return 1;
            }
        }
    }
    return -1;
}

int diasMax(int idade) {
    int aux;
    aux = (int) idade / 10;
    aux += BASEDIASDOENTE;
    return aux;
}