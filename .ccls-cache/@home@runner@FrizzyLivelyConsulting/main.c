#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bingo.h"


// Definição das estruturas
typedef struct {
    char nomeUsuario[50];
    char senha[20];
    char email[80];
    float saldo; // Adicionando saldo para cada usuário
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

// Definição de variáveis globais
Usuario usuarios[100];
int numeroUsuarios = 0;

Aposta apostas[100];
int numeroApostas = 0;

ApostaUsuario apostasUsuarios[100];
int numeroApostasUsuarios = 0;

ApostaUsuarioConcluida apostasUsuariosConcluida[100];
int numeroApostasUsuariosConcluida = 0;

int usuarioLogado = -1; // Índice do usuário logado

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
    char email[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", novoUsuario.nomeUsuario);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o email: ");
    scanf("%s", email);

    // Validação básica do email (exemplo)
    if (strchr(email, '@') == NULL) {
        printf("Email inválido.\n");
        return;
    }

    strcpy(novoUsuario.email, email);
    novoUsuario.saldo = 0.0; // Inicializa o saldo do novo usuário

    usuarios[numeroUsuarios] = novoUsuario;
    numeroUsuarios++;

    printf("Usuário cadastrado com sucesso!\n");

    salvarUsuarios(); // Salva as alterações
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
            usuarioLogado = i; // Define o índice do usuário logado
            return 1; // Usuário encontrado
        }
    }

    printf("Credenciais inválidas.\n");
    return 0; // Falha no login
}

void visualizarApostasDisponiveis() {
    printf("Jogos disponíveis:\n");
    for (int i = 0; i < numeroApostas; i++) {
        printf("ID: %d\n", apostas[i].id);
        printf("Time da Casa: %s\n", apostas[i].casa);
        printf("Time Visitante: %s\n", apostas[i].visitante);
        printf("Odd Casa: %.2f\n", apostas[i].oddCasa);
        printf("Odd Visitante: %.2f\n", apostas[i].oddVisitante);
        printf("Odd Empate: %.2f\n", apostas[i].oddEmpate);
        printf("-------------------------\n");
    }
}

void fazerAposta() {
    int idJogo, tipoAposta;
    float valorAposta;

    visualizarApostasDisponiveis();

    printf("Digite o ID do jogo em que deseja apostar: ");
    scanf("%d", &idJogo);

    // Verifica se o jogo existe
    Aposta* aposta = NULL;
    for (int i = 0; i < numeroApostas; i++) {
        if (apostas[i].id == idJogo) {
            aposta = &apostas[i];
            break;
        }
    }

    if (aposta == NULL) {
        printf("Jogo não encontrado.\n");
        return;
    }

    printf("Escolha o tipo de aposta:\n");
    printf("1. Casa\n");
    printf("2. Visitante\n");
    printf("3. Empate\n");
    printf("Escolha uma opção: ");
    scanf("%d", &tipoAposta);

    if (tipoAposta < 1 || tipoAposta > 3) {
        printf("Tipo de aposta inválido.\n");
        return;
    }

    printf("Digite o valor da aposta: R$");
    scanf("%f", &valorAposta);

    if (valorAposta <= 0 || valorAposta > usuarios[usuarioLogado].saldo) {
        printf("Valor da aposta inválido ou saldo insuficiente.\n");
        return;
    }

    // Registra a aposta
    ApostaUsuario novaAposta;
    novaAposta.idUsuario = usuarioLogado;
    novaAposta.idAposta = idJogo;
    novaAposta.valorApostado = valorAposta;

    apostasUsuarios[numeroApostasUsuarios++] = novaAposta;
    usuarios[usuarioLogado].saldo -= valorAposta;

    printf("Aposta realizada com sucesso!\n");

    salvarApostasUsuarios(); // Salva as alterações
    salvarUsuarios(); // Salva o saldo atualizado
}

