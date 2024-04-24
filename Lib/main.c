//continuei tendo problemas com a execução no vscode, neste site consegui executar https://www.online-cpp.com/online_c_compiler

#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct Usuario *usuarios = malloc(100 * sizeof(struct Usuario));
    if (usuarios == NULL) {
        printf("Erro ao alocar memória para usuários.\n");
        return 1;
    }
    int opcao, totalUsuarios = 0;
    
    totalUsuarios = carregarUsuarios(usuarios);
    
    printf("Bem-vindo ao sistema de gerenciamento de biblioteca pessoal!\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Realizar login\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &opcao);
        
        if (opcao == 1) {
            cadastrarUsuario(usuarios, &totalUsuarios);
            salvarUsuarios(usuarios, totalUsuarios);
        } else if (opcao == 2) {
            int indiceUsuario = realizarLogin(usuarios, totalUsuarios);
            if (indiceUsuario != -1) {
                menuGerenciamento(&usuarios[indiceUsuario]);
            } else {
                printf("Nome de usuario ou senha incorretos. Tente novamente.\n");
            }
        } else if (opcao == 3) {
            printf("Saindo do programa\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);
    
    free(usuarios);
    return 0;
}
