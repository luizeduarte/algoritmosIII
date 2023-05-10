#include "remove_avl.h"
#include <stdio.h>
#include <stdlib.h>

struct nodo_avl* sucessor(struct nodo_avl* nodo){
	//o sucessor sera o menor valor da subarvore direita
	struct nodo_avl* temp = nodo->dir;

	while (temp->esq)
		temp = temp->esq;

	return temp;
}


struct nodo_avl* remove_nodo(struct nodo_avl* nodo, int valor){
	//busca o nodo a ser removido
	if (!nodo)	//nao encontrado
		return nodo;
		
	if (valor < nodo->valor){
		nodo->esq = remove_nodo(nodo->esq, valor);
		if (nodo->esq)
			nodo->esq->pai = nodo;

	} else if (valor > nodo->valor){
		nodo->dir = remove_nodo(nodo->dir, valor);
		if (nodo->dir)
			nodo->dir->pai = nodo;
			
	} else {	//encontrou o nodo a ser removido
		if (!nodo->esq && !nodo->dir){	//eh uma folha
			free(nodo);
			return NULL;	//o pai do nodo retirado recebera NULL

		} else if(!nodo->esq ^ !nodo->dir){	//tem apenas um filho
			struct nodo_avl* temp = nodo;

			if (nodo->esq)
				nodo = nodo->esq;	//nodo é atualizado pro filho
			else 
				nodo = nodo->dir;
			
			free(temp);
			return nodo;	//o pai do nodo retirado recebera o filho do nodo retirado

		} else {	//tem dois filhos
			struct nodo_avl* temp = sucessor(nodo);	 	//retorna um ponteiro para o sucessor do valor

			nodo->valor = temp->valor;	//sobe o sucessor. Agora, por definicao da avl, o valor a ser retirado tem no maximo um filho
			nodo->dir = remove_nodo(nodo->dir, temp->valor);	//remove o valor duplicado na folha
		}
	}

	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;	//atualiza a altura das raizes das subarvores
	nodo = balanceia(nodo);		//balanceia apos ter retirado o filho da folha, subindo na arvore atraves da recursiva

	return nodo;
}