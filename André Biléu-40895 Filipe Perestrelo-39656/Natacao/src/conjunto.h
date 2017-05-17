/**********
 * conjunto.h
 */

#ifndef _H_CONJUNTO
#define _H_CONJUNTO

/* Tipo de dados: conjunto ---> os elementos não podem ser repetidos com base numa função de igualdade.*/
typedef struct _conjunto * conjunto;

/* Prototipos das funcoes associadas a um conjunto */

/***********************************************
criaConjunto - Criacao da instancia da estrutura associada a um conjunto.
Parametros:
     cap - capacidade prevista do conjunto
     igual – função de igualdade de elementos (retorna 1 se iguais, 0 caso contrario
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
conjunto criaConjunto(int cap, int (* igual)(void *, void *));

/***********************************************
destroiConjunto - Liberta a memoria ocupada pela instancia da estrutura associada ao conjunto.
Parametros:	c - conjunto a destruir
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroiConjunto (conjunto c );

/***********************************************
destroiConjEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao conjunto e os elementos.
Parametros:
	c - conjunto a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroiConjEElems(conjunto c, void (*destroi)(void *) );

/***********************************************
vazioConjunto - Indica se o conjunto está vazio.
Parametros:
	c - conjunto
Retorno: 1- caso conjunto vazio; 0 - caso contrário
Pre-condicoes: c != NULL
***********************************************/
int vazioConjunto(conjunto c);

/***********************************************
tamanhoConjunto - Consulta o numero de elementos no conjunto.
Parametros:
	c - conjunto
Retorno: numero de elementos no conjunto

Pre-condicoes: c != NULL
***********************************************/
int tamanhoConjunto(conjunto c);

/***********************************************
existeElemConjunto – Indica se o elemento existe no conjunto.
Parametros:
c – conjunto
e – endereço do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: c != NULL
***********************************************/
int existeElemConjunto(conjunto c, void * e);

/***********************************************
adicionaElemConjunto - Adiciona o elemento dado no conjunto,caso exista.
Parametros:
	c – conjunto
	elem - endereco do elemento
Retorno: retorna 1 se adicionar e 0, caso contrário
Pre-condicoes: c != NULL
***********************************************/
int adicionaElemConjunto(conjunto c, void * elem);

/***********************************************
removeElemConjunto - Remove o elemento no conjunto, caso exista.
Parametros:
	c – conjunto
	elem - elemento
Retorno: Retorna o elemento, caso exista, ou NULL caso contrário
Pre-condicoes: c != NULL
***********************************************/
void * removeElemConjunto(conjunto c, void * elem);

/***********************************************
iteradorConjunto - Cria e devolve um iterador para o conjunto.
Parametros:
c - conjunto
Retorno: iterador do conjunto
Pre-condicoes: c != NULL && vazioConjunto(c)!=1
***********************************************/
iterador iteradorConjunto(conjunto c);

#endif
