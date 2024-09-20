#include "aposta.h"

Usuario usuarios[100];
int numeroUsuarios = 0;

Aposta apostas[100];
int numeroApostas = 0;

ApostaUsuario apostasUsuarios[100];
int numeroApostasUsuarios = 0;

ApostaUsuarioConcluida apostasUsuariosConcluida[100];
int numeroApostasUsuariosConcluida = 0;

int usuarioLogado = -1;

FILE* abrirArquivo(const char* nomeArquivo, const char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    return arquivo;
}

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

void salvarApostas() {
    FILE* arquivo = abrirArquivo("apostas.bin", "wb");
    fwrite(&numeroApostas, sizeof(int), 1, arquivo);
    fwrite(apostas, sizeof(Aposta), numeroApostas, arquivo);
    fclose(arquivo);
}

void carregarApostas() {
    FILE* arquivo = abrirArquivo("apostas.bin", "rb");
    if (fread(&numeroApostas, sizeof(int), 1, arquivo) == 1) {
        fread(apostas, sizeof(Aposta), numeroApostas, arquivo);
    }
    fclose(arquivo);
}

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

void salvarApostasUsuariosConcluida() {
    FILE* arquivo = abrirArquivo("apostas_usuarios_concluidas.bin", "wb");
    fwrite(&numeroApostasUsuariosConcluida, sizeof(int), 1, arquivo);
    fwrite(apostasUsuariosConcluida, sizeof(ApostaUsuarioConcluida), numeroApostasUsuariosConcluida, arquivo);
    fclose(arquivo);
}

void carregarApostasUsuariosConcluida() {
    FILE* arquivo = abrirArquivo("apostas_usuarios_concluidas.bin", "rb");
    if (fread(&numeroApostasUsuariosConcluida, sizeof(int), 1, arquivo) == 1) {
        fread(apostasUsuariosConcluida, sizeof(ApostaUsuarioConcluida), numeroApostasUsuariosConcluida, arquivo);
    }
    fclose(arquivo);
}

void cadastrarUsuario() {
    Usuario novoUsuario;
    printf("Nome de usuário: ");
    scanf("%s", novoUsuario.nomeUsuario);
    printf("Senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Email: ");
    scanf("%s", novoUsuario.email);
    novoUsuario.saldo = 100.0;  // Saldo inicial
    usuarios[numeroUsuarios++] = novoUsuario;
    salvarUsuarios();
    printf("Usuário cadastrado com sucesso!\n");
}

