#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#include "localidade.h"
#include "jogador.h"
#include "TADjogo.h"

int main() {
    Tabuleiro tabuleiro;
    Jogador jogadores[20];
    int numJogadores;

    // Inicializa o tabuleiro e os jogadores
    inicializarTabuleiro(&tabuleiro);
    inicializarJogadores(&jogadores, numJogadores);

    // Imprime o tabuleiro e os jogadores
    imprimirTabuleiro(&tabuleiro);
    imprimirJogadores(&jogadores, numJogadores);

    return 0;
}