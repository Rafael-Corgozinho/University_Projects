#ifndef LOCALIDADE_H
#define LOCALIDADE_H

typedef struct {
    char endereco[200];
    char cor[20];
    int custoCompra;
    int valorAluguel;
    int construcao; // 0 - sem construção, 1 - Casa, 2 - Hotel
    int idProprietario; 
} Localidade;

void inicializarLocalidade(Localidade *localidade, char endereco[], char cor[], int custoCompra, int valorAluguel);

#endif
