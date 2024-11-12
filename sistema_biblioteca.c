#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define USUARIO_CORRETO "admin123"
#define SENHA_CORRETA "senha321"
#define MAX_LIVROS 100
#define MAX_USUARIOS 100
#define MAX_NOME 50
#define MAX_EMPRESTIMOS 100

char usuario[50];
char senha[50];

typedef struct {
    int id;
    char titulo[MAX_NOME];
    char autor[MAX_NOME];
    int ano;
    int disponivel; //1 para disponivel, 0 para emprestado
} Livro;

typedef struct {
    int id;
    char nome[MAX_NOME];
    char email[MAX_NOME];
} Usuario;

typedef struct {
    int usuario_id;
    int livro_id;
    int dia, mes, ano;
    int dia_devolucao, mes_devolucao, ano_devolucao;
} Emprestimo;

Livro biblioteca[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
Emprestimo emprestimos[MAX_LIVROS];
int total_livros = 0;
int total_usuarios = 0;
int total_emprestimos = 0;



// FUNÇÕES

void adicionar_livros() {
    if (total_livros < MAX_LIVROS) {
        Livro livro;
        livro.id = total_livros + 1;
        printf("----------------------------------------\n");
        printf("|                                      |\n");
        printf("|       === Adicionar livro ===        |\n");
        printf("|                                      |\n");
        printf("|                                       \n");
        printf("|     Título: ");
        // necessário ter [^\n] para o scanf ler o titulo ou nome corretos até que o usuário pressione enter!
        scanf(" %[^\n]s", livro.titulo);
        printf("|                                         \n");
        printf("|     Autor: ");
        scanf(" %[^\n]s", livro.autor);
        printf("|                                         \n");
        printf("|     Ano: ");
        scanf("%d", &livro.ano);
        livro.disponivel = 1;

        biblioteca[total_livros++] = livro;
        printf("|                                       \n");
        printf("|    Livro adicionado com sucesso!\n");
        printf("|                                       \n");
        printf("----------------------------------------\n\n\n");
    } else {
        printf("|                                       \n");
        printf("Limite de livros atingidos!\n");
        printf("|                                       \n");
        printf("------------------------------------------\n\n\n");
    }
}

void listar_livros() {
    printf("-----------------------------------------\n");
    printf("|                                       |\n");
    printf("|       ==== Lista de livros ====       |\n");
    printf("|                                       |\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total_livros; i++) {

        printf("|                                       \n");
        printf("|     ID: %d | Título: %s | Autor: %s | Ano: %d | Disponível: %s\n",
                biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                biblioteca[i].ano, biblioteca[i].disponivel ? "Sim" : "Não");
        printf("|                                       \n");
        printf("-----------------------------------------------------------------------------------------------------------\n\n\n");
    }
}


void adicionar_usuario() {
    if (total_usuarios < MAX_USUARIOS) {
        Usuario usuario;
        usuario.id = total_usuarios + 1;
        printf("------------------------------------------\n");
        printf("|                                         \n");
        printf("|        === Adicionar Usuário ===        \n");
        printf("|                                         \n");
        printf("|                                         \n");
        printf("|     Nome: ");
        scanf(" %[^\n]s", usuario.nome);
        printf("|                                         \n");
        printf("|     Email: ");
        scanf(" %[^\n]s", usuario.email);

        usuarios[total_usuarios++] = usuario;
        printf("|                                       \n");
        printf("|     Usuário adicionado com sucesso!\n");
        printf("|                                       \n");
        printf("------------------------------------------\n\n\n");
    } else {
        printf("|                                       \n");
        printf("|     Limite de usuários atingidos!     \n");
        printf("|                                       \n");
        printf("------------------------------------------\n\n\n");
    }
}

void listar_usuarios() {
    
    printf("-------------------------------------------\n");
    printf("|                                         |\n");
    printf("|       ==== Lista de usuários ====       |\n");
    printf("|                                         |\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total_usuarios; i++) {
        printf("|                                       \n");
        printf("|     ID: %d | Nome: %s | Email: %s\n",
                usuarios[i].id, usuarios[i].nome, usuarios[i].email);
        printf("|                                       \n");
        printf("-----------------------------------------------------------------------------------------------------------\n\n\n");
    }
}

void realizar_emprestimo() {
    int usuario_id, livro_id;

    Emprestimo emprestimo;

    printf("------------------------------------------\n");
    printf("|                                         \n");
    printf("|        === Empréstimo ===        \n");
    printf("|                                         \n");
    printf("|                                         \n");
    printf("|     ID do Usuário: ");
    scanf("%d", &usuario_id);
    printf("|                                         \n");
    printf("|     ID do Livro: ");
    scanf("%d", &livro_id);
    printf("|                                         \n");
    printf("|     Digite a data do empréstimo \n");
    printf("|     Dia: ");
    scanf("%d", &emprestimo.dia);
    printf("|     Mês: ");
    scanf("%d", &emprestimo.mes);
    printf("|     Ano: ");
    scanf("%d", &emprestimo.ano);

    if (usuario_id > 0 && usuario_id <= total_usuarios && livro_id > 0 && livro_id <= total_livros) {
        if (biblioteca[livro_id - 1].disponivel) {
            biblioteca[livro_id - 1].disponivel = 0;

            emprestimo.usuario_id = usuario_id;
            emprestimo.livro_id = livro_id;
            emprestimos[total_emprestimos++] = emprestimo;

            printf("|                                         \n");
            printf("|     Empréstimo realizado com sucesso!\n");
            printf("|                                         \n");
            printf("------------------------------------------\n");
        } else {
            printf("|                                         \n");
            printf("|     Livro indisponível para empréstimo!\n");
            printf("|                                         \n");
            printf("------------------------------------------\n");
        }
    } else {
        printf("|                                         \n");
        printf("|     Usuário ou livro inválido!\n");
        printf("|                                         \n");
        printf("------------------------------------------\n");
    }
}


void devolver_livro() {
    int livro_id;
    printf("-------------------------------------------\n");
    printf("|                                         \n");
    printf("|        === Devolução de livro ===        \n");
    printf("|                                         \n");
    printf("|                                         \n");
    printf("|     ID do Livro a ser devolvido: ");
    scanf("%d", &livro_id);

    if (livro_id > 0 && livro_id <= total_livros && !biblioteca[livro_id - 1].disponivel) {
        biblioteca[livro_id - 1].disponivel = 1;

        printf("|                                         \n");
        printf("|     Livro devolvido com sucesso!\n");
        printf("|                                         \n");
        printf("-------------------------------------------\n");
    } else {
        printf("|                                         \n");
        printf("|     Livro não encontrado ou já disponível!\n");
        printf("|                                         \n");
        printf("-------------------------------------------\n");
    }
}


void listar_emprestimos() {

    printf("---------------------------------------------\n");
    printf("|                                           |\n");
    printf("|  ==== Lista de empréstimo pendentes ====  |\n");
    printf("|                                           |\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < total_emprestimos; i++) {
        int livro_id = emprestimos[i].livro_id;
        int usuario_id = emprestimos[i].usuario_id;
        int dia = emprestimos[i].dia;
        int mes = emprestimos[i].mes;
        int ano = emprestimos[i].ano;

        if(biblioteca[livro_id - 1].disponivel == 0) {
        printf("|                                           \n");
        printf("|     Livro: %s (ID: %d) | Emprestado para: %s (ID: %d)\n",
               biblioteca[livro_id - 1].titulo, livro_id,
               usuarios[usuario_id - 1].nome, usuario_id);
        printf("|     Data do empréstimo: %02d/%02d/%04d \n", dia, mes, ano);
        printf("|                                       \n");
        printf("-----------------------------------------------------------------------------------------------------------\n");
        }
    }
}


void limpar_tela() {
    system("cls");
    system("clear");
}


void menu_inicial() {
    int opcao;
    do {
        printf("----------------------------------------\n");
        printf("*                                      *\n");
        printf("*         ==== Biblioteca ====         *\n");
        printf("*                                      *\n");
        printf("----------------------------------------\n");
        printf("|                                      |\n");
        printf("|   1. Adicionar Livro                 |\n");
        printf("|   2. Listar Livros                   |\n");
        printf("|   3. Adicionar Usuário               |\n");
        printf("|   4. Listar Usuários                 |\n");
        printf("|   5. Realizar Empréstimo             |\n");
        printf("|   6. Devolver Livro                  |\n");
        printf("|   7. Listar Empréstimos Pendentes    |\n");
        printf("|   8. Sair                            |\n");
        printf("|                                      |\n");
        printf("----------------------------------------\n");
        printf("\n");
        printf("   Escolha a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                limpar_tela();
                adicionar_livros();
                break;
            
            case 2:
                limpar_tela();
                listar_livros();
                break;

            case 3:
                limpar_tela();
                adicionar_usuario();
                break;

            case 4:
                limpar_tela();
                listar_usuarios();
                break;

            case 5:
                limpar_tela();
                realizar_emprestimo();
                break;

            case 6:
                limpar_tela();
                devolver_livro();
                break;

            case 7:
                limpar_tela();
                listar_emprestimos();
                break;

            case 8:
                limpar_tela();
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente...\n");
        }
    } while (opcao != 8);
}

int verificar_login(const char *usuario, const char *senha) {
    // strcmp - Função da biblioteca string.h que realiza a verificação do login e senha.
    return strcmp(usuario, USUARIO_CORRETO) == 0 && strcmp(senha, SENHA_CORRETA) == 0;
}


int main() {

    setlocale(LC_ALL, "Portuguese_Brazil");

    printf("------------------------------------\n");
    printf("|                                  \n");
    printf("|         Login Biblioteca         \n");
    printf("|                                  \n");
    printf("------------------------------------\n");
    printf("|                                  \n");
    printf("|     Login: ");
    scanf(" %s", &usuario);
    printf("|                                  \n");
    printf("|     Senha: ");
    scanf(" %s", &senha);

    if(verificar_login(usuario, senha)) {
        limpar_tela();
        menu_inicial();
    } else {
        printf("|                                   \n");
        printf("|    Usuário ou senha incorretos.   \n");
        printf("|                                   \n");
        printf("------------------------------------\n");
    }
    return 0;
}