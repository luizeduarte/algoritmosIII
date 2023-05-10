#ifndef _INSERE_AVL_H_
#define _INSERE_AVL_H_
#include "manipula_avl.h"

//recebe a raiz e insere um nodo com o valor passado, balanceando a arvore e retornando a raiz da mesma
struct nodo_avl* insere_nodo(struct nodo_avl* nodo, int valor);	

#endif
