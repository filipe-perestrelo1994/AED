/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */
#include "atletaGen.h"
#include "iterador.h"
#include <stdlib.h>
#include "dicionario.h"
#include "chaves.h"


/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos nÃ£o podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario{
	void * * elems; // apontador para vector de enderecos de elementos
	int numElems;
	int capacidade;
	int tipoCh; // 0-inteiro; 1-string
	void * (*chave)(void *); // endereco da funcao que da a chave dum elemento
};

/* Prototipos das funcoes associadas a um dicionario */

/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
     cap - capacidade prevista do dicionario
     chave â funÃ§Ã£o que retorna o endereÃ§o de uma cÃ³pia da chave do elemento
     TipoChave â 0 â inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
dicionario criaDicionario(int cap, void * (* chave)(void *), int tipoChave){
	dicionario d;
	d = (dicionario) malloc(sizeof(struct _dicionario));
	if ( d == NULL) return NULL;
	d->elems = malloc(sizeof(void *) * cap);
	if (d->elems == NULL){
		free(d);
		return NULL;
	}
	d->numElems = 0;
	d->capacidade = cap;
	d->tipoCh =tipoChave;
	d->chave = chave;
	return d;
}

/***********************************************
destroiDicionario - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario.
Parametros:	d - dicionario a destruir
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicionario (dicionario d ){
	free(d->elems);
	free(d);
}

/***********************************************
destroiDicEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - funÃ§Ã£o para destruiÃ§Ã£o os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicEElems(dicionario d, void (*destroi)(void *) ){
	int i;
	for(i=0;i < d->numElems;i++)
		destroi(d->elems[i]);
	free(d->elems);
	free(d);
}

/***********************************************
vazioDicionario - Indica se o dicionario estÃ¡ vazio.
Parametros:
	d - dicionario
Retorno: 1- caso dicionario vazio; 0 - caso contrÃ¡rio
Pre-condicoes: d != NULL
***********************************************/
int vazioDicionario(dicionario d){
	if (d->numElems == 0)
		return 1;
	return 0;
}

/***********************************************
tamanhoDicionario - Consulta o numero de elementos no dicionario.
Parametros:
	d - dicionario
Retorno: numero de elementos no dicionario
Pre-condicoes: d != NULL
***********************************************/
int tamanhoDicionario(dicionario d){
	return d->numElems;
}
/* FunÃ§Ã£o para calcular a posiÃ§Ã£o dum dado elemento no vector */
int posElemDicionario(dicionario d, void * ch){
	int i;
	void * auxch;
	for (i = 0; i<d->numElems;i++){
		auxch =d->chave(d->elems[i]);
		if (igualChaves(ch,auxch,d->tipoCh) == 1){
			free(auxch);
			return i;
		}
		free(auxch);
	}
	return -1;
}
/***********************************************
existeElemDicionario â Indica se o elemento  com a chave dada existe no dicionario.
Parametros:
	d â dicionario
	ch â endereÃ§o da chave do elemento
Retorno: retorna 1 se existir, e 0, caso contrÃ¡rio
Pre-condicoes: d != NULL
***********************************************/
int existeElemDicionario(dicionario d, void * ch){
	if (posElemDicionario(d,ch) != -1)
		return 1;
	return 0;
}

/***********************************************
elementoDicionario - retorna o elemento no dicionario com a chave dada
Parametros:
	d â dicionario	ch - endereco da chave do elemento
Retorno: retorna o elemento
Pre-condicoes: d != NULL
***********************************************/
void * elementoDicionario(dicionario d, void * ch){
	int pos = posElemDicionario(d,ch);
	if (pos != -1)
		return d->elems[pos];
	return NULL;
}
/* Aumenta o vector do dicionario */
void incDicionario (dicionario d){
	int i = 0;
	void ** aux = malloc(sizeof(void * ) * d->capacidade*2); // duplica
	for (;i<d->numElems;i++)
		aux[i] = d->elems[i];
	free(d->elems);
	d->elems = aux;
	d->capacidade = d->capacidade * 2;
}

/***********************************************
adicionaElemDicionario - Adiciona o elemento dado no dicionario, se nÃ£o existir um elemento com a mesma chave.
Parametros:
	d â dicionario
	elem - endereco do elemento
Retorno: Retorna 1 se adicionar, e 0, caso contrÃ¡rio
Pre-condicoes: d != NULL
***********************************************/
int adicionaElemDicionario(dicionario d, void * elem){
	int pos;
	void * auxch =d->chave(elem);
	pos = posElemDicionario(d,auxch);
	free(auxch);
	if (pos != -1)
		return 0;
	if (d->numElems == d->capacidade)
		incDicionario(d);
	d->elems[d->numElems++] = elem;
	return 1;
}

/***********************************************
removeElemDicionario - Remove o elemento com a chave dada no dicionario, se existir.
Parametros:
	d â dicionario	ch â endereco da chave
Retorno: Retorna o elemento, caso exista ou NULL, caso contrario
Pre-condicoes: d != NULL
***********************************************/
void * removeElemDicionario(dicionario d, void * ch){
	void * elem;
	int pos = posElemDicionario(d,ch);
	if (pos == -1)
		return NULL;
	elem = d->elems[pos];
	d->elems[pos] = d->elems[--d->numElems];
	return elem;
}

/***********************************************
iteradorDicionario - Cria e devolve um iterador para o dicionario.
Parametros:
d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorDicionario(dicionario d){
	return criaIterador(d->elems,d->numElems);
}
