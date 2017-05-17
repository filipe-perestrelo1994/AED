/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */

#include <stdlib.h>

#include "atleta.h"
#include "atletaGen.h"

void destroiGenAtleta(void * a){
	destruirAtleta((atleta) a);
}

void * chaveGenAtleta (void * a){		//gera uma chave para variaveis do tipo atleta//
	int * num = (int *)malloc(sizeof(int *));
	if(num==NULL)
		free(a);
	num=numeroAtleta(a);
	return (void *) num;
}


