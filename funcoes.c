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
	return;
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
	//verifica se o ponteiro eh null para retornar sua altura
	if (!nodo)
		return -1;
	else
		return nodo->altura;
}

int maior(int esq, int dir){	//evita que a altura tenha q ser calculada toda vez
	if (esq > dir)
		return esq;
	else
		return dir;
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
	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;
	nodo2->altura = maior(altura(nodo2->esq), altura(nodo2->dir)) + 1;

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
	nodo->altura = maior(altura(nodo->esq), altura(nodo->dir)) + 1;
	nodo2->altura = maior(altura(nodo2->esq), altura(nodo2->dir)) + 1;

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

struct nodo_avl* insere_nodo(struct nodo_avl* nodo, int valor){
	if (!nodo)	//fim da arvore, adiciona
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



int main(){
	struct nodo_avl* raiz = NULL;
	raiz = insere_nodo(raiz, 10);
	printf("incluiu 10\n");
	raiz = insere_nodo(raiz, 20);
	printf("incluiu 20\n");
	imprime_avl(raiz);
	raiz = insere_nodo(raiz, 15);
	printf("incluiu 15\n");
	imprime_avl(raiz);

	raiz = remove_nodo(raiz, 15);
	printf("removeu 15\n");

	imprime_avl(raiz);
	return 0;
}
