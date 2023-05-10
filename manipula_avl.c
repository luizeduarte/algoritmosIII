#include "manipula_avl.h"
#include <stdlib.h>
#include <stdio.h>

struct nodo_avl* aloca_nodo(int valor){
	//aloca um novo nodo, o inicializa e retorna um ponteiro para ele
	
	struct nodo_avl* novo = malloc(sizeof(struct nodo_avl));
	novo->valor = valor;
	novo->altura = 0; 	//nao tem filhos 
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

void desaloca_avl(struct nodo_avl* nodo){
	if (!nodo)
		return;

	desaloca_avl(nodo->esq);
	desaloca_avl(nodo->dir);
	free(nodo);
	return;
}

static void imprime_avl_(struct nodo_avl *nodo, int nivel){
	//de maneira "in order"
	if(!nodo)
		return;

	imprime_avl_(nodo->esq, nivel + 1);
	printf("%d,%d\n", nodo->valor, nivel);
	imprime_avl_(nodo->dir, nivel + 1);
	return;
}

void imprime_avl(struct nodo_avl *nodo){
	imprime_avl_(nodo, 0);	//recursiva
}

int altura(struct nodo_avl* nodo){
	//verifica se o ponteiro eh null para retornar sua altura
	if (!nodo)
		return -1;
	else
		return nodo->altura;
}

int maior(int esq, int dir){	//evita que a altura tenha q ser calculada toda vez
	//retorna o maior inteiro
	if (esq > dir)
		return esq;
	else
		return dir;
}

struct nodo_avl* rotacao_dir(struct nodo_avl* nodo){
	//pelos ponteiros, desce o pai (passado como argumento) e sobe o filho
	struct nodo_avl* nodo2 = nodo->esq;
	nodo->esq = nodo2->dir;
	nodo2->pai = nodo->pai;
	nodo->pai = nodo2;

	if (nodo2->dir)
		nodo2->dir->pai = nodo;

	nodo2->dir = nodo;

	//atualiza as alturas
	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;
	nodo2->altura = maior(altura(nodo2->esq), altura(nodo2->dir)) + 1;

	return nodo2;
}

struct nodo_avl* rotacao_esq(struct nodo_avl* nodo){
	//pelos ponteiros, desce o pai (passado como argumento) e sobe o filho
	struct nodo_avl* nodo2 = nodo->dir;
	nodo->dir = nodo2->esq;
	nodo2->pai = nodo->pai;
	nodo->pai = nodo2;

	if (nodo2->esq)
		nodo2->esq->pai = nodo;

	nodo2->esq = nodo;	

	//atualiza as alturas
	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;
	nodo2->altura = maior(altura(nodo2->esq), altura(nodo2->dir)) + 1;

	return nodo2;
}

int fator_balanceamento(struct nodo_avl* nodo){	
	//calcula o fator de balanceamento atraves das alturas
	return altura(nodo->esq) - altura(nodo->dir);
}

struct nodo_avl* balanceia(struct nodo_avl* nodo){
	//balanceia a avl a partir do nodo passado, verificando qual lado esta desbalanceado e fazendo as rotacoes necessarias
	
	if (fator_balanceamento(nodo) > 1){	//o lado esquerdo esta desbalanceado
		if (fator_balanceamento(nodo->esq) < 0)	//o lado direito do filho eh mais pesado, tende para dois lados 
			nodo->esq = rotacao_esq(nodo->esq);

		nodo = rotacao_dir(nodo);

	} else if (fator_balanceamento(nodo) < -1){	//lado direito desbalanceado
		if (fator_balanceamento(nodo->dir) > 0)	//lado esquerdo do filho esta desbalanceado, tende para dois lados
			nodo->dir = rotacao_dir(nodo->dir);

		nodo = rotacao_esq(nodo);
	}

	return nodo;
}
