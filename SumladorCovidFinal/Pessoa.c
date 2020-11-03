/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"Pessoa.h"

int existeId(ppessoa p, char * id) {
    ppessoa aux = p;

    while (aux != NULL) {
        if (strcmp(aux->id, id) == 0) {
            return 1;
        }
        aux = aux->prox;
    }

    return -1;
}

ppessoa criarNovaPessoa(char * buffer) {
    int i = 0;
    ppessoa novo = malloc(sizeof (pessoa));

    if (novo == NULL) {
        return NULL;
    }

    char *token = strtok(buffer, " ");

    novo->diasInfetado = -1;
    //alocar espaço para o id
    novo->id = malloc(sizeof (char) * strlen(token));
    if (novo->id == NULL) {
        free(novo);
        return NULL;
    }


    //copiar id 

    strcpy(novo->id, token);
    token = strtok(NULL, " ");

    //verificar tipo de dados e atribuir idade
    for (i = 0; i < strlen(token); i++) {
        if (isdigit(token[i]) == 0)
            return NULL;
    }
    novo->idade = atoi(token);


    //receber estado
    token = strtok(NULL, " ");
    novo->estado = token[0];

    token = strtok(NULL, " ");
    if (novo->estado == 'D') {
        //verificar tipo de dados e atribuir dias doente
        for (i = 0; i < strlen(token); i++) {
            if (isdigit(token[i]) == 0)
                return NULL;
        }
        novo->diasInfetado = atoi(token);
    }

    novo->prox = NULL;

    return novo;
}

ppessoa leFichPessoa(char *nomeFich) {
    ppessoa cabecalho = NULL, temp = NULL;
    char buffer[100];

    FILE* ficheiro = fopen(nomeFich, "rt");

    if (ficheiro == NULL) {
        return NULL;
    }


    while (fscanf(ficheiro, " %[^\n]", buffer) == 1) {
        temp = criarNovaPessoa(buffer);
        if (temp == NULL) {
            fclose(ficheiro);
            return NULL;
        }

        if (existeId(cabecalho, temp->id) != 1) {
            temp->prox = cabecalho;
            cabecalho = temp;
        } else
            free(temp);
    }

    fclose(ficheiro);


    return cabecalho;
}

void libertaMPessoas(ppessoa p) {

    ppessoa aux;
    while (p != NULL) {
        aux = p;
        p = p->prox;
        free(aux);

    }
}

void imprimePessoas(ppessoa cabecalho) {
    ppessoa aux = cabecalho;
    int numS = 0, numD = 0, numI = 0, total = 0;
    printf("\n\t\t\tLista Pessoas:\n");
    while (aux != NULL) {
        fflush(stdout);
        printf("\t\t\t\t%-20s %d\t%c\t%d\n", aux->id, aux->idade, aux->estado, aux->diasInfetado);
        aux = aux->prox;
    }


}

void getDados(ppessoa cabecalho, int *numD, int *numS, int *numI, int *total) {
    ppessoa aux = cabecalho;
    while (aux != NULL) {

        (*total)++;
        switch (aux->estado) {
            case 'D':
                (*numD)++;
                break;
            case 'S':
                (*numS)++;
                break;
            case 'I':
                (*numI)++;
                break;

        }

        aux = aux->prox;
    }

}

void setEstado(ppessoa p, char e) {
    switch (p->estado) {
        case 'I':
            break;
        case 'S':
            if (e == 'D') {
                p->estado = e;
                p->diasInfetado = 0;
            }
            break;
        case 'D':
            p->diasInfetado = -1;
            p->estado = e;
            break;
    }
}

ppessoa getPessoa(ppessoa p, int pos) {
    int i = 0;

    while (p != NULL && i < pos) {
        p = p->prox;
        i++;
    }

    return p;
}

int verificaPessoas(ppessoa p) {
    ppessoa aux = p;


    while (aux != NULL) {
        if (aux->idade < 0 || aux->idade >= 130)
            return -1;

        if (aux->estado != 'S' && aux->estado != 'D' && aux->estado != 'I')
            return -1;

        if (aux->diasInfetado != -1 && aux->estado != 'D')
            return -1;

        if (aux->diasInfetado < 0 && aux->diasInfetado != -1)
            return -1;

        aux = aux->prox;
    }
    return 1;
}

int contaPessoas(ppessoa p) {
    ppessoa aux = p;
    int conta = 0;
    while (aux != NULL) {
        conta++;
        aux = aux->prox;
    }
    return conta;
}