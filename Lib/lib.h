//continuei tendo problemas com a execução no vscode, neste site consegui executar https://www.online-cpp.com/online_c_compiler

#ifndef LIB_H
#define LIB_H

struct Livro {
    char nome[100];
    char autor[100];
    int paginas;
    float custo;
    struct Livro *prox;
};

struct Usuario {
    char nome[50];
    char email[80];
    char senha[20];
    struct Livro *livros;
};

int carregarUsuarios(struct Usuario *usuarios);
void menuCadastro(struct Usuario *usuario);
void menuGerenciamento(struct Usuario *usuario);
void cadastrarLivro(struct Usuario *usuario);
void listarLivros(struct Usuario *usuario);
void editarLivro(struct Usuario *usuario);
void excluirLivro(struct Usuario *usuario);
float calcularTotalGasto(struct Usuario *usuario);
int calcularTotalPaginas(struct Usuario *usuario);
void salvarUsuarios(struct Usuario *usuarios, int totalUsuarios);

int realizarLogin(struct Usuario *usuarios, int totalUsuarios);
int verificarNomeUsuario(struct Usuario *usuarios, int totalUsuarios, char *nomeUsuario);
int verificarEmail(struct Usuario *usuarios, int totalUsuarios, char *email);
void cadastrarUsuario(struct Usuario *usuarios, int *totalUsuarios);

#endif /* LIB_H */
