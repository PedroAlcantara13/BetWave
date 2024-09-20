#ifndef APOSTA_H
#define APOSTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMEROS 5

// Estruturas
typedef struct {
    char nomeUsuario[50];
    char senha[20];
    char email[80];
    float saldo;
} Usuario;

typedef struct {
    int id;
    char casa[15];
    char visitante[15];
    float oddCasa, oddVisitante, oddEmpate;
} Aposta;

typedef struct {
    int idUsuario;
    int idAposta;
    float valorApostado;
} ApostaUsuario;

typedef struct {
    int idUsuario;
    int idAposta;
    char casa[15];
    char visitante[15];
    float valorApostado;
    float valorGanho;
} ApostaUsuarioConcluida;

// Variáveis globais
extern Usuario usuarios[100];
extern int numeroUsuarios;
extern Aposta apostas[100];
extern int numeroApostas;
extern ApostaUsuario apostasUsuarios[100];
extern int numeroApostasUsuarios;
extern ApostaUsuarioConcluida apostasUsuariosConcluida[100];
extern int numeroApostasUsuariosConcluida;
extern int usuarioLogado;

// Funções
FILE* abrirArquivo(const char* nomeArquivo, const char* modo);
void salvarUsuarios();
void carregarUsuarios();
void salvarApostas();
void carregarApostas();
void salvarApostasUsuarios();
void carregarApostasUsuarios();
void salvarApostasUsuariosConcluida();
void carregarApostasUsuariosConcluida();
void cadastrarUsuario();
int logarUsuario();
void visualizarApostasDisponiveis();
void fazerAposta();
void verApostasEmAberto();
void verApostasConcluidas();
void adicionarJogo();
void definirResultadoJogo();
void listarUsuarios();
void menuPrincipal();

#endif
