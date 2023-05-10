#include "insere_avl.h"
#include <stdio.h>
#include <stdlib.h>

struct nodo_avl* aloca_nodo(int valor){
	struct nodo_avl* novo = malloc(sizeof(struct nodo_avl));
	novo->valor = valor;
	novo->altura = 0; 	//nao tem filhos 
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

struct nodo_avl* insere_nodo(struct nodo_avl* nodo, int valor){	
	if (!nodo)	//fim da arvore, adiciona novo nodo
		return aloca_nodo(valor);

	if (valor < nodo->valor){
		nodo->esq = insere_nodo(nodo->esq, valor);	//abre como subarvore para analisar
		nodo->esq->pai = nodo;
	} else if (valor > nodo->valor){
		nodo->dir = insere_nodo(nodo->dir, valor);
		nodo->dir->pai = nodo;
	} else 
		return nodo;	//ja existe

	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;	//atualiza a altura das raizes das subarvores
	nodo = balanceia(nodo);	//balanceia da folha para a raiz, subindo nas subarvores atraves da recursiva

	return nodo;	//retorna a raiz da subarvore
}