void verApostasEmAberto() {
    printf("Apostas em aberto:\n");
    for (int i = 0; i < numeroApostasUsuarios; i++) {
        if (apostasUsuarios[i].idUsuario == usuarioLogado) {
            // Encontra a aposta correspondente
            Aposta* aposta = NULL;
            for (int j = 0; j < numeroApostas; j++) {
                if (apostas[j].id == apostasUsuarios[i].idAposta) {
                    aposta = &apostas[j];
                    break;
                }
            }

            if (aposta != NULL) {
                float retorno = 0.0;
                // Calcula o retorno baseado no tipo de aposta
                printf("ID Aposta: %d\n", apostasUsuarios[i].idAposta);
                printf("Time da Casa: %s\n", aposta->casa);
                printf("Time Visitante: %s\n", aposta->visitante);
                printf("Odd Casa: %.2f\n", aposta->oddCasa);
                printf("Odd Visitante: %.2f\n", aposta->oddVisitante);
                printf("Odd Empate: %.2f\n", aposta->oddEmpate);
                printf("Valor Apostado: R$%.2f\n", apostasUsuarios[i].valorApostado);

                // Aqui assumimos que o tipo de aposta foi registrado na estrutura
                // e usa um valor fixo para este exemplo. Substitua pela lógica real.
                int tipoAposta = 1; // Tipo de aposta: 1 - Casa, 2 - Visitante, 3 - Empate
                if (tipoAposta == 1) {
                    retorno = apostasUsuarios[i].valorApostado * aposta->oddCasa;
                } else if (tipoAposta == 2) {
                    retorno = apostasUsuarios[i].valorApostado * aposta->oddVisitante;
                } else if (tipoAposta == 3) {
                    retorno = apostasUsuarios[i].valorApostado * aposta->oddEmpate;
                }

                printf("Possível Retorno: R$%.2f\n", retorno);
                printf("-------------------------\n");
            }
        }
    }
}

void verApostasConcluidas() {
    printf("Apostas concluídas:\n");
    int encontrado = 0;
    for (int i = 0; i < numeroApostasUsuariosConcluida; i++) {
        if (apostasUsuariosConcluida[i].idUsuario == usuarioLogado) {
            // Encontra a aposta correspondente
            Aposta* aposta = NULL;
            for (int j = 0; j < numeroApostas; j++) {
                if (apostas[j].id == apostasUsuariosConcluida[i].idAposta) {
                    aposta = &apostas[j];
                    break;
                }
            }

            if (aposta != NULL) {
                printf("ID Aposta: %d\n", apostasUsuariosConcluida[i].idAposta);
                printf("Valor Apostado: R$%.2f\n", apostasUsuariosConcluida[i].valorApostado);
                printf("Valor Ganhado: R$%.2f\n", apostasUsuariosConcluida[i].valorGanho);
                printf("-------------------------\n");
                encontrado = 1;
            }
        }
    }

    if (!encontrado) {
        printf("Você não tem apostas concluídas.\n");
    }
}


