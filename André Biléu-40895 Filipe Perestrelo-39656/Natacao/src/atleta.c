/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */

#include <stdlib.h>
#include <string.h>
#include "atleta.h"

#define Y 45
#define X 40

struct _atleta{		//estrutura atleta//
	int numero;
	char *nome;
	char *clube;
	char *nomeprova;
	float tempo;
};

atleta criarAtleta(int numatleta, char *nome, char *clube, char *prova, float segundos ){		//função em que é criada uma estrutura do tipo atleta//
	atleta t = (atleta)malloc(sizeof(struct _atleta));	//alocar espaço na memoria para t (atleta)//
	if(t==NULL)
		return NULL;
	t->numero=numatleta;
		if(t->numero==0){
			destruirAtleta(t);
		}
	t->nome=(char *)malloc(sizeof(sizeof(char *)*X));	//alocar espaço na memoria para nome, clube e nomeprova (char *)//
	if (t->nome==NULL){
		free(t->numero);
		destruirAtleta(t);
	}
	strcpy(t->nome, nome);
	t->clube=(char *)malloc(sizeof(sizeof(char *)*Y));
	if(t->clube==NULL){
		free(t->nome);
		free(t->numero);
		destruirAtleta(t);
	}
	strcpy(t->clube, clube);
	t->nomeprova=(char *)malloc(sizeof(sizeof(char *)*Y));
	if(t->nomeProva==NULL){
		free(t->nome);
		free(t->numero);
		free(t->clube);
		destruirAtleta(t);
	}
	strcpy(t->nomeprova, prova);
	t->tempo=segundos;
	return t;
}

void destruirAtleta(atleta t){		//destruir variavel do tipo atleta//
	free(t);
}

int numeroAtleta(atleta t){		//retornar o numero do atleta//
	return(t->numero);
}

char* nomeAtleta(atleta t){		//retornar o nome do atleta//
	return(t->nome);
}

char* nomeClubeAtleta(atleta t){		//retornar o nome do clube do atleta//
	return(t->clube);
}

char* nomeProvaAtleta(atleta t){		//retornar o nome da prova em que o atleta participou//
	return(t->nomeprova);
}

float tempoAtleta(atleta t){		//retornar o tempo do atleta//
	return(t->tempo);
}

float tempoParaSeg(int minutos, float segundos){		//converter os dados (minutos e segundos) para segundos//
	segundos=(minutos*60)+segundos;
	return segundos;
}

void alteraTempoAtleta(float segundos, atleta t){	//Alterar o tempo de uma variável do tipo atleta//
	t->tempo=segundos;
}

int minutoAtleta(atleta t){		//retorna os minutos do tempo do atleta( que se encontra em segundos)//
	int minutos;
	minutos=(t->tempo)/60;
	return minutos;
}

float segundoAtleta(atleta t){		//retorna os segundos do tempo do atleta//
	float segundos;
	segundos=(((int)t->tempo)%60)*60;
	segundos=(t->tempo)-((int)t->tempo);
	return segundos;
}

int comparaTempo(float tempseg, atleta t){		//compara dois tempos(olimpico e o do atleta) retorna 1 (caso tempo do atleta seja menor que o olimpico//
	if(tempseg>t->tempo)
		return 1;
	else
		return 0;
}
