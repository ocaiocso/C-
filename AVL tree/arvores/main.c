#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(void) {
  int idx = 0;
  avl_tree t;
  avl_info x;
  init_tree(&t);
  char nome_do_arquivo[100];
  printf("Insira o caminho do arquivo: ");
  scanf("%99s[\n]", nome_do_arquivo);

  ///Abertura do arquivo
  load_file(&t,nome_do_arquivo,idx);
  printf("Qual coluna deseja obter? ");
  scanf("%d", &idx);
  printf("\nDados da coluna %d: \n", idx);

  ///Mostrar coluna
  show_col(t,idx-1);
  printf("\n");

  printf("Escolha o dado a ser filtrado: ");
  char value[30];
  scanf("%s", value);
  printf("Escolha a coluna a ser filtrada: ");
  scanf("%d", &idx);
  if (idx != 1){
  printf("Coluna 1:     Coluna %d: \n", idx);
  } else printf("Coluna 1:  \n");

  ///Filtragem de dados
  filter_data(t,idx-1,value);
  printf("\n");
  printf("Insira os dados a serem adicionados: (um valor por linha)\n");

  ///Adicionar nova linha
  add_new_row(&t,x);
  printf("\nColunas com os dados adicionados: \n");

  for(idx=0;idx<NUMERO_COLUNAS;idx++){
    printf("Coluna %d\n", idx+1);
    show_col(t,idx);
    printf("\n");
  }

  //remove_data(&t,idx,value);


   return 0;
}
