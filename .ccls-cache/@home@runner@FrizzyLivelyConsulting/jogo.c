#include "jogo.h"
#include "aposta.h"
#include "usuario.h"
#include <stdio.h>

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
