#ifndef APOSTA_USUARIO_H
#define APOSTA_USUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idUsuario;
    int idAposta;
    float valorApostado;
} ApostaUsuario;

extern ApostaUsuario apostasUsuarios[100];
extern int numeroApostasUsuarios;

void salvarApostasUsuarios();
void carregarApostasUsuarios();
void fazerAposta();
void verApostasEmAberto();

#endif // APOSTA_USUARIO_H
