#ifndef TREE_NODES_H
    #define TREE_NODES_H

    #include <time.h>

    enum _Color {Red, Black, BLACK};
    typedef enum _Color color;

    /* Valor individual de uma chave no nó */
    typedef struct key {
        int key;                /* Índice do valor */
        char * name;            /* Ponteiro para a String de nome do valor */
        struct tm *node_time;   /* Timestamp da key */
        int value;              /* Valor numérico da chave */
    } key;

    /* Struct de um nó da árvore B */
    /* Um ponteiro é a mesma coisa que um array [] sem tamanho*/
    /* A implementação de ponteiros para ponteiros ao invés de ponteiros únicos facilita as operações de rebalanceamento da árvore */
    /* Não tenha medo de ponteiros de ponteiros, eles são seus amigos ദ്ദി(˘‿˘) */
    typedef struct Bnode {
        int size;               /* Número de chaves armazenadas no nó */
        key ** keys;            /* Vetor de endereços das chaves do nó */

        struct Bnode ** children; /* Vetor de endereços das crianças do nó */

        bool leaf;              /* Indica se o nó é folha ou não */
    } Bnode;

    /* Struct de um nó da árvore red-black */
    typedef struct RBnode {
        key * key;      /* Chave do nó*/
        color color;    /* Cor do nó */

        struct RBnode * left = null;
        struct RBnode * right = null;
        struct RBnode * parent = null;

    } RBnode

    /* Árvore B 🐝 */
    typedef struct Btree {
        int N;  /* N da árvore */
        Bnode * root; /* Raíz da árvore */
    } Btree

    /* Árvore Red-Black */
    /* Sim, é só um wrapper pro código ser mais legível */
    typedef struct RBtree {
        RBnode * root;    /* Raíz da árvore */
    } RBtree

#endif