int logarUsuario() {
    char nome[50], senha[20];
    printf("Nome de usuário: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < numeroUsuarios; i++) {
        if (strcmp(usuarios[i].nomeUsuario, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            usuarioLogado = i;
            printf("Login realizado com sucesso!\n");
            return 1;
        }
    }
    printf("Usuário ou senha incorretos.\n");
    return 0;
}

void visualizarApostasDisponiveis() {
    printf("Apostas disponíveis:\n");
    for (int i = 0; i < numeroApostas; i++) {
        printf("ID: %d, %s vs %s - Odd Casa: %.2f, Odd Visitante: %.2f, Odd Empate: %.2f\n", 
               apostas[i].id, apostas[i].casa, apostas[i].visitante, 
               apostas[i].oddCasa, apostas[i].oddVisitante, apostas[i].oddEmpate);
    }
}

void fazerAposta() {
    int idAposta;
    float valor;

    visualizarApostasDisponiveis();
    printf("Digite o ID da aposta que deseja fazer: ");
    scanf("%d", &idAposta);

    printf("Digite o valor da aposta: ");
    scanf("%f", &valor);

    if (valor > usuarios[usuarioLogado].saldo) {
        printf("Saldo insuficiente.\n");
        return;
    }

    usuarios[usuarioLogado].saldo -= valor;
    salvarUsuarios();

    ApostaUsuario novaApostaUsuario = {usuarioLogado, idAposta, valor};
    apostasUsuarios[numeroApostasUsuarios++] = novaApostaUsuario;
    salvarApostasUsuarios();

    printf("Aposta realizada com sucesso!\n");
}

void verApostasEmAberto() {
    printf("Apostas em aberto:\n");
    for (int i = 0; i < numeroApostasUsuarios; i++) {
        if (apostasUsuarios[i].idUsuario == usuarioLogado) {
            Aposta a = apostas[apostasUsuarios[i].idAposta];
            printf("ID: %d, %s vs %s, Valor apostado: %.2f\n", 
                   apostasUsuarios[i].idAposta, a.casa, a.visitante, apostasUsuarios[i].valorApostado);
        }
    }
}

void verApostasConcluidas() {
    printf("Apostas concluídas:\n");
    for (int i = 0; i < numeroApostasUsuariosConcluida; i++) {
        if (apostasUsuariosConcluida[i].idUsuario == usuarioLogado) {
            printf("Jogo: %s vs %s, Valor apostado: %.2f, Valor ganho: %.2f\n", 
                   apostasUsuariosConcluida[i].casa, apostasUsuariosConcluida[i].visitante, 
                   apostasUsuariosConcluida[i].valorApostado, apostasUsuariosConcluida[i].valorGanho);
        }
    }
}

void adicionarJogo() {
    Aposta novaAposta;
    novaAposta.id = numeroApostas;

    printf("Time da casa: ");
    scanf("%s", novaAposta.casa);
    printf("Time visitante: ");
    scanf("%s", novaAposta.visitante);
    printf("Odd Casa: ");
    scanf("%f", &novaAposta.oddCasa);
    printf("Odd Visitante: ");
    scanf("%f", &novaAposta.oddVisitante);
    printf("Odd Empate: ");
    scanf("%f", &novaAposta.oddEmpate);

    apostas[numeroApostas++] = novaAposta;
    salvarApostas();
    printf("Jogo adicionado com sucesso!\n");
}

void definirResultadoJogo() {
    int idAposta, resultado;

    printf("Digite o ID do jogo para definir o resultado: ");
    scanf("%d", &idAposta);

    printf("Resultado do jogo (1 = Casa, 2 = Visitante, 3 = Empate): ");
    scanf("%d", &resultado);

    for (int i = 0; i < numeroApostasUsuarios; i++) {
        if (apostasUsuarios[i].idAposta == idAposta) {
            float odd = 0.0;
            if (resultado == 1) odd = apostas[idAposta].oddCasa;
            else if (resultado == 2) odd = apostas[idAposta].oddVisitante;
            else if (resultado == 3) odd = apostas[idAposta].oddEmpate;

            float ganho = apostasUsuarios[i].valorApostado * odd;

            ApostaUsuarioConcluida apostaConcluida = {
                apostasUsuarios[i].idUsuario,
                apostasUsuarios[i].idAposta,
                apostas[idAposta].casa,
                apostas[idAposta].visitante,
                apostasUsuarios[i].valorApostado,
                ganho
            };

            usuarios[apostasUsuarios[i].idUsuario].saldo += ganho;
            salvarUsuarios();

            apostasUsuariosConcluida[numeroApostasUsuariosConcluida++] = apostaConcluida;
            salvarApostasUsuariosConcluida();
        }
    }

    printf("Resultado definido e apostas concluídas!\n");
}

void listarUsuarios() {
    printf("Usuários cadastrados:\n");
    for (int i = 0; i < numeroUsuarios; i++) {
        printf("Nome: %s, Email: %s, Saldo: %.2f\n", 
               usuarios[i].nomeUsuario, usuarios[i].email, usuarios[i].saldo);
    }
}

void menuPrincipal() {
    int opcao;

    do {
        printf("1. Cadastrar usuário\n");
        printf("2. Fazer login\n");
        printf("3. Visualizar apostas\n");
        printf("4. Fazer aposta\n");
        printf("5. Ver apostas em aberto\n");
        printf("6. Ver apostas concluídas\n");
        printf("7. Adicionar jogo (admin)\n");
        printf("8. Definir resultado do jogo (admin)\n");
        printf("9. Listar usuários (admin)\n");
        printf("0. Sair\n");

        scanf("%d", &opcao);
        switch(opcao) {
            case 1: cadastrarUsuario(); break;
            case 2: logarUsuario(); break;
            case 3: visualizarApostasDisponiveis(); break;
            case 4: fazerAposta(); break;
            case 5: verApostasEmAberto(); break;
            case 6: verApostasConcluidas(); break;
            case 7: adicionarJogo(); break;
            case 8: definirResultadoJogo(); break;
            case 9: listarUsuarios(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n"); break;
        }
    } while(opcao != 0);
}
