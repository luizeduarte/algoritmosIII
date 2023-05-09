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

int fator_balanceamento(struct nodo_avl* nodo){
	return altura(nodo->esq) - altura(nodo->dir);
}

struct nodo_avl* balanceia(struct nodo_avl* nodo){
	if (fator_balanceamento(nodo) > 1){	//o lado esquerdo esta desbalanceado
		if (fator_balanceamento(nodo->esq) < 0)	//o lado direito do filho eh mais pesado 
			nodo->esq = rotacao_esq(nodo->esq);

		nodo = rotacao_dir(nodo);

	} else if (fator_balanceamento(nodo) < -1){	//lado direito desbalanceado
		if (fator_balanceamento(nodo->dir) > 0)	//lado esquerdo do filho esta desbalanceado
			nodo->dir = rotacao_dir(nodo->dir);

		nodo = rotacao_esq(nodo);
	}

	return nodo;
}

struct nodo_avl* sucessor(struct nodo_avl* nodo){
	struct nodo_avl* temp = nodo->dir;

	while (temp->esq)
		temp = temp->esq;

	return temp;
}


struct nodo_avl* remove_nodo(struct nodo_avl* nodo, int valor){
	//busca o nodo a ser removido
	if (!nodo)	//nao encontrado
		return nodo;
		
	if (valor < nodo->valor)
		nodo->esq = remove_nodo(nodo->esq, valor);
	else if (valor > nodo->valor)
		nodo->dir = remove_nodo(nodo->dir, valor);

	else {	//encontrou o nodo a ser removido
		if (!nodo->esq && !nodo->dir){	//eh uma folha
			free(nodo);
			return NULL;

		} else if(!nodo->esq ^ !nodo->dir){	//tem apenas um filho
			struct nodo_avl* temp = nodo;

			if (nodo->esq)
				nodo = nodo->esq;
			else 
				nodo = nodo->dir;
			
			free(temp);
		} else {	//tem dois filhos
			struct nodo_avl* temp = sucessor(nodo);	 	//retorna um ponteiro para o sucessor do valor

			nodo->valor = temp->valor;		//sobe o sucessor. Agora, por definicao da avl, o valor antigo tem no maximo um filho
			nodo->esq = remove_nodo(nodo->esq, valor);	//remove o valor antigo
		}
	}

	nodo->altura = altura(nodo);	//atualiza a altura do pai
	nodo = balanceia(nodo);		//balanceia apos ter retirado o filho da folha, subindo na arvore atraves da recursiva

	return nodo;
}

struct nodo_avl* inclui_folha(struct nodo_avl* nodo, int valor){
	if (!nodo)	//fim da arvore, adiciona
		return aloca_nodo(valor);

	if (valor < nodo->valor){
		nodo->esq = inclui_folha(nodo->esq, valor);	//abre como subarvore
		nodo->esq->pai = nodo;
	} else if (valor > nodo->valor){
		nodo->dir = inclui_folha(nodo->dir, valor);
		nodo->dir->pai = nodo;
	} else 
		return nodo;	//ja existe

	nodo->altura = altura(nodo);	//atualiza a altura do pai
	nodo = balanceia(nodo);	//balanceia da folha para a raiz, subindo nas subarvores atraves da recursiva

	return nodo;	//retorna pai da subarvore
}



int main(){
	struct nodo_avl* raiz = NULL;
	raiz = inclui_folha(raiz, 10);
	printf("incluiu 10\n");
	raiz = inclui_folha(raiz, 20);
	printf("incluiu 20\n");
	imprime_avl(raiz);
	raiz = inclui_folha(raiz, 15);
	printf("incluiu 15\n");
	imprime_avl(raiz);

	remove_nodo(raiz, 10);
	printf("removeu 10\n");

	imprime_avl(raiz);
	return 0;
}
