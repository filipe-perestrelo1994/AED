/*
 * iterador.c
 *
 *  Created on: 7 de Mai de 2013
 *      Author: António
 */

#include <stdlib.h>
# include "iterador.h"
#include "noSimples.h"

// estrutura de dados necessária para iterador de vector
struct _itVector{
	void ** vector;
	int corrente;
	int numElems;
};
// estrutura de dados necessária para iterador de lista ligada
struct _itNoSimples{
	noSimples primeiro;
	noSimples corrente;
};
// estrutura de dados necessária para iterador de tabela de dispersão
struct _itTabDis{
	void ** vector;
	int tamanho;
	int posCor, posPri;
	noSimples corrente;
};


struct _iterador{
	int tipo; // 0- em vector; 1- em lista ligada simples; 2 - tabela de dispersão
	union _ed{
		struct _itVector itV; // serve para  vector
		struct _itNoSimples itLS; // serve para lista ligada simples
		struct _itTabDis itTD; // serve para a tabela de dispersão
	} itED;
};

/* Prototipos das funcoes associadas a um iterador */

/***********************************************
criaIterador - Criacao da instancia da estrutura associada a um iterador para um vector com n elementos.
Parametros:
	vector - endereco do vector a iterar
	n - numero de elementos no vector
Retorno: apontador para a  instancia criada
Pre-condicoes:  vector != NULL && n > 0
***********************************************/
iterador criaIteradorVector(void ** vector, int n){
	iterador it = malloc(sizeof(struct _iterador));
	if (it == NULL) return NULL;
	it->tipo = 0;
	it->itED.itV.numElems = n;
	it->itED.itV.vector = vector;
	it->itED.itV.corrente = 0;
	return it;
}

/***********************************************
criaIterador - Criacao da instancia da estrutura associada a um iterador para uma lista ligada simples com n elementos.
Parametros:
	no - endereco do primeiro nó
	n - numero de elementos no vector
Retorno: apontador para a  instancia criada
Pre-condicoes:  no != NULL && n > 0
***********************************************/
iterador criaIteradorListaSimples(void * no){
	iterador it = malloc(sizeof(struct _iterador));
	if (it == NULL) return NULL;
	it->tipo = 1;
	it->itED.itLS.primeiro = no;
	it->itED.itLS.corrente = no;
	return it;
}

/***********************************************
criaIterador - Criacao da instancia da estrutura associada a um iterador para uma tabela de dispersão com tamanho tam.
Parametros:
	vector - endereco da tabela de dispersão
	tam - tamanho da tabela de dispersão
Retorno: apontador para a  instancia criada
Pre-condicoes:  vector != NULL && n > 0
***********************************************/
iterador criaIteradorTabDispersao(void* * vector, int tam){
	int i;
	iterador it = malloc(sizeof(struct _iterador));
	if (it == NULL) return NULL;
	it->itED.itTD.vector = vector;
	it->tipo = 2;
	it->itED.itTD.tamanho = tam;
	it->itED.itTD.posCor=0;
	for(i=0;i<tam && it->itED.itTD.vector[i]==NULL;i++);
	if(i==tam){
		it->itED.itTD.corrente = NULL;
		it->itED.itTD.posCor = tam;
		it->itED.itTD.posPri = tam;
	}
	else{
		it->itED.itTD.posCor=i;
		it->itED.itTD.posPri=i;
		it->itED.itTD.corrente = it->itED.itTD.vector[it->itED.itTD.posCor];
	}
	return it;
}

/***********************************************
destroiIterador - Liberta a memoria ocupada pela instancia da estrutura associada ao iterador.
Parametros:
	it - iterador a destruir
Retorno:
Pre-condicoes: it != NULL
***********************************************/
void destroiIterador (iterador it){
	free(it);
}

/***********************************************
temSeguinteIterador - Indica se existe mais elementos para iterar no iterador.
Parametros:
	it - iterador
Retorno: 1- caso exista mais elementos; 0- caso contrario
Pre-condicoes: it != NULL
***********************************************/
int temSeguinteIterador(iterador it){
	if ((it->tipo == 0) && (it->itED.itV.corrente == it->itED.itV.numElems))
		return 0;
	if ((it->tipo == 1) && (it->itED.itLS.corrente == NULL))
		return 0;
	if((it->tipo == 2) && (it->itED.itTD.corrente == NULL))
		return 0;
	return 1;
}

/***********************************************
seguinteIterador - Consulta o seguinte elemento no iterador.
Parametros:
	it - iterador
Retorno: endereco do elemento
Pre-condicoes: it != NULL && temSeguinteIterador(it) == 1
***********************************************/
void * seguinteIterador(iterador it){
	void * elem = NULL;
	int i;
	switch (it->tipo){
		case 0:{
			elem = it->itED.itV.vector[it->itED.itV.corrente++];
			break;
		}
		case 1:{
			elem = elemNoSimples(it->itED.itLS.corrente);
			it->itED.itLS.corrente = segNoSimples(it->itED.itLS.corrente);
			break;
		}
		case 2:{
			elem = elemNoSimples(it->itED.itTD.corrente);
			if(segNoSimples(it->itED.itTD.corrente)!=NULL){
				it->itED.itTD.corrente = segNoSimples(it->itED.itTD.corrente);
			}
			else{
				for(i=it->itED.itTD.posCor+1;i<it->itED.itTD.tamanho && it->itED.itTD.vector[i]==NULL;i++);
				if(i==it->itED.itTD.tamanho){
					it->itED.itTD.corrente = NULL;
					it->itED.itTD.posCor = i;
					it->itED.itTD.posPri = i;
				}
				else{
					it->itED.itTD.posCor=i;
					it->itED.itTD.posPri=i;
					it->itED.itTD.corrente = it->itED.itTD.vector[it->itED.itTD.posCor];
				}
			}
			break;
		}
	}
	return elem;
}

/***********************************************
iniciaIterador - coloca o iterador no início da iteração.
Parametros:
	it - iterador
Retorno:
Pre-condicoes: it != NULL
***********************************************/
void iniciaIterador(iterador it){
	if (it->tipo == 0)
		it->itED.itV.corrente = 0;
	else
		if(it->tipo == 1)
			it->itED.itLS.corrente = it->itED.itLS.primeiro;
		else
			if (it->tipo == 2){
				it->itED.itTD.posCor = it->itED.itTD.posPri;
				it->itED.itTD.corrente = it->itED.itTD.vector[it->itED.itTD.posPri];
			}
}


