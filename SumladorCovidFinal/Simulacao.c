/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"simulacao.h"

pSimulacao fase1(pSimulacao simulacao) {
    pespaco pEspaco = &simulacao->espaco;
    ppessoa listaPessoa = NULL;
    char nomeFich[MAXNOME];


    initRandom();

    //ler ficheiro binario com espaços
    /*
        printf("\n\t\tintroduza nome do ficheiro com o espaço: ");
        scanf("%s", nomeFich);
     */
    leFichEspaco("E1.bin", pEspaco);

    imprimeEspaco(pEspaco);
    //validar conteudo recebido
    if (verificaEspaco(pEspaco) == -1) {
        libertaMEspaco(pEspaco);
        Abort("Espaco com campos invalidos\n\n");
    } else {
        printf("\t\t\t\tEspaco validado com Sucesso");
    }


    //ler ficheiro de texto com pessoa
    /*
        printf("\n\n\t\tintroduza nome do ficheiro com as pessoas: ");
        scanf("%s", nomeFich);
     */


    listaPessoa = leFichPessoa("pessoasB.txt");

    if (listaPessoa == NULL) {
        libertaMEspaco(pEspaco);
        Abort("Não e possivel ler ficheiro com pessoas");
    }

    imprimePessoas(listaPessoa);


    //validar conteudo recebido
    if (verificaPessoas(listaPessoa) == -1) {
        libertaMEspaco(pEspaco);
        Abort("Pessoas com campos invalidos\n\n");
    } else {
        printf("\t\t\t\tPessoas validadas com sucesso\n\n\n");
    }



    pEspaco = associaPessoasSala(pEspaco, listaPessoa);

    simulacao->espaco = *pEspaco;

    imprimeReunioes(pEspaco);
    getEnter();
    return simulacao;
}

void resetDados(pSimulacao simulacao) {

    simulacao->dados.dias = 0;
    simulacao->dados.numDoentes = 0;
    simulacao->dados.numImundes = 0;
    simulacao->dados.numImunesDia = NULL;
    simulacao->dados.numInfetadosDia = NULL;
    simulacao->dados.numRecuperadosDia = NULL;
    simulacao->dados.numSaudaveis = 0;
    simulacao->dados.populacao = 0;

}

int menuPrincipal() {
    printf("\n\n\n\n\n");
    int opt;
    printf("\t\t\t\t_______________SELECIONE UMA OPERÇÃO_______________\n\n");
    printf("\t\t\t\t1- Avançar 1 iteração na simulação\n");
    printf("\t\t\t\t2- Apresentar estatística\n");
    printf("\t\t\t\t3- Apresentar Salas\n");
    printf("\t\t\t\t4- Adicionar doente:\n");
    printf("\t\t\t\t5- Transferir pessoas\n");
    printf("\t\t\t\t6- Desfazer iteração\n\n");
    printf("\t\t\t\t7- Terminar Simulação\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t");
    scanf("%d", &opt);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return opt;

}

pSimulacao libertaMsimulacao(pSimulacao simulacao) {
    if (simulacao == NULL) {
        return NULL;
    }
    libertaMEspaco(&simulacao->espaco);

    if (simulacao->dados.numImunesDia != NULL)
        free(simulacao->dados.numImunesDia);


    if (simulacao->dados.numInfetadosDia != NULL)
        free(simulacao->dados.numInfetadosDia);


    if (simulacao->dados.numRecuperadosDia != NULL)
        free(simulacao->dados.numRecuperadosDia);



    return simulacao;
}