void menuPrincipal() {
    int opcao;
    float valor, valorB;
    int sorteados[NUMEROS], escolhidos[NUMEROS];
    int acertos;
    float pontos;
    float ganhou;
    printf("\nMenu Principal do Cliente\n");
    printf("1. Ver jogos disponíveis para Aposta\n");
    printf("2. Ver minhas apostas em Aberto\n");
    printf("3. Ver minhas apostas Concluídas\n");
    printf("4. Ver meu saldo\n");
    printf("5. Depositar R$\n");
    printf("6. Sacar R$\n");
    printf("7. LOTERIA\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            fazerAposta();
            break;
        case 2:
            verApostasEmAberto();
            break;
        case 3:
            verApostasConcluidas();
            break;
        case 4:
            // Mostrar saldo do usuário logado
            printf("Seu saldo é: R$%.2f\n", usuarios[usuarioLogado].saldo);
            break;
        case 5:
            printf("Digite o valor a ser depositado: R$");
            scanf("%f", &valor);
            if (valor > 0) {
                usuarios[usuarioLogado].saldo += valor;
                printf("Depósito de R$%.2f realizado com sucesso!\n", valor);
                salvarUsuarios(); // Salva as alterações
            } else {
                printf("Valor inválido.\n");
            }
            break;
        case 6:
            printf("Digite o valor a ser sacado: R$");
            scanf("%f", &valor);
            if (valor > 0 && valor <= usuarios[usuarioLogado].saldo) {
                usuarios[usuarioLogado].saldo -= valor;
                printf("Saque de R$%.2f realizado com sucesso!\n", valor);
                salvarUsuarios(); // Salva as alterações
            } else {
                printf("Valor inválido ou saldo insuficiente.\n");
            }
            break;
        case 7:
            // Inicializando o gerador de números aleatórios
            srand(time(NULL));

            // Gerando os números aleatórios entre 1 e 60
            for (int i = 0; i < NUMEROS; i++) {
                sorteados[i] = (rand() % 60) + 1;
            }
            printf("Digite o valor a ser Apostado: R$");
            scanf("%f", &valorB);
            if (valorB > 0 && valorB <= usuarios[usuarioLogado].saldo) {
                usuarios[usuarioLogado].saldo -= valorB;
                salvarUsuarios(); // Salva as alterações
            }else{
                printf("Valor inválido ou saldo insuficiente.\n");
                break;
            }
            // Solicitando ao usuário para inserir 5 números entre 1 e 60

            printf("Caso acerte 2 sua Aposta será multiplicada por 2.0\n");
            printf("Caso acerte 3 sua Aposta será multiplicada por 4.0\n");
            printf("Caso acerte 4 sua Aposta será multiplicada por 6.0\n");
            printf("Caso acerte 5 sua Aposta será multiplicada por 20.0\n");
            printf("Escolha 5 números entre 1 e 60:\n");
            for (int i = 0; i < NUMEROS; i++) {
                do {
                    printf("Número %d: ", i + 1);
                    scanf("%d", &escolhidos[i]);
                    if (escolhidos[i] < 1 || escolhidos[i] > 60) {
                        printf("Número inválido! Escolha um número entre 1 e 60.\n");
                    }
                } while (escolhidos[i] < 1 || escolhidos[i] > 60);
            }

            // Ordenando os arrays
            ordenar(sorteados, NUMEROS);
            ordenar(escolhidos, NUMEROS);

            // Exibindo os números sorteados e escolhidos
            printf("\nNúmeros sorteados: ");
            for (int i = 0; i < NUMEROS; i++) {
                printf("%d ", sorteados[i]);
            }

            printf("\nSeus números: ");
            for (int i = 0; i < NUMEROS; i++) {
                printf("%d ", escolhidos[i]);
            }

            // Comparando os arrays e calculando os pontos
            acertos = comparar(sorteados, escolhidos, NUMEROS);
            pontos = calcular_pontos(acertos);
            if(acertos >= 2){
            usuarios[usuarioLogado].saldo = valorB * pontos;
            }
            ganhou = valorB * pontos;
            salvarUsuarios();

            // Exibindo o resultado
            printf("\n\nVocê acertou %d números e ganhou R$ %.2f.\n", acertos, ganhou);
            
        break;
        case 8:
            printf("Saindo...\n");
            // Salva os dados antes de sair
            salvarUsuarios();
            salvarApostas();
            salvarApostasUsuarios();
            salvarApostasUsuariosConcluida();
            break;
        default:
            printf("Opção inválida.\n");
    }
}

void adicionarJogo() {
    Aposta novoJogo;

    printf("Digite o ID do jogo: ");
    scanf("%d", &novoJogo.id);
    printf("Digite o time da casa: ");
    scanf("%s", novoJogo.casa);
    printf("Digite o time visitante: ");
    scanf("%s", novoJogo.visitante);
    printf("Digite a odd para a vitória da casa: ");
    scanf("%f", &novoJogo.oddCasa);
    printf("Digite a odd para a vitória do visitante: ");
    scanf("%f", &novoJogo.oddVisitante);
    printf("Digite a odd para empate: ");
    scanf("%f", &novoJogo.oddEmpate);

    apostas[numeroApostas] = novoJogo;
    numeroApostas++;

    printf("Jogo adicionado com sucesso!\n");

    salvarApostas(); // Salva as alterações
}

