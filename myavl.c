#include <stdio.h>
#include "manipula_avl.h"
#include "insere_avl.h"
#include "remove_avl.h"

int main(){
	char op;
	int valor;
	struct nodo_avl* raiz = NULL;	//inicializa a arvore

	while (scanf("%c %d\n", &op, &valor) != EOF){
		if (op == 'i')
			raiz = insere_nodo(raiz, valor);
		else if (op == 'r')
			raiz = remove_nodo(raiz, valor);
		else
			printf("operacao invalida\n");
	}

	imprime_avl(raiz);
	desaloca_avl(raiz);
	return 0;
}