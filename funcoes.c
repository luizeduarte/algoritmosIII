#include <stdio.h>
#include <stdlib.h>

struct nodo_avl{
	int valor;
	struct nodo_avl *esq;
	struct nodo_avl *dir;
};

static void imprime_avl_(struct nodo_avl *nodo, int nivel){
	if(!nodo){
		printf("\n");
		return;
	}

	imprime_avl_(nodo->esq, nivel + 1);
	printf("%d, %d ", nodo->valor, nivel);
	imprime_avl_(nodo->dir, nivel + 1);
}

void imprime_avl(struct nodo_avl *nodo){
	imprime_avl_(nodo, 0);	//recursiva
}

struct nodo_avl* aloca_nodo(int valor){
	struct nodo_avl* novo = malloc(sizeof(struct nodo_avl));
	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

struct nodo_avl* inclui_folha(struct nodo_avl* raiz, int valor){
	struct nodo_avl *aux = raiz;
	struct nodo_avl *pai = NULL;

	while (aux){	//encontra onde deve ser inserido
		pai = aux;
		if (valor < aux->valor)
			aux = aux->esq;

		else if (valor > aux->valor)
			aux = aux->dir;
	}

	if (!pai)	//arvore vazia
		return aloca_nodo(valor);

	if (valor < pai->valor)
		pai->esq = aloca_nodo(valor);	//adiciona na folha

	else if (valor > pai->valor)
		pai->dir = aloca_nodo(valor);	//adiciona na folha

	return raiz;
}

void balencea(){
	//calcula altura pra ver se esta desbalanceado 	
}

int main(){
	struct nodo_avl* raiz = NULL;
	raiz = inclui_folha(raiz, 10);
	raiz = inclui_folha(raiz, 20);
	raiz = inclui_folha(raiz, 30);
	raiz = inclui_folha(raiz, 40);
	raiz = inclui_folha(raiz, 50);
	raiz = inclui_folha(raiz, 60);
	raiz = inclui_folha(raiz, 70);
	raiz = inclui_folha(raiz, 80);

	imprime_avl(raiz);
	return 0;
}