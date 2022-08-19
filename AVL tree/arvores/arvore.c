#include "arvore.h"
#include <string.h>
#define SEPARADOR ","
#define MAX_LINHA 200

bool show_col(avl_tree t, int idx)
{
    if( !t ) return;
    show_col((t)->esq, idx);
    printf("%s\n", (t)->dado.dados[idx]);
    show_col((t)->dir, idx);

    return true;
}

void filter_data(avl_tree t, int idx, char * value)
{
    if( !t ) return;
    filter_data((t)->esq, idx, value);
    if(!strcmp(t->dado.dados[idx],value))
        if(idx!=0){
            printf("%s     %s\n", (t)->dado.dados[key_idx], (t)->dado.dados[idx]);
        } else printf("%s\n", (t)->dado.dados[key_idx]);
    filter_data((t)->dir, idx, value);
}

void init_tree(avl_tree *t)
{
    memset(t, 0, sizeof(avl_tree));
}

void rotacao_esq(avl_tree * t)
{
    avl_tree p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

void rotacao_dir(avl_tree * t)
{
    avl_tree p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


void insert(avl_tree * t, avl_info * x, bool * h)
{
    if (*t == NULL)
    {
        if((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL)
        {
            fprintf(stderr,"Erro de aloca�o de mem�ria!/n");
            exit(1);
        }
        *h = true;
        int i;
        for (i = 0; i < NUMERO_COLUNAS; i++)
        {
            (*t)->dado.dados[i] = x->dados[i];
        }
        //(*t)->dado.cont = 1;
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcmp(x->dados[key_idx],(*t)->dado.dados[key_idx]) < 0)   // Inserir a esquerda
    {
        insert(&(*t)->esq, x, h);
        if (*h)   // O ramo esquerdo cresceu
        {
            switch ((*t)->bal)
            {
            case 1:
                (*t)->bal = 0;
                *h = false;
                break;
            case 0:
                (*t)->bal = -1;
                break;
            case -1: // Rebalanceamento
                if ((*t)->esq->bal == -1)   //Rota�o simples p/ direita
                {
                    rotacao_dir(t);
                    (*t)->dir->bal = 0; //Ajusta o fator de	balanceamento
                }
                else     // Rota�o dupla para direita
                {
                    rotacao_esq(&(*t)->esq);
                    rotacao_dir(t);
                    // Ajusta o fator de balanceamento
                    if ((*t)->bal == -1) (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                    if ((*t)->bal == 1) (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                }
                *h = false;
                (*t)->bal = 0;
                break;
            } // fim do switch
        }
    } // fim do if
    else if (strcmp(x->dados[key_idx], (*t)->dado.dados[key_idx]) > 0)   // Inserir a direita
    {
        insert(&(*t)->dir, x, h);
        if (*h)   // O ramo direito cresceu
        {
            switch ((*t)->bal)
            {
            case -1:
                (*t)->bal = 0;
                *h = false;
                break;
            case 0:
                (*t)->bal = +1;
                break;
            case 1: // Rebalanceamento
                if ((*t)->dir->bal == 1)   // Rota�o simples p/ esquerda
                {
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    (*t)->esq->bal = 0;
                }
                else     // Rota�o dupla para esquerda
                {
                    rotacao_dir(&(*t)->dir);
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    if ((*t)->bal == +1) (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                    if ((*t)->bal == -1) (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                } // fim do else
                *h = false;
                (*t)->bal = 0;
                break;
            } // fim do switch
        }
    } // fim do if
    //else // a chave j� est� na �rvore
    //(*t)->dado.cont++;
} // fim de search


/*bool remove_data(avl_tree * t, int idx, char * value)
{
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(value,(*t)->dado.dados[idx]) == 0)
    {
        p = *t;
        if ((*t)->esq == NULL)
        {
            *t = p->dir;
        }
        else if ((*t)->dir == NULL)
        {
            *t = p->esq;
        }
        else   // nó com duas subávores
        {
            p = getMin(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if (*h) rotacao_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(value, (*t)->dado.dados[idx]) < 0)
    {
        result = remove_data(&(*t)->esq, x, h);
        if (*h) rotacao_esq(t, h);
        return result;
    }
    else
    {
        result = remove_data(&(*t)->dir, idx, value);
        if (*h) rotacao_dir(t,h);
        return result;
    }


}
*/

bool add_new_row(avl_tree * t, avl_info x)
{
    int i;
    bool h = false;
    for(i = 0; i < NUMERO_COLUNAS; i++){
        x.dados[i] = NULL;
        x.dados[i] = malloc(sizeof(char) * 100);
        if (x.dados[i] == NULL){
            return false;
        }
        scanf("%s", x.dados[i]);
    }
    insert(t,&x,&h);
    return true;
}

void load_file(avl_tree * t, char * filename, int idx)
{

    key_idx = idx;
    int i;

    FILE *arquivo;
    arquivo = fopen(filename,"r");
    char linha[MAX_LINHA], *token;

    fgets(linha,MAX_LINHA,arquivo);

    avl_info dados_colunas;
    bool h = false;
    while(fgets(linha,MAX_LINHA,arquivo)!=NULL)
    {

        token = strtok(linha,SEPARADOR);
        dados_colunas.dados[0] = malloc(sizeof(char)*strlen(token));
        strcpy(dados_colunas.dados[0], token);
        ///caso queira indices nao ordenados
        //printf("%s\n", dados_colunas.dados[0]);

        for(i = 1; i < NUMERO_COLUNAS ; i++)
        {

            if(i < NUMERO_COLUNAS-1)
                token = strtok(NULL,SEPARADOR);
            else
                token = strtok(NULL,"\n");
            dados_colunas.dados[i] = malloc(sizeof(char) * strlen(token));
            strcpy(dados_colunas.dados[i],token);
            ///caso queira dados numéricos da arvore
            //printf("%s\n", dados_colunas.dados[i]);
        }

        insert(t, &dados_colunas, &h);

    }
    fclose(arquivo);
}
