// TADjogo.c
#include "TADjogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PreencherJogo(Tabuleiro *tabuleiro, const char arq[]) {
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        // Processa cada linha do arquivo
        char endereco[200], cor[20];
        int custoCompra, valorAluguel;

        // Use o formato correto para a leitura dos dados
        if (sscanf(linha, "%199[^;];%19[^;];%d;%d", endereco, cor, &custoCompra, &valorAluguel) != 4) {
            fprintf(stderr, "Erro ao ler os dados da linha: %s", linha);
            continue; // Pula para a próxima linha em caso de erro
        }

        // Cria uma nova localidade e insere no tabuleiro
        Localidade localidade;
        inicializarLocalidade(&localidade, endereco, cor, custoCompra, valorAluguel);
        inserirLocalidade(tabuleiro, &localidade);
    }

    fclose(file);
}

void adicionar_jogador(Jogador *jogadores, const char arq[], int *num_jogadores) {
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char nome[256];
        int dinheiro, idJogador;

        // Use o formato correto para a leitura dos dados
        if (sscanf(linha, "%255[^;];%d;%d", nome, &dinheiro, &idJogador) != 3) {
            fprintf(stderr, "Erro ao ler os dados da linha: %s", linha);
            continue; // Pula para a próxima linha em caso de erro
        }

        // Inicializa o jogador
        inicializarJogador(&jogadores[*num_jogadores], nome, dinheiro, idJogador);
        (*num_jogadores)++;
    }

    fclose(file);
}

void inicializarJogador(Jogador *jogadorA, char nomeN[], int saldo, int id2) {
    strcpy(jogadorA->nome, nomeN);
    jogadorA->id = id2;
    jogadorA->saldo = saldo;
    for (int i = 0; i < MAX_PROPRIEDADES; i++) {
        jogadorA->propriedades[i] = NULL;
    }
    jogadorA->posicao= 0;
}

void imprimeJogador(const Jogador *jogadores, int num_jogadores) {
    for (int i = 0; i < num_jogadores; i++) {
        printf("Jogador %d:\n", i + 1);
        printf("Nome: %s\n", jogadores[i].nome);
        printf("Dinheiro: %d\n", jogadores[i].saldo); // Ajustado para %d para inteiros
        printf("ID: %d\n", jogadores[i].id);
        printf("\n");
    }
}

void TFalencia(Jogador *jogadorA) {
    if (jogadorA->saldo < 0) {
        jogadorA->saldo = 0;
        printf("Jogador %s faliu!\n", jogadorA->nome);
    }
}
int rola_dados() {
    int D1 = rand() % 6 + 1;
    int D2 = rand() % 6 + 1;
    return D1 + D2;
}

void MovimentoJogadores(Jogo* jogo, int Dados) {
    Jogador *jogador = &jogo->jogadores[jogo->jogadores->posicao];
    int posicaoAnterior = jogador->posicao;

    jogador->posicao = (jogador->posicao + Dados) % jogo->tabuleiro.numLocalidades;

    Apontador *novaLocalidade = jogo->tabuleiro.inicio;
    for (int i = 0; i < jogador->posicao; i++) {
        novaLocalidade = novaLocalidade->prox;
    }

    printf("%s se moveu de %d para %d - %s\n", jogador->nome, posicaoAnterior, jogador->posicao, novaLocalidade->localidade->endereco);

    if (novaLocalidade->localidade->idProprietario == -1) {
        comprarPropriedade(jogo, jogador, novaLocalidade->localidade);
    } else if (novaLocalidade->localidade->idProprietario != jogador->id) {
        PagamentoAluguel(jogo, jogador, novaLocalidade->localidade);
    }
}

void comprarPropriedade(Jogo *jogo, Jogador* jogador, Localidade* localidade) {
    if (jogador->saldo >= localidade->custoCompra) {
        jogador->saldo -= localidade->custoCompra;
        localidade->idProprietario = jogador->id;
        printf("%s comprou a propriedade %s por %d\n", jogador->nome, localidade->endereco, localidade->custoCompra);
    } else {
        printf("%s não tem dinheiro suficiente para comprar %s\n", jogador->nome, localidade->endereco);
    }
}

void PagamentoAluguel(Jogo *jogo, Jogador* jogador, Localidade* localidade) {
    // Check if the property has an owner
    if (localidade->idProprietario != -1) {
        Jogador *proprietario = NULL;
        
        // Find the owner player
        for (int i = 0; i < 100; i++) {
            if (jogo->jogadores[i].id == localidade->idProprietario) {
                proprietario = &jogo->jogadores[i];
                break;
            }
        }

        // Ensure the owner was found
        if (proprietario != NULL) {
            jogador->saldo -= localidade->valorAluguel;
            proprietario->saldo += localidade->valorAluguel;
            printf("%s pagou aluguel de %d para %s\n", jogador->nome, localidade->valorAluguel, proprietario->nome);
        } else {
            printf("Erro: Proprietário da localidade não encontrado!\n");
        }
    } else {
        printf("A propriedade %s não tem proprietário.\n", localidade->endereco);
    }
}