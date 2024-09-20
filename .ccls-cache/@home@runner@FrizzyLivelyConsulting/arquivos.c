#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>

FILE* abrirArquivo(const char* nomeArquivo, const char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    return arquivo;
}
