#include "aposta_usuario.h"
#include "usuario.h"
#include "aposta.h"

ApostaUsuario apostasUsuarios[100];
int numeroApostasUsuarios = 0;

void salvarApostasUsuarios() {
    FILE* arquivo = abrirArquivo("apostas_usuarios.bin", "wb");
    fwrite(&numeroApostasUsuarios, sizeof(int), 1, arquivo);
    fwrite(apostasUsuarios, sizeof(ApostaUsuario), numeroApostasUsuarios, arquivo);
    fclose(arquivo);
}

void carregarApostasUsuarios() {
    FILE* arquivo = abrirArquivo("apostas_usuarios.bin", "rb");
    if (fread(&numeroApostasUsuarios, sizeof(int), 1, arquivo) == 1) {
        fread(apostasUsuarios, sizeof(ApostaUsuario), numeroApostasUsuarios, arquivo);
    }
    fclose(arquivo);
}

void fazerAposta() {
    int idJogo, tipoAposta;
    float valorAposta;

    visualizarApostasDisponiveis();

    printf("Digite o ID do jogo em que deseja apostar: ");
    scanf("%d", &idJogo);

    Aposta* apostaSelecionada = NULL;
    for (int i = 0; i < numeroApostas; i++) {
        if (apostas[i].id == idJogo) {
            apostaSelecionada = &apostas[i];
            break;
        }
    }

    if (apostaSelecionada == NULL) {
        printf("Jogo não encontrado.\n");
        return;
    }

    printf("Digite o valor da aposta: ");
    scanf("%f", &valorAposta);
    printf("Escolha o tipo de aposta: 1 - Casa, 2 - Visitante, 3 - Empate: ");
    scanf("%d", &tipoAposta);

    ApostaUsuario novaAposta;
    novaAposta.idUsuario = usuarioLogado;
    novaAposta.idAposta = idJogo;
    novaAposta.valorApostado = valorAposta;

    apostasUsuarios[numeroApostasUsuarios] = novaAposta;
    numeroApostasUsuarios++;

    printf("Aposta registrada com sucesso!\n");

    salvarApostasUsuarios();
}

void verApostasEmAberto() {
    printf("Suas apostas:\n");
    for (int i = 0; i < numeroApostasUsuarios; i++) {
        if (apostasUsuarios[i].idUsuario == usuarioLogado) {
            printf("ID Aposta: %d\n", apostasUsuarios[i].idAposta);
            printf("Valor Apostado: %.2f\n", apostasUsuarios[i].valorApostado);
            printf("-------------------------\n");
        }
    }
}
