/*
 * dicTabDis.c
 *
 *  Created on: 12 de Mai de 2013
 *      Author: António
 */

#include <stdlib.h>

#include "iterador.h"
#include "dicionario.h"
#include "chaves.h"
#include "noSimples.h"


/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos não podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario{
	void * * elems; // apontador para vector de noSimples (tipo void *)
	int numElems;
	int capacidade; // capacidade prevista
	int tamanho; // tamanho do vector criado
	int tipoCh; // 0-inteiro; 1-string
	void * (*chave)(void *); // endereco da funcao que da a chave dum elemento
};

/* Prototipos das funcoes associadas a um dicionario */

/* fun??o auxiliar para calcular o seguinte primo */
int segPrimo(int n){
	int k=n,m=0,i;
	while(1){
		k++;m=0;
		for(i=1;i<10;i++){
			if((k%i)==0)m++;
		}
		if(k>9){
			if(m==1)return k;
		}
		else{
			if(m==2)return k;
		}
	}
	return 0;
}



/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
     cap - capacidade prevista do dicionario
     chave – função que retorna o endereço de uma cópia da chave do elemento
     TipoChave – 0 – inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
dicionario criaDicionario(int cap, void * (* chave)(void *), int tipoChave){
	dicionario d;
	int i;
	d = (dicionario) malloc(sizeof(struct _dicionario));
	if ( d == NULL) return NULL;
	d->tamanho = segPrimo(2*cap);
	d->elems = (void **)malloc(sizeof(void *) * d->tamanho);
	if (d->elems == NULL){
		free(d);
		return NULL;
	}
	for (i=0;i<d->tamanho;i++)
		d->elems[i] = NULL;
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
	int i = 0;
	noSimples  aux;
	for(;i<d->tamanho;i++){
		aux = d->elems[i];
		while (aux != NULL){
			d->elems[i] = segNoSimples(aux);
			destroiNoSimples(aux);
			aux = d->elems[i];
		}
	}
	free(d);
}

/***********************************************
destroiDicEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicEElems(dicionario d, void (*destroi)(void *) ){
	int i = 0;
	noSimples  aux;
	for(;i<d->tamanho;i++){
		aux = d->elems[i];
		while (aux != NULL){
			d->elems[i] = segNoSimples(aux);
			destroiElemENoSimples(aux,destroi);
			aux = d->elems[i];
		}
	}
	free(d);
}

/***********************************************
vazioDicionario - Indica se o dicionario está vazio.
Parametros:
	d - dicionario
Retorno: 1- caso dicionario vazio; 0 - caso contrário
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
/***********************************************
existeElemDicionario – Indica se o elemento  com a chave dada existe no dicionario.
Parametros:
	d – dicionario
	ch – endereço da chave do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int existeElemDicionario(dicionario d, void * ch){
	if (elementoDicionario(d,ch) != NULL)
		return 1;
	return 0;
}

/***********************************************
elementoDicionario - retorna o elemento no dicionario com a chave dada
Parametros:
	d – dicionario	ch - endereco da chave do elemento
Retorno: retorna o elemento
Pre-condicoes: d != NULL
***********************************************/
void * elementoDicionario(dicionario d, void * ch){
	void * auxCh;
	void * elem;
	noSimples auxNo;
	int pos = dispersao(ch,d->tamanho,d->tipoCh);
	auxNo = d->elems[pos];
	while (auxNo != NULL){
		elem = elemNoSimples(auxNo);
		auxCh = d->chave(elem);
		if (igualChaves(auxCh, ch,d->tipoCh) == 1){
			free(auxCh);
			return elem;
		}
		free(auxCh);
		auxNo = segNoSimples(auxNo);
	}
	return NULL;
}

/***********************************************
adicionaElemDicionario - Adiciona o elemento dado no dicionario, se não existir um elemento com a mesma chave.
Parametros:
	d – dicionario
	elem - endereco do elemento
Retorno: Retorna 1 se adicionar, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int adicionaElemDicionario(dicionario d, void * elem){
	int pos;
	noSimples auxNo;
	void * auxch =d->chave(elem);
	if (existeElemDicionario(d,auxch) == 1){
		free(auxch);
		return 0;
	}
	pos = dispersao(auxch,d->tamanho,d->tipoCh);
	//adicionar na cabe?a da lista ligada simples d->elems[pos]
	auxNo = criaNoSimples(elem,d->elems[pos]);
	d->elems[pos] = auxNo;
	d->numElems++;
	free(auxch);
	return 1;
}

/***********************************************
removeElemDicionario - Remove o elemento com a chave dada no dicionario, se existir.
Parametros:
	d – dicionario	ch – endereco da chave
Retorno: Retorna o elemento, caso exista ou NULL, caso contrario
Pre-condicoes: d != NULL
***********************************************/
void * removeElemDicionario(dicionario d, void * ch){
	void * elem = NULL;
	void * auxCh;
	noSimples auxNo, antNo = NULL;
	int pos = dispersao(ch,d->tamanho,d->tipoCh);
	auxNo = d->elems[pos];
	if (auxNo == NULL)
		return NULL;
	//procurar elemento e remover da lista d->elems[pos]
	while (auxNo != NULL){
		elem = elemNoSimples(auxNo);
		auxCh = d->chave(elem);
		if (igualChaves(auxCh, ch,d->tipoCh) == 1){
			free(auxCh);
			if (antNo == NULL){
				d->elems[pos]=segNoSimples(auxNo);
			}
			else{
				atribuiSegNoSimples(antNo,segNoSimples(auxNo));
			}
			d->numElems--;
			destroiNoSimples(auxNo);
			return elem;
		}
		free(auxCh);
		antNo=auxNo;
		auxNo=segNoSimples(auxNo);
	}
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
	return criaIteradorTabDispersao(d->elems,d->tamanho);
}