void proximaIteracao(pSimulacao simulacao) {


    printf("\n INICIO ITERACAO\n");

    int numAInfetar; //numero pessoas a infetar
    int i = 0, j = 0, z = 0;

    printf("iniciou alocação diaria\n");
    simulacao->dados.numInfetadosDia = acrescentaAArray(simulacao->dados.numInfetadosDia, (simulacao->dados.dias + 1));
    printf("iniciou alocação diaria\n");
    simulacao->dados.numRecuperadosDia = acrescentaAArray(simulacao->dados.numRecuperadosDia, (simulacao->dados.dias + 1));
    printf("iniciou alocação diaria\n");
    simulacao->dados.numImunesDia = acrescentaAArray(simulacao->dados.numImunesDia, (simulacao->dados.dias + 1));
    printf("terminou alocação diaria\n");


    if (simulacao->dados.numInfetadosDia == NULL || simulacao->dados.numRecuperadosDia == NULL || simulacao->dados.numImunesDia == NULL) {
        libertaMsimulacao(simulacao);
        Abort("não é possivel fazer analise diaria");
    }
    *(simulacao->dados.numInfetadosDia + (simulacao->dados.dias)) = 0;
    *(simulacao->dados.numRecuperadosDia + (simulacao->dados.dias)) = 0;
    *(simulacao->dados.numImunesDia + (simulacao->dados.dias)) = 0;

    printf("\t\t\t_______________ACONTECIMENTOS DO DIA_______________\n\n");

    for (i = 0; i < simulacao->espaco.numSalas; i++) {

        int totalPessoas = contaPessoas(simulacao->espaco.pessoas[i]);
        char proxEstado[totalPessoas];
        memset(proxEstado, 'N', sizeof (proxEstado));


        numAInfetar = (int) totalPessoas * TDISSEMINACAO;

        //ciclo para descubrir proximo estado de cada pessoa
        for (z = 0; z < totalPessoas; z++) {
            ppessoa pessoaAtual = getPessoa(simulacao->espaco.pessoas[i], z);

            if (pessoaAtual->estado == 'D') {
                if (numAInfetar > 0) {
                    int posInfetado[numAInfetar];
                    //obter posicoes diferentes

                    do {
                        for (j = 0; j < numAInfetar; j++) {
                            posInfetado[j] = randomInt(0, totalPessoas - 1);
                        }
                    } while (contemIguais(posInfetado, numAInfetar) == 1 || posInfetado[0] == z);

                    //pessoas a contaminar
                    for (j = 0; j < numAInfetar; j++) {
                        if (getPessoa(simulacao->espaco.pessoas[i], posInfetado[j])->estado == 'S')
                            proxEstado[posInfetado[j]] = 'C'; //c de contamindao

                    }
                }
                if (probEvento(1 / (float) pessoaAtual->idade) != 0 || pessoaAtual->diasInfetado >= diasMax(pessoaAtual->idade)) {

                    //pessoas a tornar imunes
                    if (probEvento(TAXAIMUNIDADE) != 0) {
                        proxEstado[z] = 'I';
                    } else {//pessoas a recuperar
                        proxEstado[z] = 'R';
                    }
                }
            }
        }



        printf("\t\t\t\tsala %d\n", i);


        //ciclo para aplicar proximo estado a cada pessoa
        for (z = 0; z < totalPessoas; z++) {
            ppessoa pessoaAtual = getPessoa(simulacao->espaco.pessoas[i], z);

            switch (proxEstado[z]) {
                case 'C':
                    (*(simulacao->dados.numInfetadosDia + (simulacao->dados.dias)))++;
                    printf("\t\t\t\t\t%s foi contamindo\n", pessoaAtual->id);
                    setEstado(pessoaAtual, 'D');
                    break;
                case 'R':
                    (*(simulacao->dados.numRecuperadosDia + (simulacao->dados.dias)))++;
                    printf("\t\t\t\t\t%s recuperou\n", pessoaAtual->id);
                    setEstado(pessoaAtual, 'S');
                    break;
                case 'I':
                    (*(simulacao->dados.numImunesDia + (simulacao->dados.dias)))++;
                    printf("\t\t\t\t\t%s tornou-se imune\n", pessoaAtual->id);
                    setEstado(pessoaAtual, 'I');
                    break;
                default:
                    if (pessoaAtual->estado == 'D') {
                        pessoaAtual->diasInfetado++;
                    }
                    break;
            }


        }

    }

    simulacao->dados.dias++;
    printf("\n FIM ITERACAO\n");

}

