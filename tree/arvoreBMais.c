#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ORDEM 4 //máximo de chave no nó

typedef struct NoFolha{
    int chave[ORDEM]; // chaves armazenadas
    int valores[ORDEM]; // valores correspondidos
    struct NoFolha *prox; // ponteiro para o próximo elemento folha
    int num_chaves; // número atual de chaves
} No_folha;

// Estrutura do nó interno
typedef struct NoInterno{
    int chave[ORDEM];
    void *ponteiro[ORDEM + 1];
    int num_chaves;
} NoInterno;

// Estrutura da árvore B+
typedef struct ArvoreBMais{
    void *raiz; // ponteiro para o nó raiz
    int altura; // altura da árvore
} ArvoreBMais;

// Nó folha vazio
No_folha *criafolha() {
    No_folha *novo = (No_folha *)malloc(sizeof(No_folha));
    if (!novo) {
        perror("Erro ao alocar memória para nó folha");
        exit(EXIT_FAILURE);
    }
    novo->num_chaves = 0;
    novo->prox = NULL;
    memset(novo->chave, 0, ORDEM * sizeof(int));    // Inicializa as chaves com 0
    memset(novo->valores, 0, ORDEM * sizeof(int));  // Inicializa os valores com 0
    return novo;
}

// Nó interno vazio
NoInterno *criaNoInterno() {
    NoInterno *novo = (NoInterno *)malloc(sizeof(NoInterno));
    if (!novo) {
        perror("Erro ao alocar memória para nó interno");
        exit(EXIT_FAILURE);
    }
    novo->num_chaves = 0;
    memset(novo->chave, 0, ORDEM * sizeof(int));       // Inicializa as chaves com 0
    memset(novo->ponteiro, 0, (ORDEM + 1) * sizeof(void *)); // Inicializa os ponteiros com NULL
    return novo;
}

// Inicializando a árvore B+
ArvoreBMais *criaArvoreBMais() {
    ArvoreBMais *novo = (ArvoreBMais *)malloc(sizeof(ArvoreBMais));
    if (!novo) {
        perror("Erro ao alocar memoria para a arvore B+");
        exit(EXIT_FAILURE);
    }
    novo->raiz = criafolha(); // Corrigido: Chamar a função criafolha
    novo->altura = 1;
    return novo;
}

// Dividindo folhas
No_folha *DivideFolhas(No_folha *folha, int *chave_promovida) {
    int meio = ORDEM / 2; // momento de partição
    No_folha *novo = criafolha();

    printf("Iniciando divisao da folha. Numero de chaves na folha: %d\n", folha->num_chaves);

    // move a metade da direita superior para um novo nó folha
    for (int i = meio; i < ORDEM; i++) {
        novo->chave[i - meio] = folha->chave[i];
        novo->valores[i - meio] = folha->valores[i];
    }

    novo->num_chaves = ORDEM - meio;
    folha->num_chaves = meio;

    // conexão entre as folhas
    novo->prox = folha->prox;
    folha->prox = novo;

    // A chave que será promovida é a primeira chave do novo nó (novo->chave[0])
    *chave_promovida = novo->chave[0];

    // Adicionando uma mensagem indicando que as chaves foram separadas
    printf("Folha dividida. A chave %d foi promovida para o no interno.\n", *chave_promovida);

    return novo;
}

// Inserir um valor na folha
No_folha *InsereFolha(No_folha *folha, int chave, int valor, int *chave_promovida) {
    int i = folha->num_chaves - 1;

    // Localizando a posição correta para inserir a nova chave
    while (i >= 0 && folha->chave[i] > chave) {
        folha->chave[i + 1] = folha->chave[i];
        folha->valores[i + 1] = folha->valores[i];
        i--;
    }

    // Inserindo os novos valores
    folha->chave[i + 1] = chave;
    folha->valores[i + 1] = valor;
    folha->num_chaves++;

    // Verificando se a folha excedeu o número máximo de chaves
    if (folha->num_chaves == ORDEM) {
        // Dividir folha e promover chave
        return DivideFolhas(folha, chave_promovida);
    }

    // Caso não haja divisão, retorna NULL
    return NULL;
}

