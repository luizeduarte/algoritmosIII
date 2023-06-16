#include <stdio.h>

void imprime_hash(int* T1, int* T2){
	for (int i = 0; i < 11; i++)
		if (T1[i] > 0)
			printf("%d,T1,%d", T1[i], i + 1);
	
	for (int i = 0; i < 11; i++)
		if (T2[i] > 0)
			printf("%d,T2,%d", T2[i], i + 1);

	return;
}

int* busca_hash(int chave, int* T1, int* T2){
	int pos1 = h1(chave);	//gera a localizacao na tabela da chave
	if (T1[pos1] == 0)	//chave nao existe
		return NULL;
	
	if (T1[pos1] == chave)	//chave esta na primeira tabela
		return &T1[pos1];
	
	else {
		int pos2 = h2(chave);	//gera a localizacao na segunda tabela da chave
		if (T2[pos2] == chave)	//chave esta na segunda tabela
			return &T2[pos2];
		
		return NULL;	//chave nao existe
	}
}

int* insere_hash(int chave, int* T1, int* T2){
	int pos1 = h1(chave);	//gera a localizacao na tabela da nova chave
	if (T1[pos1] < 1){	//se o lugar estiver vago, insere a chave
		T1[pos1] = chave;
		return &T1[pos1];
	}

	int pos2 = h2(T1[pos1]);	//se nao, gera a posicao na segunda tabela da chave que estava na primeira
	T2[pos2] = T1[pos1];		//insere a chave antiga na segunda tabela
	T1[pos1] = chave;		//insere a nova chave na primeira tabela

	return &T1[pos1];		//retorna a posicao da nova chave
}

int* remove_hash(int chave, int* T1, int* T2){
	int pos2 = h2(chave);		//gera a posicao na segunda tabela da chave que sera excluida

	if (T2[pos2] == chave){		//se a chave estiver na segunda tabela, exclui ela
		T2[pos2] = 0;
		return &T2[pos2];
	}

	int pos1 = h1(chave);		//se nao, gera a posicao na primeira tabela
	if (T1[pos1] == chave){		
		if (T2[pos2] > 0)	//se a chave estiver na primeira tabela e a segunda nao estiver vazia, marca como excluido
			T1[pos1] = -1;
		else 
			T1[pos1] = 0;		//se a segunda tabela estiver vazia, exclui a chave

		return &T1[pos1];
	}

	return NULL;
}

int main(){
	char op;
	int valor;
	int T1[11], T2[11];

	while (scanf("%c %d", &op, &valor) != EOF){
		if (op == 'i')
			insere_hash(valor, T1, T2);
		else if (op == 'b')
			busca_hash(valor, T1, T2);
		else if (op == 'e')
			remove_hash(valor, T1, T2);
	}
	imprime_hash(T1, T2);
	return 0;
}