void definirResultadoJogo() {
    int idJogo, resultado;
    float valorGanho;

    printf("Digite o ID do jogo para definir o resultado: ");
    scanf("%d", &idJogo);

    // Busca o jogo pelo ID
    Aposta* aposta = NULL;
    int indiceAposta = -1;
    for (int i = 0; i < numeroApostas; i++) {
        if (apostas[i].id == idJogo) {
            aposta = &apostas[i];
            indiceAposta = i;
            break;
        }
    }

    if (aposta == NULL) {
        printf("Jogo não encontrado.\n");
        return;
    }

    printf("Digite o resultado do jogo (1 - Casa, 2 - Visitante, 3 - Empate): ");
    scanf("%d", &resultado);

    for (int i = 0; i < numeroApostasUsuarios; i++) {
        if (apostasUsuarios[i].idAposta == idJogo) {
            ApostaUsuarioConcluida apostaConcluida;
            apostaConcluida.idUsuario = apostasUsuarios[i].idUsuario;
            apostaConcluida.idAposta = apostasUsuarios[i].idAposta;
            apostaConcluida.valorApostado = apostasUsuarios[i].valorApostado;

            switch (resultado) {
                case 1: // Vitória da casa
                    valorGanho = apostasUsuarios[i].valorApostado * aposta->oddCasa;
                    break;
                case 2: // Vitória do visitante
                    valorGanho = apostasUsuarios[i].valorApostado * aposta->oddVisitante;
                    break;
                case 3: // Empate
                    valorGanho = apostasUsuarios[i].valorApostado * aposta->oddEmpate;
                    break;
                default:
                    printf("Resultado inválido.\n");
                    return;
            }

            apostaConcluida.valorGanho = valorGanho;
            apostasUsuariosConcluida[numeroApostasUsuariosConcluida++] = apostaConcluida;

            // Atualiza o saldo do usuário
            usuarios[apostasUsuarios[i].idUsuario].saldo += valorGanho;
        }
    }

    // Salva as alterações
    salvarApostasUsuariosConcluida();
    salvarUsuarios();

    // Remove as apostas concluídas do arquivo de apostas em aberto
    for (int i = indiceAposta; i < numeroApostas - 1; i++) {
        apostas[i] = apostas[i + 1];
    }
    numeroApostas--;
    salvarApostas();

    printf("Resultado do jogo definido e apostas concluídas registradas.\n");
}

void listarUsuarios() {
    printf("Listando usuários:\n");
    for (int i = 0; i < numeroUsuarios; i++) {
        printf("Usuário %d:\n", i + 1);
        printf("Nome: %s\n", usuarios[i].nomeUsuario);
        printf("Email: %s\n", usuarios[i].email);
        printf("Saldo: R$%.2f\n", usuarios[i].saldo);
        printf("-------------------------\n");
    }
}

void listarApostasUsuarios() {
    printf("Listando apostas dos usuários:\n");
    for (int i = 0; i < numeroApostasUsuarios; i++) {
        printf("Aposta %d:\n", i + 1);
        printf("Usuário ID: %d\n", apostasUsuarios[i].idUsuario);
        printf("Jogo ID: %d\n", apostasUsuarios[i].idAposta);
        printf("Valor Apostado: R$%.2f\n", apostasUsuarios[i].valorApostado);
        printf("-------------------------\n");
    }
}

void menuADM() {
    int opcao;
    while (1) {
        printf("\nMenu do Administrador\n");
        printf("1. Adicionar Jogo\n");
        printf("2. Definir o Resultado do Jogo\n");
        printf("3. Listar Usuários\n");
        printf("4. Listar Apostas dos Usuários\n");
        printf("5. Listar Jogos Disponíveis\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarJogo();
                break;
            case 2:
                definirResultadoJogo();
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                listarApostasUsuarios();
                break;
            case 5:
                printf("Listando jogos disponíveis:\n");
                for (int i = 0; i < numeroApostas; i++) {
                    printf("Jogo %d:\n", i + 1);
                    printf("ID: %d\n", apostas[i].id);
                    printf("Time da Casa: %s\n", apostas[i].casa);
                    printf("Time Visitante: %s\n", apostas[i].visitante);
                    printf("Odd Casa: %.2f\n", apostas[i].oddCasa);
                    printf("Odd Visitante: %.2f\n", apostas[i].oddVisitante);
                    printf("Odd Empate: %.2f\n", apostas[i].oddEmpate);
                    printf("-------------------------\n");
                }
                break;
            case 6:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void menuLogin() {
    printf("1. Cadastrar\n");
    printf("2. Logar\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao = 0;

    // Carrega os dados dos arquivos binários
    carregarUsuarios();
    carregarApostas();
    carregarApostasUsuarios();
    carregarApostasUsuariosConcluida();

    while (opcao != 3) {
        menuLogin();
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrarUsuario();
        } else if (opcao == 2) {
            if (logarUsuario()) {
                int tipoUsuario;
                printf("Digite 1 para Cliente ou 2 para Administrador: ");
                scanf("%d", &tipoUsuario);

                switch (tipoUsuario) {
                    case 1:
                        menuPrincipal();
                        break;
                    case 2:
                        menuADM();
                        break;
                    default:
                        printf("Tipo de usuário inválido.\n");
                }
            }
        } else if (opcao == 3) {
            printf("Saindo...\n");
            // Salva os dados nos arquivos binários antes de sair
            salvarUsuarios();
            salvarApostas();
            salvarApostasUsuarios();
            salvarApostasUsuariosConcluida();
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