void atualizaEstatistica(pSimulacao simulacao) {
    int i = 0;

    simulacao->dados.numDoentes = 0;
    simulacao->dados.numImundes = 0;
    simulacao->dados.numSaudaveis = 0;
    simulacao->dados.populacao = 0;


    for (i = 0; i < simulacao->espaco.numSalas; i++) {
        getDados(simulacao->espaco.pessoas[i], &simulacao->dados.numDoentes, &simulacao->dados.numSaudaveis, &simulacao->dados.numImundes, &simulacao->dados.populacao);
    }

}

void apresentaEstatistica(dados dados) {


    int numD = dados.numDoentes;
    int numS = dados.numSaudaveis;
    int numI = dados.numImundes;
    int totalP = dados.populacao;
    int *a = dados.numInfetadosDia;
    int *b = dados.numRecuperadosDia;
    int *c = dados.numImunesDia;
    int num = dados.dias;
    printf("numero dias=%d\n", num);
    int i = 0, j = 0;

    printf("\n\n\n\t\tESTATISTICA\n\n");
    printf("\t\t\tNumero total de Pessoas:%d\n", (totalP));
    printf("\t\t\tNumero de Doentes:%d   -> %.1f%% da população\n", numD, numD * 100 / (float) totalP);
    printf("\t\t\tNumero de Saudaveis:%d -> %.1f%% da população\n", numS, numS * 100 / (float) totalP);
    printf("\t\t\tNumero de Imunes:%d    -> %.f%% da população\n", numI, numI * 100 / (float) totalP);



    if (num <= 0)
        return;


    printf("\n\t\t\tResumo DIA %d\n", num);
    printf("\t\t\t\tnumero infetados: %d", a[num - 1]);

    printf("\n\t\t\t\tnumero Recuperados: %d", b[num - 1]);

    printf("\n\t\t\t\tnumero Imunes do dia : %d\n\n", c[num - 1]);
    for (i = 0; i < num; i++) {


        printf("\n\t\t\t\tD ");
        for (j = 0; j < a[i]; j++) {
            printf("________");
        }
        printf("\n\t\t\tDia %d   R ", i);
        for (j = 0; j < b[i]; j++) {
            printf("________");
        }
        printf("\n\t\t\t\tI ");
        for (j = 0; j < c[i]; j++) {
            printf("________");
        }


    }
    printf("\n\t\t\t\t  0       1       2       3       4       5       6");

}

void guardaRelatorio(dados dados) {
    int i = 0;
    FILE* ficheiro;
    ficheiro = fopen("report.txt", "wt");
    fprintf(ficheiro, "DimensaoPopulacao %d\n", dados.populacao);
    fprintf(ficheiro, "NumeroDoentes %d\n", dados.numDoentes);
    fprintf(ficheiro, "NumeroSaudaveis %d\n", dados.numSaudaveis);
    fprintf(ficheiro, "NumeroImunes %d\n", dados.numImundes);


    for (i = 0; i < dados.dias; i++) {

        fprintf(ficheiro, "Dia %d\n", i + 1);
        fprintf(ficheiro, "numeroInfetadosDiario %d\n", dados.numInfetadosDia[i]);
        fprintf(ficheiro, "numeroRecuperadosDiario %d\n", dados.numRecuperadosDia[i]);
        fprintf(ficheiro, "numeroImunesDiario %d\n", dados.numImunesDia[i]);
    }

    fclose(ficheiro);



}

