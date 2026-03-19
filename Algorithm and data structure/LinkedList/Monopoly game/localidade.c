#include "localidade.h"
#include <string.h>

void inicializarLocalidade(Localidade *localidade, char endereco[], char cor[], int custoCompra, int valorAluguel) {
    strcpy(localidade->endereco, endereco);
    strcpy(localidade->cor, cor);
    localidade->custoCompra = custoCompra;
    localidade->valorAluguel = valorAluguel;
    localidade->idProprietario = -1; // Initialize with NO_OWNER
}