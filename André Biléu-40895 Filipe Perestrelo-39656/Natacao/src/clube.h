/*
 * clube.h
 *
 *  Created on: 13 de Mai de 2013
 *      Author: f.perestrelo
 */

#ifndef CLUBE_H_
#define CLUBE_H_

typedef struct _clube * clube;

clube criaClube(int nAtletasOlimpicos, char* nomeclube);

void destroiClube(clube c);

int numAtletasOlimpicosClube(clube c);

int existemAtletasOlimpicos(clube c);

void incNumAtletasOlimpicos(clube c);



#endif /* CLUBE_H_ */
