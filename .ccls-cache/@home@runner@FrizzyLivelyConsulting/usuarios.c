#include "usuarios.h"
#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuario usuarios[100];
int numeroUsuarios = 0;

void salvarUsuarios() {
    FILE* arquivo = abrirArquivo("usuarios.bin", "wb");
    fwrite(&numeroUsuarios, sizeof(int), 1, arquivo);
    fwrite(usuarios, sizeof(Usuario), numeroUsuarios, arquivo);
    fclose(arquivo);
}

void carregarUsuarios() {
    FILE* arquivo = abrirArquivo("usuarios.bin", "rb");
    if (fread(&numeroUsuarios, sizeof(int), 1, arquivo) == 1) {
        fread(usuarios, sizeof(Usuario), numeroUsuarios, arquivo);
    }
    fclose(arquivo);
}

void cadastrarUsuario() {
    Usuario novoUsuario;
    char email[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", novoUsuario.nomeUsuario);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o email: ");
    scanf("%s", email);

    if (strchr(email, '@') == NULL) {
        printf("Email inválido.\n");
        return;
    }

    strcpy(novoUsuario.email, email);
    novoUsuario.saldo = 0.0;

    usuarios[numeroUsuarios++] = novoUsuario;

    printf("Usuário cadastrado com sucesso!\n");

    salvarUsuarios();
}

int logarUsuario() {
    char nomeUsuario[50], senha[20];

    printf("Digite o nome de usuário ou e-mail: ");
    scanf("%s", nomeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < numeroUsuarios; i++) {
        if ((strcmp(usuarios[i].nomeUsuario, nomeUsuario) == 0 || strcmp(usuarios[i].email, nomeUsuario) == 0) &&
            strcmp(usuarios[i].senha, senha) == 0) {
            return 1;
        }
    }

    printf("Credenciais inválidas.\n");
    return 0;
}
