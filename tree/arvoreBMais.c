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
        perror("Erro ao alocar memória para a árvore B+");
        exit(EXIT_FAILURE);
    }
    novo->raiz = criafolha(); // Corrigido: Chamar a função criafolha
    novo->altura = 1;
    return novo;
}

// Inserir um valor na folha
void InsereFolha(No_folha *folha, int chave, int valor){
    int i = folha->num_chaves - 1; // isso garante que o ponteiro da árvore nunca seja maior que "ORDEM"

    // localizando a posição correta
    while(i >= 0 && folha->chave[i] > chave){
        folha->chave[i + 1] = folha->chave[i];
        folha->valores[i + 1] = folha->valores[i];
        i--;
    }

    // inserindo os valores novos
    folha->chave[i + 1] = chave;
    folha->valores[i + 1] = valor;
    folha->num_chaves++;
}

// Dividindo folhas
No_folha *DivideFolhas(No_folha *folha, int *chave_promovida) {
    int meio = ORDEM / 2; // momento de partição
    No_folha *novo = criafolha();

    printf("Iniciando divisão da folha. Número de chaves na folha: %d\n", folha->num_chaves);

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
    printf("Folha dividida. A chave %d foi promovida para o nó interno.\n", *chave_promovida);

    return novo;
}

// Inserir na árvore B+
void InsereArvoreBMais(ArvoreBMais *arvore, int chave, int valor) {
    No_folha *raiz = (No_folha *)arvore->raiz; // permite a inserção dentro da árvore B+

    printf("Inserindo chave %d, valor %d\n", chave, valor);

    // Se a raiz for uma folha e ainda houver espaço
    if (raiz->num_chaves < ORDEM) {
        InsereFolha(raiz, chave, valor);
    } else {
        // Caso a folha esteja cheia, realiza a divisão
        int chave_promovida;
        No_folha *novo = DivideFolhas(raiz, &chave_promovida);

        // Criando um nó interno para ser a nova raiz
        NoInterno *novoRaiz = criaNoInterno();
        novoRaiz->chave[0] = chave_promovida;
        novoRaiz->ponteiro[0] = raiz;
        novoRaiz->ponteiro[1] = novo;
        novoRaiz->num_chaves = 1;

        // Atualizando a raiz da árvore e a altura
        arvore->raiz = novoRaiz;
        arvore->altura++;
    }
}

int main() {
    ArvoreBMais *arvore = criaArvoreBMais();

    // Inserções
    InsereArvoreBMais(arvore, 10, 100);
    InsereArvoreBMais(arvore, 20, 200);
    InsereArvoreBMais(arvore, 5, 50);
    InsereArvoreBMais(arvore, 15, 150);  // Testa a divisão da folha

    // Verificando a árvore após inserções
    if (arvore->altura == 1) {
        No_folha *folha = (No_folha *)arvore->raiz;
        printf("Folha: ");
        for (int i = 0; i < folha->num_chaves; i++) {
            printf("%d ", folha->chave[i]);
        }
        printf("\n");
    } else {
        printf("Árvore dividida em nós internos e folhas.\n");
    }

    return 0;
}
