#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição das variáveis globais
Usuario usuarios[100];
int numeroUsuarios = 0;
int usuarioLogado = -1;

// Função para abrir arquivo e tratar erro caso ocorra

// Função para salvar os usuários em um arquivo binário
void salvarUsuarios() {
    FILE* arquivo = abrirArquivo("usuarios.bin", "wb");
    fwrite(&numeroUsuarios, sizeof(int), 1, arquivo);
    fwrite(usuarios, sizeof(Usuario), numeroUsuarios, arquivo);
    fclose(arquivo);
}

// Função para carregar os usuários de um arquivo binário
void carregarUsuarios() {
    FILE* arquivo = fopen("usuarios.bin", "rb");
    if (arquivo != NULL) {
        fread(&numeroUsuarios, sizeof(int), 1, arquivo);
        fread(usuarios, sizeof(Usuario), numeroUsuarios, arquivo);
        fclose(arquivo);
    }
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    Usuario novoUsuario;
    char email[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", novoUsuario.nomeUsuario);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o email: ");
    scanf("%s", email);

    // Verificação básica de e-mail
    if (strchr(email, '@') == NULL) {
        printf("Email inválido.\n");
        return;
    }

    strcpy(novoUsuario.email, email);
    novoUsuario.saldo = 0.0;

    usuarios[numeroUsuarios] = novoUsuario;
    numeroUsuarios++;

    printf("Usuário cadastrado com sucesso!\n");
    salvarUsuarios();
}

// Função para autenticar um usuário
int logarUsuario() {
    char nomeUsuario[50], senha[20];

    printf("Digite o nome de usuário ou e-mail: ");
    scanf("%s", nomeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < numeroUsuarios; i++) {
        if ((strcmp(usuarios[i].nomeUsuario, nomeUsuario) == 0 || strcmp(usuarios[i].email, nomeUsuario) == 0) &&
            strcmp(usuarios[i].senha, senha) == 0) {
            usuarioLogado = i;
            printf("Login realizado com sucesso!\n");
            return 1;
        }
    }

    printf("Credenciais inválidas.\n");
    return 0;
}
