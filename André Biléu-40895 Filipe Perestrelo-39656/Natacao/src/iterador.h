/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */

#ifndef ITERADOR_H_
#define ITERADOR_H_

typedef struct _iterador * iterador;

iterador criaIterador(void ** vector, int n);

void destroiIterador (iterador it);

int temSeguinteIterador(iterador it);

void * seguinteIterador(iterador it);

#endif /* ITERADOR_H_ */
