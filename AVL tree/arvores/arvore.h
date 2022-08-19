#ifndef _ARVORE_H
#define _ARVORE_H
#include <stdbool.h>
#include <stdio.h>

#define NUMERO_COLUNAS 7

int key_idx;

typedef struct avl_no* avl_tree;

typedef struct {
    char * dados[NUMERO_COLUNAS];
} avl_info;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

void insert(avl_tree * t, avl_info *x, bool * h);
bool remove_data(avl_tree * t, int idx, char * value);
bool add_new_row(avl_tree * t, avl_info x);
void load_file(avl_tree * t, char * filename, int idx);
void init_tree(avl_tree *t);
bool show_col(avl_tree t, int idx);
void filter_data(avl_tree t, int idx, char * value);
#endif
