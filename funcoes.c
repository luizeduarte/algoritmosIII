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
	novo->altura = 1; 	//nao tem filhos 
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

int altura(struct nodo_avl* nodo){
	if (!nodo)
		return -1;	//chegou na folha

	int alt_esq = altura(nodo->esq);
	int alt_dir = altura(nodo->dir);

	if (alt_esq > alt_dir)
		return alt_esq + 1;
	else
		return alt_dir + 1;

}

struct nodo_avl* rotacao_dir(struct nodo_avl* nodo){
	struct nodo_avl* nodo2 = nodo->esq;
	nodo->esq = nodo2->dir;
	nodo2->pai = nodo->pai;
	nodo->pai = nodo2;

	if (nodo2->dir)
		nodo2->dir->pai = nodo;

	nodo2->dir = nodo;

	//atualiza as alturas
	nodo->altura = altura(nodo);
	nodo2->altura = altura(nodo2);

	return nodo2;
}

struct nodo_avl* rotacao_esq(struct nodo_avl* nodo){
	struct nodo_avl* nodo2 = nodo->dir;
	nodo->dir = nodo2->esq;
	nodo2->pai = nodo->pai;
	nodo->pai = nodo2;

	if (nodo2->esq)
		nodo2->esq->pai = nodo;

	nodo2->esq = nodo;	

	//atualiza as alturas
	nodo->altura = altura(nodo);
	nodo2->altura = altura(nodo2);

	return nodo2;
}

struct nodo_avl* balanceia(struct nodo_avl* nodo, int valor){
	int fator_balanceamento = altura(nodo->esq) - altura(nodo->dir);	//NAO GOSTEI

	if (fator_balanceamento > 1){	//o lado esquerdo esta desbalanceado
		if (valor < nodo->esq->valor)
			nodo = rotacao_dir(nodo);
		else {
			nodo = rotacao_esq(nodo->esq);
			nodo = rotacao_dir(nodo);
		}
	} else if (fator_balanceamento < -1){	//lado direito desbalanceado
		if (valor > nodo->dir->valor)
			nodo = rotacao_esq(nodo->esq);
		else {
			nodo = rotacao_dir(nodo->dir);
			nodo = rotacao_esq(nodo);
		}
	}

	return nodo;
}

/*void remove(){
	//busca o nodo

	if (!nodo->esq && !nodo->dir){	//se for a folha, apenas retira
		//desaloca 
		nodo->pai = NULL;
		return raiz;
	}


	
}*/

struct nodo_avl* inclui_folha(struct nodo_avl* nodo, int valor){
	if (!nodo)	//fim da arvore
		return aloca_nodo(valor);

	if (valor < nodo->valor)
		nodo->esq = inclui_folha(nodo->esq, valor);
	else if (valor > nodo->valor)
		nodo->dir = inclui_folha(nodo->dir, valor);
	else 
		return NULL;	//ja existe

	//atualiza a altura
	nodo->altura = altura(nodo);
	//balenceia
	nodo = balanceia(nodo, valor);

	return nodo;
}



int main(){
	struct nodo_avl* raiz = NULL;
	raiz = inclui_folha(raiz, 10);
	printf("incluiu 10\n");
	raiz = inclui_folha(raiz, 20);
	imprime_avl(raiz);
	printf("incluiu 20\n");
	raiz = inclui_folha(raiz, 15);
	printf("incluiu 15\n");

	imprime_avl(raiz);
	return 0;
}