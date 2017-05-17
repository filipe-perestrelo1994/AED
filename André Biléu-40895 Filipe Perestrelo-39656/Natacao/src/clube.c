#include "clube.h"
#include "conjunto.h"
#include <string.h>
#define X 50

struct _clube{
	char * nome;
	conjunto atletasOlimpicosClube;
};

clube criaClube(char * nomeclube){
	char * nomeclube;
	clube c = (clube)malloc(sizeof(struct _clube));
	if(c==NULL) return NULL;
	c->nome=(char *)malloc(sizeof(sizeof(char *)*X));
	if (c->nome==NULL){
		destroiClube(c);
	}
	strcpy(c->nome, nomeclube);
	c->atletasOlimpicosClube=(conjunto)malloc(sizeof(struct _conjunto));
	if(c->atletasOlimpicosClube==NULL){
		free(c->nome);
		free(c);
	}
	c->nAtletas=tamanhoConjunto(c->atletasOlimpicosClube);
	return c;
}

void destroiClube(clube c){
	free(c->nome);
	destroiConjunto(c->atletasOlimpicosClube);
	free(c);
}


void incAtletasOlimpicos(clube c){
		c->nAtletasOlimpicos++;
}

int existemAtletasOlimpicos(clube c){
	if (tamanhoConjunto(c->atletasOlimpicosClube)!=0)
		return 1;
	else return 0;

}

int numeroAtletasOlimpicosClube(clube c){
	int nAtletas=tamanhoConjunto(c->atletasOlimpicosClube);
	return nAtletas;
}

void adicionaElemClube(clube c, atleta t){
	adicionaElemConjunto(c->atletasOlimpicos, (void*) t);
}

conjunto atletasOlimpicosClube(clube c){
	return c->atletasOlimpicosClube;
}