#include "menu.h"
#include "usuario.h"
#include "aposta.h"
#include "aposta_usuario.h"
#include "aposta_usuario_concluida.h"

void menuLogin() {
    printf("1. Cadastrar\n");
    printf("2. Logar\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

void menuPrincipal() {
    int opcao;
    while (1) {
        printf("1. Fazer aposta\n");
        printf("2. Ver apostas em aberto\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            fazerAposta();
        } else if (opcao == 2) {
            verApostasEmAberto();
        } else if (opcao == 3) {
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }
}

void menuADM() {
    int opcao;
    while (1) {
        printf("1. Adicionar jogo\n");
        printf("2. Definir resultado\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            adicionarJogo();
        } else if (opcao == 2) {
            definirResultadoApostas();
        } else if (opcao == 3) {
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }
}
