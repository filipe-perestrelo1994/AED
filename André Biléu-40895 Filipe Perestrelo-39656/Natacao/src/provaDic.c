#include <stdlib.h>
#include <string.h>
#include "noSimples.h"
#include "atletaGen.h"
#include "iterador.h"
#include "atleta.h"
#include "provaDic.h"
#include "dicionario.h"
#include "conjunto.h"
#include "clube.h"
#include "tempo.h"


#define CAP 25

struct _prova{					//estrutura prova//
	dicionario atletas;
	int comprimento;
	char *estilo;
	float tempoolimpico;
	conjunto atletasOlimpicos;
	dicionario clubes;
};

prova criaProva(){						//função em que é criada uma estrutura do tipo prova//
	prova p = (prova)malloc(sizeof(struct _prova));		//alocar espaço na memoria para p (prova)//
	if (p==NULL) return NULL;
	p->atletas = criaDicionario(CAP,chaveGenAtleta,0);	//cria o dicionario de atletas da estrutura prova//
	if (p->atletas==NULL){
		free(p);
		return NULL;
	}
	p->comprimento=0;
	p->estilo=(char *) malloc(sizeof(sizeof(char *)*CAP));	//alocar espaço na memoria para estilo (char *)//
	P->estilo=NULL;
	p->tempoolimpico=0;
	p->atletasOlimpicos=criaConjunto(CAP, );
	if (p->atletasOlimpicos==NULL){
		destroiDicionario(p->atletas);
		free(p->estilo);
		free(p);
	}
	p->clube = criaDicionario(CAP,chaveGenClube,0);
	if(p->clube==NULL){
		free(p->estilo);
		free(p->atletasOlimpicos);
		free(p);
	}
	return p;
}

void destroiProva(prova p){		//destruir prova//
	destroiDicionario(p->atletas); //destruir dicionario de atletas//
	free (p->estilo);
	free(p);		//libertar prova p//
}

void destroiProvaEAtletas(prova p){		//destruir prova e atletas//
	destroiDicEElems(p->atletas, destroiGenAtleta);
	free(p);
}

atleta qualAtleta(prova p, int num){		//retorno de um atleta, através da sua respectiva chave//
      int x = num;
      return (atleta) elementoDicionario(p->atletas, (void *)&x);
}

void guardarRegistos(prova p, int metros, char *estilo){	//guardar informações relativas ao comprimento e ao estilo numa prova//
	p->comprimento=metros;
	strcpy(p->estilo, estilo);
}
void tempoOlimpico(prova p, int tempseg){	//guardar tempo olimpico inserido, numa prova//
	p->tempoolimpico=tempseg;
}
int existeNumAtleta(prova p,int num){		//função que permite saber se um determinado atleta se encontra no dicionario de atletas, através da respectiva chave//
	int x = num;
    return existeElemDicionario(p->atletas, (void *) &x);
}


int nAtletas(prova p){		//retorno do numero de atletas presentes na respectiva prova (int)//
	return tamanhoDicionario(p->atletas);
}

int adicAtletaProva(prova p, atleta t){		//adicionar um atleta a uma prova respectiva//
	return (adicionaElemDicionario(p->atletas, t));
}

iterador iteradorAtletas(prova p){		//retorno do iterador que permitirá percorrer o dicionário de atletas//
	return iteradorDicionario(p->atletas);
}


int atletaOlimpico(prova p, atleta t){			//permite saber se o atleta está na lista dos olímpicos ou não//
	if(existeElemConjunto(p->atletasOlimpicos, chaveGenAtleta((void*) t))==1)
		return 1;
	else return 0;
}

void adicionaAtletaOlimpico(prova p, atleta t){
	if(comparaTempo(p->tempoolimpico, t)==0){
		adicionaElemConjunto(p->atletasOlimpicos);
			if(existeElemDicionario(p->clubes, nomeClubeAtleta(t))==1){
				adicionaElemClube(elementoDicionario(p->clubes, nomeClubeAtleta(t)), t);
				incAtletasOlimpicos(elementoDicionario(p->clubes, nomeClubeAtleta(t));
			}
			else
				clube d=criaClube(nomeClubeAtleta(t));
				adicionaElemClube(d, t);
				incAtletas(d);
				
	}
}
