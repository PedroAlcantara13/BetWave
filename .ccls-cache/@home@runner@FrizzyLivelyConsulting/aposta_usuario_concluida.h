#ifndef APOSTA_USUARIO_CONCLUIDA_H
#define APOSTA_USUARIO_CONCLUIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idUsuario;
    int idAposta;
    float valorApostado;
    char resultado[20];
} ApostaUsuarioConcluida;

extern ApostaUsuarioConcluida apostasUsuariosConcluidas[100];
extern int numeroApostasUsuariosConcluidas;

void salvarApostasUsuariosConcluida();
void carregarApostasUsuariosConcluida();
void definirResultadoApostas();

#endif // APOSTA_USUARIO_CONCLUIDA_H
