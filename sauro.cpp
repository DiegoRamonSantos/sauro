#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct Aluno
{
    char nome[MAX_NOME];
    int matricula;
    char curso[MAX_NOME];
    float valorMensalidade;
    char statusFinanceiro[15]; // "adimplente" ou "inadimplente"
    struct Aluno *prox;
} Aluno;

typedef struct Curso
{
    char nome[MAX_NOME];
    int codigo;
    float valorCurso;
    struct Curso *prox;
} Curso;

Aluno *listaAlunos = NULL;
Curso *listaCursos = NULL;

// Função de pesquisa sequencial de aluno por matricula
Aluno *pesquisarAlunoPorMatricula(int matricula);

// Função de menu
void menuPrincipal();
void menuAdministrador();
void menuGestaoAlunos();
void menuGestaoCursos();
void menuAluno();

// Função para validar a entrada do usuario
int obterOpcao(int minimo, int maximo);

// Função CRUD de alunos
void cadastrarAluno();
void alterarCadastroAluno();
void removerCadastroAluno();
void relatorioAlunos();
void statusFinanceiroAlunos();

// Função CRUD de cursos
void cadastrarCurso();
void alterarCurso();
void removerCurso();
void listarCursos();

// Função auxiliares para lista encadeada
void inserirAlunoInicio(Aluno **lista, Aluno *novoAluno);
void inserirAlunoFim(Aluno **lista, Aluno *novoAluno);
void inserirCursoOrdenado(Curso **lista, Curso *novoCurso);
Aluno *buscarAluno(int matricula);
Curso *buscarCurso(int codigo);

// Função para ordenar a lista de alunos usando BubbleSort
void ordenarAlunosPorMatricula(Aluno **lista);

int main()
{
    menuPrincipal();
    return 0;
}

// Implementação da função de pesquisa sequencial
Aluno *pesquisarAlunoPorMatricula(int matricula)
{
    Aluno *aluno = listaAlunos;
    while (aluno != NULL)
    {
        if (aluno->matricula == matricula)
        {
            return aluno;
        }
        aluno = aluno->prox;
    }
    return NULL;
}

void menuPrincipal()
{
    int opcao;
    do
    {
        printf("Menu Principal:\n");
        printf("1) Administrador\n");
        printf("2) Aluno\n");
        printf("3) Sair\n");
        printf("Escolha uma opcao: ");
        opcao = obterOpcao(1, 3);

        switch (opcao)
        {
        case 1:
            menuAdministrador();
            break;
        case 2:
            menuAluno();
            break;
        case 3:
            printf("Saindo...\n");
            break;
        }
    } while (opcao != 3);
}

