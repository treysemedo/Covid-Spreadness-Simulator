/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include"Espaco.h"

pespaco leFichEspaco(char* nomeFich,pespaco e1){
    
    
    z
    int numSala=e1->numSalas=0;;
   
    plocal novo;
    
    FILE* ficheiro = fopen(nomeFich, "rb");
   
    if (ficheiro == NULL) {
        Abort("não foi possivel abrir ficheiro com espaços");
    }
    
    if (fread(&aux, sizeof (local), 1, ficheiro) == 1) {
        //alocar memoria dinamicamente para uma sala e ler a primeira
        e1->salas = malloc(1 * sizeof (local));
        if (e1->salas == NULL) {
            fclose(ficheiro);
            Abort("erro malloc salas");
        }

        e1->salas[numSala++] = aux;
    }
     while (fread(&aux, sizeof (local), 1, ficheiro) == 1) {
        novo = realloc(e1->salas, (numSala + 1) * sizeof (local));
        if (novo == NULL) {
            warning("não é possivel reallocar mais memoria");
        }else{
            e1->salas=novo;
        }
        e1->salas[numSala++] = aux;
    }
    e1->numSalas=numSala;
    fclose(ficheiro);
   
    return e1;
  
}

void imprimeEspaco(pespaco e) {
    int i = 0;
    printf("\n\t\t\tSalas:\n");
    for (i = 0; i < e->numSalas; i++) {
        printf("\t\t\t\tid:%d capacidade:%d ligacao:%d %d %d\n", e->salas[i].id, e->salas[i].capacidade, e->salas[i].liga[0], e->salas[i].liga[1], e->salas[i].liga[2]);
    }
}

int posSala(espaco *e, int tam, int id) {
    int i = 0;
    for (i = 0; i < tam; i++) {
        if (id == e->salas[i].id)
            return i;
    }
    return -1;
}

int verificaSala(local *l) {
    int i = 0;
    if (l->capacidade < 0 || l->id < 0)
        return -1;
    for (i = 0; i < MAXLIGACAO; i++) {
        if (l->liga[i] == l->id)
            return -1;
    }
    return 1;
}

int verificaLigacoes(pespaco e, plocal l, int pos) {

    int i = 0, j = 0;
    for (i = 0; i < MAXLIGACAO; i++) {

        if (l->liga[i] != -1) {
            for (j = 0; j < MAXLIGACAO; j++) {
                if (e->salas[posSala(e, e->numSalas, l->liga[i])].liga[j] != -1) {
                    if (l->id == e->salas[posSala(e, e->numSalas, l->liga[i])].liga[j])
                        return 1;

                }
            }

        }
    }
    return -1;

}

int verificaEspaco(pespaco e) {
    int i = 0, j;

    for (i = 0; i < e->numSalas; i++) {
        if (verificaSala(&e->salas[i]) == -1) {
            warning("Erro dados incoerentes sala");
            return -1;
        }
        for (j = i + 1; j < e->numSalas; j++) {
            if (e->salas[i].id == e->salas[j].id){
                warning("Erro id de salas repetidos");
                return -1;
            }
                

        }

        if (verificaLigacoes(e, &e->salas[i], i) == -1) {
            warning("Erro ligacoes incorretas entre salas");
            return -1;
        }


    }
    return 1;
}

void libertaMEspaco(pespaco e){
    int i=0;
    if(e->salas!=NULL)
        free(e->salas); 

    
    for(i=0;i<e->numSalas;i++){
        libertaMPessoas(e->pessoas[i]);
    }
    
   
}


int salasLivres(pespaco espaco, int tam) {
    int i = 0;
    for (i = 0; i < tam; i++) {
        if (contaPessoas(espaco->pessoas[i]) < espaco->salas[i].capacidade)
            return 1;
    }
    return -1;
}

pespaco associaPessoasSala(pespaco e, ppessoa pp) {

    int i = 0, rand, tam = e->numSalas;
    
    ppessoa aux;
    e->pessoas=malloc(sizeof(ppessoa)*tam);
    for(i=0;i<tam;i++){
        e->pessoas[i]=NULL;
    }
   
    while (pp != NULL) {
        if (salasLivres(e, tam) == -1)
            break;

        rand = randomInt(0, tam - 1);
        if (contaPessoas(e->pessoas[rand]) < e->salas[rand].capacidade) {
            aux = malloc(sizeof (pessoa));
            if (aux == NULL) {
                free(e);
                libertaMEspaco(e);
                
                warning("problema com alocação de espaco para pessoa");
                return NULL;
            }
            *aux = *pp;
            aux->prox = e->pessoas[rand];
            e->pessoas[rand] = aux;
            pp = pp->prox;
        }
    }

    return e;

}