pSimulacao copiaSimulacao(pSimulacao simula) {

    ppessoa iteradorP, novoPessoa;
    pSimulacao copia, iteradorAux;
 int i = 0, conta = 0;
    

    copia = malloc(sizeof (simulacao));
    if (copia == NULL) {
        Abort("ERRO COPIA");
    }
    copia->anterior = NULL;

    if (simula->dados.dias != 0) {
        copia->dados.numImunesDia = malloc(sizeof (int)*(simula->dados.dias));
        copia->dados.numInfetadosDia = malloc(sizeof (int)*(simula->dados.dias));
        copia->dados.numRecuperadosDia = malloc(sizeof (int)*(simula->dados.dias));

        if (copia->dados.numImunesDia == NULL || copia->dados.numInfetadosDia == NULL || copia->dados.numRecuperadosDia == NULL)
            Abort("malloc copia->numeros diarios");
    }

    copia->espaco.salas = malloc(sizeof (local) * simula->espaco.numSalas);
    if (copia->espaco.salas == NULL)
        Abort("malloc copia->salas");

    copia->espaco.pessoas = malloc(sizeof (ppessoa)*(simula->espaco.numSalas));
    if (copia->espaco.salas == NULL)
        Abort("malloc copia->vetor de ponteiro pessoas");

    for (i = 0; i < simula->espaco.numSalas; i++) {
        copia->espaco.pessoas[i] = NULL;
    }

    for (i = 0; i < simula->espaco.numSalas; i++) {
        iteradorP = simula->espaco.pessoas[i];
        while (iteradorP != NULL) {
            novoPessoa = malloc(sizeof (pessoa));
            if (novoPessoa == NULL)
                Abort("malloc copia->pessoa");
            *novoPessoa = *iteradorP;

            novoPessoa->prox = copia->espaco.pessoas[i];
            copia->espaco.pessoas[i] = novoPessoa;
            iteradorP=iteradorP->prox;
        }
    }

     for (i = 0; i < simula->espaco.numSalas; i++) {
        copia->espaco.salas[i]= simula->espaco.salas[i];
    }

    for(i=0;i<simula->dados.dias;i++){
        copia->dados.numImunesDia[i]=simula->dados.numImunesDia[i];
        copia->dados.numInfetadosDia[i]=simula->dados.numInfetadosDia[i];
        copia->dados.numRecuperadosDia[i]=simula->dados.numRecuperadosDia[i];
    }
    

    //copia dados
    copia->dados.dias = simula->dados.dias;
    copia->dados.numDoentes = simula->dados.numDoentes;
    copia->dados.numImundes = simula->dados.numImundes;
    copia->dados.numSaudaveis = simula->dados.numSaudaveis;
    copia->dados.populacao = simula->dados.populacao;


    //copia espaco
    copia->espaco.numSalas = simula->espaco.numSalas;
    

     if (simula->anterior == NULL) {
        copia->anterior = NULL;
        simula->anterior = copia;
    } else {
        copia->anterior = simula->anterior;
        simula->anterior = copia;
    }
    

    
    iteradorAux=simula;
    
    while(iteradorAux!=NULL){
        iteradorAux=iteradorAux->anterior;
        conta++;
    }

    iteradorAux=simula;
     pSimulacao iteradorAux2;
    if(conta>4){
        while(iteradorAux->anterior!=NULL){
            iteradorAux2 = iteradorAux;
            iteradorAux=iteradorAux->anterior;
        }
        iteradorAux=libertaMsimulacao(iteradorAux);
        free(iteradorAux);
        iteradorAux2->anterior =NULL;
    }
    
    return simula;
    
    
}

void fase2(pSimulacao simulacao) {
    int fim = 0;
    pespaco pespaco = &simulacao->espaco;
    resetDados(simulacao);

    simulacao->anterior = NULL;




    while (fim == 0) {

        switch (menuPrincipal()) {
            case 1:
                simulacao = copiaSimulacao(simulacao);
                proximaIteracao(simulacao);
                atualizaEstatistica(simulacao);
                getEnter();
                break;

            case 2:
                atualizaEstatistica(simulacao);
                apresentaEstatistica(simulacao->dados);
                getEnter();
                break;

            case 3:
                imprimeReunioes(pespaco);
                getEnter();
                break;
            case 4:
                pespaco = adcionaDoente(pespaco);
                break;
            case 5:
                pespaco = move(pespaco);
                getEnter();
                break;
            case 6:
                if (simulacao->anterior != NULL)
                    simulacao = simulacao->anterior;
                break;
            case 7:
                printf("\n\n\n\n\n\n\n\n\t\t\t\t");
                atualizaEstatistica(simulacao);
                guardaRelatorio(simulacao->dados);
                guardaPessoas(pespaco);
                fim = 1;
                break;

        }
    }



    libertaMsimulacao(simulacao);

}
