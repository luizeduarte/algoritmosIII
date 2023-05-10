#ifndef _MANIPULA_AVL_H_
#define _MANIPULA_AVL_H_

struct nodo_avl{	//estrutura dos nodos quem compoem a arvore
	int valor, altura;
	struct nodo_avl *esq, *dir, *pai;
};

void desaloca_avl(struct nodo_avl* nodo);
void imprime_avl(struct nodo_avl *nodo);	//de maneira "in order"

//recebe um nodo e verifica se ele eh null, retornando -1, ou se existe e pode ser acessada sua altura
int altura(struct nodo_avl* nodo);

//recebe dois inteiros e retorna o maior
int maior(int esq, int dir);

//desce o nodo passado como argumento e sobe seu filho, alterando a altura dos nodos e mantendo a propriedade de arvore binaria
struct nodo_avl* rotacao_dir(struct nodo_avl* nodo);
struct nodo_avl* rotacao_esq(struct nodo_avl* nodo);

//calcula o fator de balanceamento, sendo a altura do nodo da esquerda menos a do nodo da direita
int fator_balanceamento(struct nodo_avl* nodo);

//balanceia a avl a partir do nodo passado, verificando qual lado esta desbalanceado e fazendo as rotacoes necessarias
struct nodo_avl* balanceia(struct nodo_avl* nodo);

#endif
