struct nodo_avl{
	int valor, altura;
	struct nodo_avl *esq, *dir, *pai;
};

void desaloca_avl(struct nodo_avl* nodo);
void imprime_avl(struct nodo_avl *nodo);
int altura(struct nodo_avl* nodo);
int maior(int esq, int dir);
struct nodo_avl* rotacao_dir(struct nodo_avl* nodo);
struct nodo_avl* rotacao_esq(struct nodo_avl* nodo);
int fator_balanceamento(struct nodo_avl* nodo);
struct nodo_avl* balanceia(struct nodo_avl* nodo);