#include "bingo.h"

// Função para ordenar os valores usando o algoritmo bubble sort
void ordenar(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função Busca Binaria e contar os acertos
int comparar(int sorteados[], int escolhidos[], int n) {
    int acertos = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sorteados[i] == escolhidos[j]) {
                acertos++;
                break;
            }
        }
    }
    return acertos;
}

// Função para calcular os pontos com base nos acertos
float calcular_pontos(int acertos) {
    switch (acertos) {
        case 2: return 2.0;
        case 3: return 4.0;
        case 4: return 6.0;
        case 5: return 20.0;
        default: return 0.0;
    }
}