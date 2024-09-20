#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    char nomeUsuario[50];
    char senha[20];
    char email[80];
    float saldo;
} Usuario;

// Variáveis globais
extern Usuario usuarios[100];
extern int numeroUsuarios;
extern int usuarioLogado;

// Funções para manipulação dos usuários
void salvarUsuarios();
void carregarUsuarios();
void cadastrarUsuario();
int logarUsuario();

#endif
