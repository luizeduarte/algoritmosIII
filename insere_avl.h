#ifndef _MANIPULA_AVL_H_
#define _MANIPULA_AVL_H_
#include "manipula_avl.h"

struct nodo_avl* aloca_nodo(int valor);	//aloca mem do nodo e inicializa seus valores
struct nodo_avl* insere_nodo(struct nodo_avl* nodo, int valor);	
//insere um nodo com o valor passado, balanceando a arvore e retornando a raiz da mesma

#endif