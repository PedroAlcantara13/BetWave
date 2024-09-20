#include "aposta_usuario_concluida.h"
#include "aposta_usuario.h"

ApostaUsuarioConcluida apostasUsuariosConcluidas[100];
int numeroApostasUsuariosConcluidas = 0;

void salvarApostasUsuariosConcluida() {
    FILE* arquivo = abrirArquivo("apostas_usuarios_concluidas.bin", "wb");
    fwrite(&numeroApostasUsuariosConcluidas, sizeof(int), 1, arquivo);
    fwrite(apostasUsuariosConcluidas, sizeof(ApostaUsuarioConcluida), numeroApostasUsuariosConcluidas, arquivo);
    fclose(arquivo);
}


