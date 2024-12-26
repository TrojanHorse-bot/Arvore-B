#ifndef BTREE_MANIPULATION_H
    #define BTREE_MANIPULATION_H

    #include "tree_nodes.h" /* Puxando as nossas structs personalizadas */

    /* Cria uma nova árvore B */
    /* Recebe um N de árvore B "N" e retorna a nova árvore */
    Btree Btree_new(int N);

    /* Insere um nó em uma árvore B */
    /* Recebe a árvore e o nó */
    void Btree_insert(Btree tree, Bnode node);

#endif