// Função para inserir uma chave promovida em um nó interno
void InsereNoInterno(NoInterno *pai, int chave_promovida, void *novo_no) {
    int i = pai->num_chaves - 1;

    // Localizando a posição para inserir a nova chave
    while (i >= 0 && pai->chave[i] > chave_promovida) {
        pai->chave[i + 1] = pai->chave[i];
        pai->ponteiro[i + 2] = pai->ponteiro[i + 1];
        i--;
    }

    // Inserindo a chave promovida e atualizando os ponteiros
    pai->chave[i + 1] = chave_promovida;
    pai->ponteiro[i + 2] = novo_no;
    pai->num_chaves++;
}

void InsereArvoreBMais(ArvoreBMais *arvore, int chave, int valor) {
    int chave_promovida;
    No_folha *nova_folha = InsereFolha((No_folha *)arvore->raiz, chave, valor, &chave_promovida);

    if (nova_folha != NULL) {
        // Criando um nó interno para ser a nova raiz
        NoInterno *novoRaiz = criaNoInterno();
        novoRaiz->chave[0] = chave_promovida;
        novoRaiz->ponteiro[0] = arvore->raiz;
        novoRaiz->ponteiro[1] = nova_folha;
        novoRaiz->num_chaves = 1;

        // Atualizando a raiz da árvore e a altura
        arvore->raiz = novoRaiz;
        arvore->altura++;
    }
}

void ImprimirArvore(void *raiz, int nivel, int altura) {
    if (raiz == NULL) return;

    // Verifica se estamos em um nó interno ou folha com base no nível
    if (nivel < altura - 1) {
        NoInterno *noInterno = (NoInterno *)raiz;

        // Imprimindo chaves do nível atual
        printf("Nivel %d: ", nivel);
        for (int i = 0; i < noInterno->num_chaves; i++) {
            printf("%d ", noInterno->chave[i]);
        }
        printf("\n");

        // Recursivamente imprimindo filhos
        for (int i = 0; i <= noInterno->num_chaves; i++) {
            ImprimirArvore(noInterno->ponteiro[i], nivel + 1, altura);
        }
    } else {
        No_folha *folha = (No_folha *)raiz;

        // Imprimindo chaves da folha
        printf("Folha: ");
        for (int j = 0; j < folha->num_chaves; j++) {
            printf("%d ", folha->chave[j]);
        }
        printf("\n");

        // Imprimindo folhas conectadas (próxima folha)
        No_folha *proxFolha = folha->prox;
        while (proxFolha) {
            printf("Folha: ");
            for (int j = 0; j < proxFolha->num_chaves; j++) {
                printf("%d ", proxFolha->chave[j]);
            }
            printf("\n");
            proxFolha = proxFolha->prox;  // Avançando para a próxima folha
        }
    }
}

void ExibeArvoreBMais(ArvoreBMais *arvore) {
    printf("Estrutura da Arvore B+:\n");

    if (arvore->altura == 1) {
        // Se a altura for 1, a raiz é uma folha
        No_folha *folha = (No_folha *)arvore->raiz;
        printf("Folha (Raiz): ");
        for (int i = 0; i < folha->num_chaves; i++) {
            printf("%d ", folha->chave[i]);
        }
        printf("\n");
    } else {
        // Para árvores com múltiplos níveis
        NoInterno *nivelAtual = (NoInterno *)arvore->raiz;
        ImprimirArvore(nivelAtual, 0, arvore->altura);
    }
}

int main(void) {
    // Criação da árvore B+
    ArvoreBMais *arvore = criaArvoreBMais();
    printf("\n");

    // Inserção de valores na árvore B+
    InsereArvoreBMais(arvore, 10, 100);
    InsereArvoreBMais(arvore, 20, 200);
    InsereArvoreBMais(arvore, 5, 50);
    InsereArvoreBMais(arvore, 15, 150);  // Testa a divisão da folha
    InsereArvoreBMais(arvore, 25, 115);
    InsereArvoreBMais(arvore, 26, 170);
    InsereArvoreBMais(arvore, 37, 110);
    InsereArvoreBMais(arvore, 40, 199);
    printf("\n");

    // Exibição da árvore B+
    ExibeArvoreBMais(arvore);
    printf("\n");

    return 0;
}