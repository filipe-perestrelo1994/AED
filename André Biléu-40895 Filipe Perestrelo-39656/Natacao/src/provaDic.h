/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */

#ifndef PROVADIC_H_
#define PROVADIC_H_


typedef struct _prova * prova;

/*criaProva - Reserva espaço na memoria para uma instancia da estrutura do tipo prova e
inicializa os seus valores.
Parâmetros:
Retorna: uma instancia do tipo prova
Pré-condições: */

prova criaProva();


/*destroiProva - Liberta espaço na memoria de uma instancia da estrutura do tipo prova
Parâmetros: prova;
Retorna:
Pré-condições: */

void destroiProva(prova p);


/*destroiProvaEAtletas - Liberta espaço na memoria de uma instancia da estrutura do tipo prova e dos seus elementos (atletas)
Parâmetros: prova;
Retorna:
Pré-condições:*/

void destroiProvaEAtletas(prova p);


/*guardarRegistos - guarda a distância e o estilo, introduzidos, na prova
Parâmetros: prova
			distancia em metros
			estilo de natação;
Retorna:
Pré-condições: prova p!=NULL */

void guardarRegistos(prova p, int metros, char *estilo);


/*tempoOlimpico - guarda o tempo olímpico, introduzido, em segundos, na prova
Parâmetros: prova;
Retorna:
Pré-condições: p!= NULL */

void tempoOlimpico(prova p, int tempseg);

/*existeNumAtleta - Indica se existe um atleta, com o numero introduzido, na prova
Parâmetros: prova
			numero do "possível" atleta;
Retorna: 0 caso exista e 1 caso nao exista
Pré-condições: p!= NULL */

int existeNumAtleta(prova p,int num);


void atletaOlimpico(atleta t);


#endif