void menuAdministrador()
{
    int opcao;
    do
    {
        printf("\nMenu Administrador:\n");
        printf("1) Gestao de Alunos\n");
        printf("2) Gestao de Cursos\n");
        printf("3) Relatorios\n");
        printf("4) Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        opcao = obterOpcao(1, 4);

        switch (opcao)
        {
        case 1:
            menuGestaoAlunos();
            break;
        case 2:
            menuGestaoCursos();
            break;
        case 3:
            printf("\nMenu Relatorios:\n");
            printf("1) Relatorio de Alunos Cadastrados\n");
            printf("2) Status Financeiro de Alunos\n");
            printf("3) Voltar ao Menu Anterior\n");
            printf("Escolha uma opcao: ");
            opcao = obterOpcao(1, 3);

            switch (opcao)
            {
            case 1:
                relatorioAlunos();
                break;
            case 2:
                statusFinanceiroAlunos();
                break;
            case 3:
                printf("Voltando ao Menu Administrador...\n");
                break;
            }
            break;
        case 4:
            printf("Voltando ao Menu Principal...\n");
            break;
        }
    } while (opcao != 4);
}

void menuGestaoAlunos()
{
    int opcao;
    do
    {
        printf("\nMenu Gestao de Alunos:\n");
        printf("1) Cadastrar Aluno\n");
        printf("2) Alterar Cadastro de Aluno\n");
        printf("3) Remover Cadastro de Aluno\n");
        printf("4) Relatorio (Alunos cadastrados)\n");
        printf("5) Financeiro (Status alunos adimplentes ou inadimplentes)\n");
        printf("6) Ordenar Alunos por Matricula\n");
        printf("7) Voltar ao Menu Anterior\n");
        printf("Escolha uma opcao: ");
        opcao = obterOpcao(1, 7);

        switch (opcao)
        {
        case 1:
            cadastrarAluno();
            break;
        case 2:
            alterarCadastroAluno();
            break;
        case 3:
            removerCadastroAluno();
            break;
        case 4:
            relatorioAlunos();
            break;
        case 5:
            statusFinanceiroAlunos();
            break;
        case 6:
            ordenarAlunosPorMatricula(&listaAlunos);
            break;
        case 7:
            printf("Voltando ao Menu Administrador...\n");
            break;
        }
    } while (opcao != 7);
}

void menuGestaoCursos()
{
    int opcao;
    do
    {
        printf("\nMenu Gestao de Cursos:\n");
        printf("1) Cadastrar Curso\n");
        printf("2) Alterar Curso\n");
        printf("3) Remover Curso\n");
        printf("4) Listar Cursos\n");
        printf("5) Voltar ao Menu Anterior\n");
        printf("Escolha uma opcao: ");
        opcao = obterOpcao(1, 5);

        switch (opcao)
        {
        case 1:
            cadastrarCurso();
            break;
        case 2:
            alterarCurso();
            break;
        case 3:
            removerCurso();
            break;
        case 4:
            listarCursos();
            break;
        case 5:
            printf("Voltando ao Menu Administrador...\n");
            break;
        }
    } while (opcao != 5);
}

void menuAluno()
{
    int opcao;
    do
    {
        printf("\nMenu Aluno:\n");
        printf("1) Consultar Cursos\n");
        printf("2) Consulta Financeira\n");
        printf("3) Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        opcao = obterOpcao(1, 3);

        switch (opcao)
        {
        case 1:
        {
            int matricula;
            printf("Digite a matricula do aluno que deseja pesquisar: ");
            scanf("%d", &matricula);

            Aluno *aluno = pesquisarAlunoPorMatricula(matricula);
            if (aluno == NULL)
            {
                printf("Aluno nao encontrado.\n");
            }
            else
            {
                printf("Nome: %s\n", aluno->nome);
                printf("Matricula: %d\n", aluno->matricula);
                printf("Curso: %s\n", aluno->curso);
            }
            break;
        }
        case 2:
        {
            int matricula;
            printf("Digite a matricula do aluno que deseja pesquisar: ");
            scanf("%d", &matricula);

            Aluno *aluno = pesquisarAlunoPorMatricula(matricula);
            if (aluno == NULL)
            {
                printf("Aluno nao encontrado.\n");
            }
            else
            {
                printf("Nome: %s\n", aluno->nome);
                printf("Matricula: %d\n", aluno->matricula);
                printf("Curso: %s\n", aluno->curso);
                printf("Valor da Mensalidade: %.2f\n", aluno->valorMensalidade);
                printf("Status Financeiro: %s\n", aluno->statusFinanceiro);
            }
            break;
        }
        case 3:
            printf("Voltando ao Menu Principal...\n");
            break;
        }
    } while (opcao != 3);
}

int obterOpcao(int minimo, int maximo)
{
    int opcao;
    while (scanf("%d", &opcao) != 1 || opcao < minimo || opcao > maximo)
    {
        printf("Opcao invalida. Tente novamente: ");
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
    }
    return opcao;
}

// Função CRUD de alunos
void cadastrarAluno()
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (novoAluno == NULL)
    {
        printf("Erro ao alocar memoria para o novo aluno.\n");
        return;
    }

    printf("Nome do Aluno: ");
    scanf(" %[^\n]", novoAluno->nome);

    printf("Matricula do Aluno: ");
    scanf("%d", &novoAluno->matricula);

    listarCursos();
    printf("Curso do Aluno: ");
    scanf(" %[^\n]", novoAluno->curso);

    Curso *cursoExistente = listaCursos;
    while (cursoExistente != NULL)
    {
        if (strcmp(cursoExistente->nome, novoAluno->curso) == 0)
        {
            break;
        }
        cursoExistente = cursoExistente->prox;
    }

    if (cursoExistente == NULL)
    {
        printf("Curso nao existe. Cadastre o curso antes de cadastrar o aluno.\n");
        free(novoAluno);
        return;
    }

    printf("Valor da Mensalidade: ");
    scanf("%f", &novoAluno->valorMensalidade);

    int statusFinanceiro;
    printf("Status Financeiro (1 - Adimplente, 2 - Inadimplente): ");
    statusFinanceiro = obterOpcao(1, 2);
    if (statusFinanceiro == 1)
    {
        strcpy(novoAluno->statusFinanceiro, "adimplente");
    }
    else
    {
        strcpy(novoAluno->statusFinanceiro, "inadimplente");
    }

    novoAluno->prox = NULL;
    inserirAlunoFim(&listaAlunos, novoAluno);

    printf("Aluno cadastrado com sucesso!\n");
}

void alterarCadastroAluno()
{
    int matricula;
    printf("Digite a matricula do aluno que deseja alterar: ");
    scanf("%d", &matricula);

    Aluno *aluno = buscarAluno(matricula);
    if (aluno == NULL)
    {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("Novo Nome do Aluno (atual: %s): ", aluno->nome);
    scanf(" %[^\n]", aluno->nome);

    listarCursos();
    printf("Novo Curso do Aluno (atual: %s): ", aluno->curso);
    scanf(" %[^\n]", aluno->curso);

    Curso *cursoExistente = listaCursos;
    while (cursoExistente != NULL)
    {
        if (strcmp(cursoExistente->nome, aluno->curso) == 0)
        {
            break;
        }
        cursoExistente = cursoExistente->prox;
    }

    if (cursoExistente == NULL)
    {
        printf("Curso nao existe. Cadastre o curso antes de cadastrar o aluno.\n");
        return;
    }

    printf("Novo Valor da Mensalidade (atual: %.2f): ", aluno->valorMensalidade);
    scanf("%f", &aluno->valorMensalidade);

    int statusFinanceiro;
    printf("Novo Status Financeiro (1 - Adimplente, 2 - Inadimplente, atual: %s): ", aluno->statusFinanceiro);
    statusFinanceiro = obterOpcao(1, 2);
    if (statusFinanceiro == 1)
    {
        strcpy(aluno->statusFinanceiro, "adimplente");
    }
    else
    {
        strcpy(aluno->statusFinanceiro, "inadimplente");
    }

    printf("Cadastro de aluno atualizado com sucesso!\n");
}

void removerCadastroAluno()
{
    int matricula;
    printf("Digite a matricula do aluno que deseja remover: ");
    scanf("%d", &matricula);

    Aluno *anterior = NULL;
    Aluno *atual = listaAlunos;

    while (atual != NULL && atual->matricula != matricula)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Aluno nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
    {
        listaAlunos = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Aluno removido com sucesso!\n");
}

void relatorioAlunos()
{
    int codigoCurso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &codigoCurso);

    Curso *curso = buscarCurso(codigoCurso);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    Aluno *aluno = listaAlunos;
    int encontrouAluno = 0;

    printf("\nRelatorio de Alunos Cadastrados no Curso %s (Codigo: %d):\n", curso->nome, curso->codigo);
    while (aluno != NULL)
    {
        if (strcmp(aluno->curso, curso->nome) == 0)
        {
            printf("Nome: %s, Matricula: %d, Valor da Mensalidade: %.2f, Status Financeiro: %s\n",
                   aluno->nome, aluno->matricula, aluno->valorMensalidade, aluno->statusFinanceiro);
            encontrouAluno = 1;
        }
        aluno = aluno->prox;
    }

    if (!encontrouAluno)
    {
        printf("Nenhum aluno cadastrado neste curso.\n");
    }
}

void statusFinanceiroAlunos()
{
    int codigoCurso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &codigoCurso);

    Curso *curso = buscarCurso(codigoCurso);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    Aluno *aluno = listaAlunos;
    int encontrouAluno = 0;

    printf("\nStatus Financeiro dos Alunos no Curso %s (Codigo: %d):\n", curso->nome, curso->codigo);
    while (aluno != NULL)
    {
        if (strcmp(aluno->curso, curso->nome) == 0)
        {
            printf("Nome: %s, Matricula: %d, Valor da Mensalidade: %.2f, Status Financeiro: %s\n",
                   aluno->nome, aluno->matricula, aluno->valorMensalidade, aluno->statusFinanceiro);
            encontrouAluno = 1;
        }
        aluno = aluno->prox;
    }

    if (!encontrouAluno)
    {
        printf("Nenhum aluno cadastrado neste curso.\n");
    }
}

// Função CRUD de cursos
void cadastrarCurso()
{
    Curso *novoCurso = (Curso *)malloc(sizeof(Curso));
    if (novoCurso == NULL)
    {
        printf("Erro ao alocar memoria para o novo curso.\n");
        return;
    }

    printf("Nome do Curso: ");
    scanf(" %[^\n]", novoCurso->nome);

    printf("Codigo do Curso: ");
    scanf("%d", &novoCurso->codigo);

    novoCurso->prox = NULL;
    inserirCursoOrdenado(&listaCursos, novoCurso);

    printf("Curso cadastrado com sucesso!\n");
}

void alterarCurso()
{
    int codigo;
    printf("Digite o codigo do curso que deseja alterar: ");
    scanf("%d", &codigo);

    Curso *curso = buscarCurso(codigo);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    // Salva o codigo atual do curso para validação depois
    int codigoAtual = curso->codigo;

    printf("Novo Nome do Curso (atual: %s): ", curso->nome);
    scanf(" %[^\n]", curso->nome);

    printf("Novo Codigo do Curso (atual: %d): ", curso->codigo);
    scanf("%d", &curso->codigo);

    // Verifica se o novo codigo do curso ja¡ existe na lista
    Curso *cursoExistente = listaCursos;
    while (cursoExistente != NULL)
    {
        if (cursoExistente != curso && cursoExistente->codigo == curso->codigo)
        {
            printf("Ja existe um curso com este codigo. A alteracao nao sera realizada.\n");

            // Restaura o codigo original do curso
            curso->codigo = codigoAtual;
            return;
        }
        cursoExistente = cursoExistente->prox;
    }

    printf("Cadastro de curso atualizado com sucesso!\n");
}

void removerCurso()
{
    int codigo;
    printf("Digite o codigo do curso que deseja remover: ");
    scanf("%d", &codigo);

    Curso *anterior = NULL;
    Curso *atual = listaCursos;

    while (atual != NULL && atual->codigo != codigo)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
    {
        listaCursos = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Curso removido com sucesso!\n");
}

void listarCursos()
{
    Curso *curso = listaCursos;
    printf("\nLista de Cursos:\n");
    while (curso != NULL)
    {
        printf("Nome: %s, Codigo: %d,", curso->nome, curso->codigo);
        curso = curso->prox;
    }
}

void inserirAlunoFim(Aluno **lista, Aluno *novoAluno)
{
    if (*lista == NULL)
    {
        *lista = novoAluno;
    }
    else
    {
        Aluno *atual = *lista;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novoAluno;
    }
}

void inserirCursoOrdenado(Curso **lista, Curso *novoCurso)
{
    if (*lista == NULL || (*lista)->codigo > novoCurso->codigo)
    {
        novoCurso->prox = *lista;
        *lista = novoCurso;
    }
    else
    {
        Curso *atual = *lista;
        while (atual->prox != NULL && atual->prox->codigo < novoCurso->codigo)
        {
            atual = atual->prox;
        }
        novoCurso->prox = atual->prox;
        atual->prox = novoCurso;
    }
}

Aluno *buscarAluno(int matricula)
{
    Aluno *atual = listaAlunos;
    while (atual != NULL)
    {
        if (atual->matricula == matricula)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

Curso *buscarCurso(int codigo)
{
    Curso *atual = listaCursos;
    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Função para ordenar a lista de alunos usando BubbleSort
void ordenarAlunosPorMatricula(Aluno **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    int trocou;
    Aluno *atual;
    Aluno *anterior = NULL;

    do
    {
        trocou = 0;
        atual = *lista;

        while (atual->prox != anterior)
        {
            if (atual->matricula > atual->prox->matricula)
            {
                int tempMatricula = atual->matricula;
                char tempNome[MAX_NOME];
                strcpy(tempNome, atual->nome);
                char tempCurso[MAX_NOME];
                strcpy(tempCurso, atual->curso);
                float tempValorMensalidade = atual->valorMensalidade;
                char tempStatusFinanceiro[15];
                strcpy(tempStatusFinanceiro, atual->statusFinanceiro);

                atual->matricula = atual->prox->matricula;
                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->curso, atual->prox->curso);
                atual->valorMensalidade = atual->prox->valorMensalidade;
                strcpy(atual->statusFinanceiro, atual->prox->statusFinanceiro);

                atual->prox->matricula = tempMatricula;
                strcpy(atual->prox->nome, tempNome);
                strcpy(atual->prox->curso, tempCurso);
                atual->prox->valorMensalidade = tempValorMensalidade;
                strcpy(atual->prox->statusFinanceiro, tempStatusFinanceiro);

                trocou = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocou);
}
