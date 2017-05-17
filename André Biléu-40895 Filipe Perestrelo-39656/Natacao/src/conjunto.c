/*
 * cjtoListaSimples.c
 */

#include <stdlib.h>
#include "iterador.h"
#include "conjunto.h"

#include "noSimples.h"

/*  Estrutura de dados do tipo de dados: conjunto ---> os elementos não podem ser repetidos com base numa função de igualdade */
struct _conjunto{
	noSimples cabeca;
	noSimples cauda;
	int numElems;
	int (*iguais)(void *, void *); // endereco da funcao de igualdade de elementos
};

/* Prototipos das funcoes associadas a um conjunto */

/***********************************************
criaConjunto - Criacao da instancia da estrutura associada a um conjunto.
Parametros:
     cap - capacidade prevista do conjunto
     igual – função de igualdade de elementos (retorna 1 se iguais, 0 caso contrario
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
conjunto criaConjunto(int cap, int (* igual)(void *, void *)){
	conjunto c;
	c = (conjunto) malloc(sizeof(struct _conjunto));
	if ( c == NULL) return NULL;
	c->cabeca = NULL;
	c->cauda = NULL;
	c->numElems = 0;
	c->iguais = igual;
	return c;
}

/***********************************************
destroiConjunto - Liberta a memoria ocupada pela instancia da estrutura associada ao conjunto.
Parametros:	c - conjunto a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroiConjunto (conjunto c ){
	noSimples  aux = c->cabeca;
	while (aux != NULL){
		c->cabeca = segNoSimples(aux);
		destroiNoSimples(aux);
		aux = c->cabeca;
	}
	free(c);
}

/***********************************************
destroiConjEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao conjunto e os elementos.
Parametros:
	c - conjunto a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroiConjEElems(conjunto c, void (*destroi)(void *) ){
	noSimples  aux = c->cabeca;
	while (aux != NULL){
		c->cabeca = segNoSimples(aux);
		destroiElemENoSimples(aux,destroi);
		aux = c->cabeca;
	}
	free(c);
}

/***********************************************
vazioConjunto - Indica se o conjunto está vazio.
Parametros:
	c - conjunto
Retorno: 1- caso conjunto vazio; 0 - caso contrário
Pre-condicoes: c != NULL
***********************************************/
int vazioConjunto(conjunto c){
	if (c->numElems == 0)
		return 1;
	return 0;
}

/***********************************************
tamanhoConjunto - Consulta o numero de elementos no conjunto.
Parametros:
	c - conjunto
Retorno: numero de elementos no conjunto
Pre-condicoes: c != NULL
***********************************************/
int tamanhoConjunto(conjunto c){
	return c->numElems;
}


/***********************************************
existeElemConjunto – Indica se o elemento existe no conjunto.
Parametros:
c – conjunto
e – endereço do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: c != NULL
***********************************************/
int existeElemConjunto(conjunto c, void * e){
	noSimples aux = c->cabeca;
	while (aux != NULL){
		if (c->iguais(elemNoSimples(aux),e) == 1)
		return 1;
		aux = segNoSimples(aux);
	}
	return 0;
}

/***********************************************
adicionaElemConjunto - Adiciona o elemento dado no conjunto,caso exista.
Parametros:
	c – conjunto
	elem - endereco do elemento
Retorno: retorna 1 se adicionar e 0, caso contrário
Pre-condicoes: c != NULL
***********************************************/
int adicionaElemConjunto(conjunto c, void * elem){
	noSimples aux;
	if (existeElemConjunto(c,elem) == 1)
		return 0;
	aux = criaNoSimples(elem,c->cabeca);
	c->cabeca = aux;
	if (c->numElems == 0)
		c->cauda = aux;
	c->numElems++;
	return 1;
}

/***********************************************
removeElemConjunto - Remove o elemento no conjunto, caso exista.
Parametros:
	c – conjunto
	elem - elemento
Retorno: Retorna o elemento caso exista, ou NULL caso contrário
Pre-condicoes: c != NULL
***********************************************/
void * removeElemConjunto(conjunto c, void * elem){
	void * e = NULL;
	noSimples antAux = NULL;
	noSimples aux = c->cabeca;
	while ((aux != NULL) && (c->iguais(elem,elemNoSimples(aux)) != 1)){
		antAux = aux;
		aux = segNoSimples(aux);
	}
	if (aux == NULL) // nao encontrou
		return NULL;
	e = elemNoSimples(aux);
	if (antAux == NULL){ // elemento na cabeca da lista ligada
		c->cabeca = segNoSimples(aux);
		if (c->numElems == 1) // unico elemento
			c->cauda = NULL;
	}
	else{ // elemento no meio ou na cauda da lista ligada
		atribuiSegNoSimples(antAux,segNoSimples(aux));
		if (aux == c->cauda) // elemento na cauda da lista ligada
			c->cauda = antAux;
	}
	destroiNoSimples(aux);
	c->numElems--;
	return e;
}

/***********************************************
iteradorConjunto - Cria e devolve um iterador para o conjunto.
Parametros:
c - conjunto
Retorno: iterador do conjunto
Pre-condicoes: c != NULL && vazioConjunto(c)!=1
***********************************************/
iterador iteradorConjunto(conjunto c){
	return criaIteradorListaSimples((void *)c->cabeca);
}

