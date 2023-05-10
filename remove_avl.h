#ifndef _REMOVE_AVL_H_
#define _REMOVE_AVL_H_
#include "manipula_avl.h"

//recebe um nodo e retorna o antecessor do seu valor encontrado na arvore
struct nodo_avl* antecessor(struct nodo_avl* nodo);

//recebe a raiz e remove o nodo com o valor passado, balanceando a arvore e retornando a raiz da mesma
struct nodo_avl* remove_nodo(struct nodo_avl* nodo, int valor);	

#endif