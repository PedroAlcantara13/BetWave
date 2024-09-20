#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
    char nomeUsuario[50];
    char senha[20];
    char email[80];
    float saldo;
} Usuario;

extern Usuario usuarios[100];
extern int numeroUsuarios;

void carregarUsuarios();
void salvarUsuarios();
void cadastrarUsuario();
int logarUsuario();

#endif