void imprimeReunioes(pespaco e) {
    int i = 0;
    printf("\n\n");
    for (i = 0; i < e->numSalas; i++) {

        printf("\n\t\t\tsala %d: %d pessoas", i + 1, contaPessoas(e->pessoas[i]));

        imprimePessoas(e->pessoas[i]);
        
    }



}


pespaco adcionaDoente(pespaco e) {
    int idSala, idade, diasI;
    char id[MAXNOME], i = 0;
    int tam=e->numSalas;

    printf("\n\n\n\n\n\n\n\t\t\t\tSala do doente:");
    scanf("%d", &idSala);
    printf("\n\t\t\t\tIdentificador do doente: ");
    fflush(stdin);
    scanf("%s", id);
    printf("\n\t\t\t\tIdade do doente: ");
    scanf("%d", &idade);
    printf("\n\t\t\t\tdias Infetado: ");
    scanf("%d", &diasI);

    if (idSala >= tam + 1 || idade >= 130 || idade < 0 || diasI < 0 || contaPessoas(e->pessoas[idSala - 1]) >= e->salas[idSala-1].capacidade) {
        warning("dados Invalidos");
        return e;
    }
    for (i = 0; i < tam; i++) {
        if (existeId(e->pessoas[i], id) == 1) {
            warning("dados Invalidos");
            return e;
        }
    }

    ppessoa novo;

    novo = malloc(sizeof (pessoa));
    if (novo == NULL)
        return e;
    novo->id = malloc(sizeof (char) * strlen(id));


    if (novo->id == NULL)
        return e;
    
    strcpy(novo->id, id);
    novo->idade = idade;
    novo->diasInfetado = diasI;
    novo->estado = 'D';
    novo->prox = NULL;


    novo->prox = e->pessoas[idSala - 1];
    e->pessoas[idSala - 1] = novo;

    return e;
}

pespaco move(pespaco e) {
    int num, id1 = 2, id2 = 3, pos;

    printf("\n\n\n\n\n\n\n\t\t\t\tNumero de pessoas:");
    scanf("%d", &num);
    printf("\n\t\t\t\tIdentificação da sala a tirar: ");
    scanf("%d", &id1);
    printf("\n\t\t\t\tIdentificação da sala a receber: ");
    scanf("%d", &id2);
    id1--;
    id2--;
    ppessoa atual, anterior = NULL;

    if (num > contaPessoas(e->pessoas[id1]))
        num = contaPessoas(e->pessoas[id1]);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    while (num > 0) {

        if ( contaPessoas(e->pessoas[id2]) + 1 >= e->salas[id2].capacidade)
            return e;


        pos = randomInt(0, contaPessoas(e->pessoas[id1]) - 1);

        if (pos == 0) {
            atual = e->pessoas[id1];
            e->pessoas[id1] = e->pessoas[id1]->prox;
            atual->prox = e->pessoas[id2];
            e->pessoas[id2] = atual;

        } else {
            atual = getPessoa(e->pessoas[id1], pos);
            anterior = getPessoa(e->pessoas[id1], pos - 1);
            anterior->prox = atual->prox;
            atual->prox = e->pessoas[id2];
            e->pessoas[id2] = atual;
        }
        printf("\n\t\t\t\t%s movido da sala %d para sala %d\n", atual->id, id1+1, id2+1);


        num--;
    }

    return e;


}

void guardaPessoas(pespaco e) {
    int i = 0, existemP = 0;
    
    ppessoa aux;
    FILE *ficheiro;


    for (i = 0; i < e->numSalas; i++) {
        if (contaPessoas(e->pessoas[i]) > 0)
            existemP = 1;
    }
    if (existemP != 1) {
        warning("não existem pessoas para guardar");
        return;
    }


    ficheiro = fopen("populacao.txt", "wt");
    if (ficheiro == NULL) {
        warning("não foi possivel guardar população");
        return;
    }


    for (i = 0; i < e->numSalas; i++) {
        aux = e->pessoas[i];

        while (aux != NULL) {
            fprintf(ficheiro, "%-20s %d %c %d\n", aux->id, aux->idade, aux->estado, aux->diasInfetado);
            aux=aux->prox;
        }
    }
    
    fclose(ficheiro);

}