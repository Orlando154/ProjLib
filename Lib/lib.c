//continuei tendo problemas com a execução no vscode, neste site consegui executar https://www.online-cpp.com/online_c_compiler

#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Livro* inicializarListaLivros() {
    return NULL;
}

void adicionarLivro(struct Livro **inicio, struct Livro *novoLivro) {
    if (*inicio == NULL) {
        *inicio = novoLivro;
    } else {
        struct Livro *temp = *inicio;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoLivro;
    }
}

void liberarListaLivros(struct Livro **inicio) {
    struct Livro *atual = *inicio;
    while (atual != NULL) {
        struct Livro *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

float calcularTotalGasto(struct Usuario *usuario) {
    float total = 0.0;
    struct Livro *livro = usuario->livros;
    while (livro != NULL) {
        total += livro->custo;
        livro = livro->prox;
    }
    return total;
}

int calcularTotalPaginas(struct Usuario *usuario) {
    int totalPaginas = 0;
    struct Livro *livro = usuario->livros;
    while (livro != NULL) {
        totalPaginas += livro->paginas;
        livro = livro->prox;
    }
    return totalPaginas;
}

void menuGerenciamento(struct Usuario *usuario) {
    int opcao;
    do {
        printf("\nMenu de Gerenciamento:\n");
        printf("1. Cadastrar novo livro\n");
        printf("2. Listar todos os livros\n");
        printf("3. Editar dados de um livro\n");
        printf("4. Excluir um livro\n");
        printf("5. Mostrar total gasto\n");
        printf("6. Mostrar total de páginas\n");
        printf("7. Voltar para a tela de login\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrarLivro(usuario);
                break;
            case 2:
                listarLivros(usuario);
                break;
            case 3:
                editarLivro(usuario);
                break;
            case 4:
                excluirLivro(usuario);
                break;
            case 5:
                printf("Total gasto em livros: R$ %.2f\n", calcularTotalGasto(usuario));
                break;
            case 6:
                printf("Total de páginas dos livros: %d\n", calcularTotalPaginas(usuario));
                break;
            case 7:
                printf("Voltando para a tela de login...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 7);
}

void cadastrarLivro(struct Usuario *usuario) {
    struct Livro *novoLivro = malloc(sizeof(struct Livro));
    if (novoLivro == NULL) {
        printf("Erro ao alocar memória para o novo livro.\n");
        return;
    }
    
    printf("Nome do livro: ");
    getchar(); 
    fgets(novoLivro->nome, sizeof(novoLivro->nome), stdin);
    novoLivro->nome[strcspn(novoLivro->nome, "\n")] = '\0'; 
    
    printf("Nome do autor: ");
    fgets(novoLivro->autor, sizeof(novoLivro->autor), stdin);
    novoLivro->autor[strcspn(novoLivro->autor, "\n")] = '\0'; 
    
    printf("Quantidade de páginas: ");
    scanf("%d", &novoLivro->paginas);
    
    printf("Custo: ");
    scanf("%f", &novoLivro->custo);
    
    novoLivro->prox = NULL;
    
    adicionarLivro(&usuario->livros, novoLivro);
    printf("Livro adicionado com sucesso!\n");
}

void listarLivros(struct Usuario *usuario) {
    struct Livro *livro = usuario->livros;
    if (livro == NULL) {
        printf("Você ainda não cadastrou nenhum livro.\n");
    } else {
        printf("Livros cadastrados:\n");
        while (livro != NULL) {
            printf("Nome: %s\n", livro->nome);
            printf("Autor: %s\n", livro->autor);
            printf("Páginas: %d\n", livro->paginas);
            printf("Custo: R$ %.2f\n", livro->custo);
            printf("\n");
            livro = livro->prox;
        }
    }
}

void editarLivro(struct Usuario *usuario) {
    int indice;
    
    printf("Digite o índice do livro que deseja editar: ");
    scanf("%d", &indice);
    indice--; 
    
    struct Livro *livro = usuario->livros;
    for (int i = 0; i < indice && livro != NULL; i++) {
        livro = livro->prox;
    }
    
    if (livro != NULL) {
        printf("Novo nome do livro: ");
        getchar(); 
        fgets(livro->nome, sizeof(livro->nome), stdin);
        livro->nome[strcspn(livro->nome, "\n")] = '\0'; 
        
        printf("Novo nome do autor: ");
        fgets(livro->autor, sizeof(livro->autor), stdin);
        livro->autor[strcspn(livro->autor, "\n")] = '\0'; 
        
        printf("Nova quantidade de páginas: ");
        scanf("%d", &livro->paginas);
        
        printf("Novo custo: ");
        scanf("%f", &livro->custo);
        
        printf("Dados do livro atualizados com sucesso!\n");
    } else {
        printf("Índice inválido.\n");
    }
}

void excluirLivro(struct Usuario *usuario) {
    int indice;
    
    printf("Digite o índice do livro que deseja excluir: ");
    scanf("%d", &indice);
    indice--; 
    
    struct Livro *livro = usuario->livros;
    struct Livro *anterior = NULL;
    for (int i = 0; i < indice && livro != NULL; i++) {
        anterior = livro;
        livro = livro->prox;
    }
    
    if (livro != NULL) {
        if (anterior != NULL) {
            anterior->prox = livro->prox;
        } else {
            usuario->livros = livro->prox;
        }
        
        free(livro);
        
        printf("Livro excluído com sucesso!\n");
    } else {
        printf("Índice inválido.\n");
    }
}
 
void salvarUsuarios(struct Usuario *usuarios, int totalUsuarios) {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(usuarios, sizeof(struct Usuario), totalUsuarios, arquivo);

    fclose(arquivo);
}

int carregarUsuarios(struct Usuario *usuarios) {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de usuários não encontrado.\n");
        return 0;
    }

    int totalUsuarios = 0;
    while (fread(&usuarios[totalUsuarios], sizeof(struct Usuario), 1, arquivo) == 1) {
        totalUsuarios++;
    }

    fclose(arquivo);
    return totalUsuarios;
}

int realizarLogin(struct Usuario *usuarios, int totalUsuarios) {
    char nome[50];
    char senha[20];
    int i;
    
    printf("Digite seu nome de usuário: ");
    scanf("%s", nome);
    
    printf("Digite sua senha: ");
    scanf("%s", senha);
    
    for (i = 0; i < totalUsuarios; i++) {
        if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s!\n", usuarios[i].nome);
            
            return i; 
        }
    }
    
    printf("Nome de usuário ou senha incorretos. Tente novamente.\n");
    return -1;
}

//verificar se o usuário já existe
int verificarNomeUsuario(struct Usuario *usuarios, int totalUsuarios, char *nomeUsuario) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nomeUsuario) == 0) {
            return 1; 
        }
    }
    return 0; 
}

// verificar se o email já existe
int verificarEmail(struct Usuario *usuarios, int totalUsuarios, char *email) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void cadastrarUsuario(struct Usuario *usuarios, int *totalUsuarios) {
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuarios[*totalUsuarios].nome);

    while (verificarNomeUsuario(usuarios, *totalUsuarios, usuarios[*totalUsuarios].nome)) {
        printf("Nome de usuário já existe. Digite outro nome de usuário: ");
        scanf("%s", usuarios[*totalUsuarios].nome);
    }
    
    printf("Digite seu e-mail: ");
    scanf("%s", usuarios[*totalUsuarios].email);

    // Verifica '@'
    while (verificarEmail(usuarios, *totalUsuarios, usuarios[*totalUsuarios].email) || !strchr(usuarios[*totalUsuarios].email, '@')) {
        printf("Email já cadastrado ou inválido. Digite outro email: ");
        scanf("%s", usuarios[*totalUsuarios].email);
    }
    
    printf("Digite sua senha: ");
    scanf("%s", usuarios[*totalUsuarios].senha);

    usuarios[*totalUsuarios].livros = inicializarListaLivros();
    (*totalUsuarios)++;
}
