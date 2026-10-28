/*Aluno : prontuário, nome completo, nome do curso, ano de ingresso,
 ano de formatura, endereço e dois telefones de contato.
 
--MENU--
 1- Filtrar por curso;
 2- Filtrar por ano de formatura

 PE3022587 - Karina Lemes Bombonato */

#include <stdio.h>
#include <string.h>
#define max 40 // quantidade de alunos p/ cadastro
#define tam 100

typedef struct endereco
{
    int num_casa;
    char rua[tam];
    char bairro[tam];
} ENDERECO;

typedef struct aluno
{
    int prontuario;
    char nome_aluno[tam];
    char nome_curso[tam];
    int ano_ingresso;
    int ano_formatura;
    ENDERECO endereco;
    int num_tel1;
    int num_tel2;

} ALUNO;

typedef struct lista
{
    ALUNO alunos[max];
    int quant;
} LISTA;

void inicializa(LISTA *lista)
{
    lista->quant = 0;
}

int cheia(LISTA *lista)
{
    return (lista->quant == max);
}

int vazia(LISTA *lista)
{
    return (lista->quant == 0);
}

void dados_aluno(ALUNO *aluno)
{
    printf("\nPreencha os dados do aluno:");
    printf("\nProntuario: ");
    scanf("%d", &aluno->prontuario);

    printf("\nNome Completo: ");
    scanf(" %[^\n]", aluno->nome_aluno);

    printf("\nEndereco-");
    printf("\n Rua: ");
    scanf(" %[^\n]", &aluno->endereco.rua);

    printf("\nNumero: ");
    scanf("%d", &aluno->endereco.num_casa);

    printf("\nBairro: ");
    scanf(" %[^\n]", &aluno->endereco.bairro);

    printf("\nTelefone 1 (Apenas numeros): ");
    scanf("%d", &aluno->num_tel1);

    // printf("\nTelefone 2 (Apenas numeros): ");
    // scanf("%d", &aluno->num_tel2);

    printf("\nNome do curso (Apenas a sigla): ");
    scanf(" %[^\n]", aluno->nome_curso);

    printf("\nAno de ingresso: ");
    scanf("%d", &aluno->ano_ingresso);

    printf("\nAno de formatura: ");
    scanf("%d", &aluno->ano_formatura);
}

void inserir_aluno(LISTA *lista, ALUNO *aluno)
{

    if (cheia(lista))
    {
        printf("\n ERRO:Limite de cadastro atingido!\n");
    }
    else
    {
        for (int i = lista->quant; i > 0; i--)
        {
            lista->alunos[i] = lista->alunos[i - 1]; // abre espaço para direita
        }

        lista->alunos[0] = *aluno; // add aluno na lista
        lista->quant++;
    }
}

void filtro_ano(LISTA *lista)
{
    if (vazia(lista))
    {
        printf("\nERRO: Nenhum aluno cadastrado!\n");
        return;
    }

    int total_anos = 0;
    int anos_unicos[max];

    for (int i = 0; i < lista->quant; i++)
    {
        int ano_atual = lista->alunos[i].ano_formatura;
        int ano_existe = 0;

        for (int j = 0; j < total_anos; j++)
        {
            if (anos_unicos[j] == ano_atual)
            {
                ano_existe = 1;
            }
        }
        if (!ano_existe)
        {
            anos_unicos[total_anos] = ano_atual;
            total_anos++;
        }
    }

    printf("\n=== ALUNOS POR ANO DE FORMATURA ===\n");
    for (int a = 0; a < total_anos; a++)
    {
        int ano = anos_unicos[a];
        int count = 0;

        printf("\n ANO %d:\n", ano);
        printf("------------------------\n");

        for (int i = 0; i < lista->quant; i++)
        {
            if (lista->alunos[i].ano_formatura == ano)
            {
                printf("Prontuário: %d\n", lista->alunos[i].prontuario);
                printf("Nome: %s\n", lista->alunos[i].nome_aluno);
                count++;
            }
        }

        printf("  Total: %d aluno(s)\n", count);
    }
}

void filtro_curso(LISTA *lista)
{
    if (vazia(lista))
    {
        printf("\n ERRO: Nenhum aluno cadastrado!\n");
        return;
    }

    char cursos_unicos[max][50]; 
    int total_cursos = 0;

    for (int i = 0; i < lista->quant; i++)
    {
        char curso_atual[50];
        strcpy(curso_atual, lista->alunos[i].nome_curso);

        int curso_existe = 0;

        for (int j = 0; j < total_cursos; j++)
        {
            if (strcmp(cursos_unicos[j], curso_atual) == 0) // compara strings
            {
                curso_existe = 1;
                break;
            }
        }

        if (!curso_existe)
        {
            strcpy(cursos_unicos[total_cursos], curso_atual);
            total_cursos++;
        }
    }

    printf("\n=== ALUNOS POR CURSO ===\n");

    for (int c = 0; c < total_cursos; c++)
    {
        int count = 0;

        printf("\nCURSO: %s\n", cursos_unicos[c]);
        printf("────────────────────────────\n");

        for (int i = 0; i < lista->quant; i++)
        {
            if (strcmp(lista->alunos[i].nome_curso, cursos_unicos[c]) == 0)
            {
                printf("Prontuário: %d\n", lista->alunos[i].prontuario);
                printf("Nome: %s\n", lista->alunos[i].nome_aluno);
                count++;
            }
        }
    }
}

void apresenta(LISTA *lista)
{
    if (vazia(lista))
    {
        printf("\nERRO:Lista vazia!\n");
        return;
    }

    printf("\n=== ALUNOS CADASTRADOS ===\n");
    for (int i = 0; i < lista->quant; i++)
    {
        printf("\n--- Aluno %d ---\n", i + 1);
        printf("Prontuário: %d\n", lista->alunos[i].prontuario);
        printf("Nome: %s\n", lista->alunos[i].nome_aluno);
        printf("Curso: %s\n", lista->alunos[i].nome_curso);
        printf("Ano ingresso: %d\n", lista->alunos[i].ano_ingresso);
        printf("Ano formatura: %d\n", lista->alunos[i].ano_formatura);
        printf("Telefone 1: %d\n", lista->alunos[i].num_tel1);
        printf("Telefone 2: %d\n", lista->alunos[i].num_tel2);
    }
}

int menu()
{
    int opcao;
    printf("\n-- RELATORIOS --");
    printf("\n1- Filtrar por curso.");
    printf("\n2- Filtrar por ano de formatura.");
    printf("\n3- Apresentar todos.");
    printf("\n0- Sair.\n");
    printf("\nSelecione a opcao que deseja: ");

    scanf("%d", &opcao);

    return opcao;
}

int main()
{
    int opcao;
    char resp = 's';

    ALUNO aluno;
    LISTA lista;
    inicializa(&lista);

    while ((resp == 's' || resp == 'S') && !cheia(&lista))
    {
        dados_aluno(&aluno);
        inserir_aluno(&lista, &aluno);

        if (!cheia(&lista))
        {
            printf("\nCadastrar outro aluno? (s/n): ");
            scanf(" %c", &resp);
        }
    }

    if (cheia(&lista))
    {
        printf("\nAtingiu o limite máximo (%d alunos).\n", max);
    }
    do
    {
        opcao = menu();
        switch (opcao)
        {

        case 1:
            filtro_curso(&lista);
            break;
        case 2:
            filtro_ano(&lista);
            break;
        case 3:
            apresenta(&lista);
            break;
        case 0:
            printf("\nPrograma encerrado.\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}