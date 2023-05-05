#include <stdio.h>
#include <stdlib.h>

struct nodo_avl{
	int valor, altura;
	struct nodo_avl *esq, *dir, *pai;
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
	novo->altura = 0; 	//nao tem filhos 
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

int altura(struct nodo_avl nodo, struct nodo_avl nodo2){
	if (nodo->esq > nodo->dir)
		return nodo->esq + 1;
	else
		return nodo->dir + 1;

}

struct nodo_avl* rotacao_dir(struct nodo_avl* nodo){
	struct nodo_avl* nodo2 = nodo->left;
	struct nodo_avl* temp = nodo2->right;

	nodo2->right = nodo;
	nodo->left = temp;

	//atualiza as alturas
	nodo = altura(nodo->esq, nodo->dir);
	nodo2 = altura(nodo2->esq, nodo2->dir);

	return nodo2;
}

struct nodo_avl* rotacao_esq(struct nodo_avl* nodo){
	struct nodo_avl* nodo2 = nodo->right;
	struct nodo_avl* temp = nodo2->left;

	nodo2->right = nodo;
	nodo->left = temp;

	//atualiza as alturas
	nodo = altura(nodo->esq, nodo->dir);
	nodo2 = altura(nodo2->esq, nodo2->dir);

	return nodo2;
}

struct nodo_avl* balanceia(struct nodo_avl* nodo, struct nodo_avl* novo){
	//DEVE DAR SEGFAULT
	int fator_balanceamento = nodo->esq->altura - nodo->dir->altura;

	if (fator_balanceamento > 1){	//o lado esquerdo esta desbalanceado
		if (novo->valor < nodo->esq->valor)
			nodo = rotacao_dir(nodo);
		else {
			nodo = rotacao_esq(nodo->esq);
			nodo = rotacao_dir(nodo);
		}
	} else if (fator_balanceamento < -1){	//lado direito desbalanceado
		if (novo->valor > nodo->dir->valor)
			rotacao_esq(nodo->esq);
		else {
			rotacao_dir(nodo->dir);
			rotacao_esq(nodo);
		}
	}

	return nodo;
}

void remove(){
	//busca o nodo

	if (!nodo->esq && !nodo->dir){	//se for a folha, apenas retira
		//desaloca 
		nodo->pai = NULL;
		return raiz;
	}


	
}

struct nodo_avl* inclui_folha(struct nodo_avl* raiz, int valor){
	struct nodo_avl *nodo = raiz;
	struct nodo_avl *pai = NULL;

	while (nodo){	//encontra onde deve ser inserido
		pai = nodo;
		if (valor < nodo->valor)
			nodo = nodo->esq;

		else if (valor > nodo->valor)
			nodo = nodo->dir;
	}

	if (!pai)	//arvore vazia
		return aloca_nodo(valor);
		
	if (valor < pai->valor){
		pai->esq = aloca_nodo(valor);	//adiciona na folha
		pai = balanceia(pai, pai->esq);

	} else if (valor > pai->valor){
		pai->dir = aloca_nodo(valor);	//adiciona na folha
		pai = balanceia(pai, pai->dir);
	}

	return raiz;
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