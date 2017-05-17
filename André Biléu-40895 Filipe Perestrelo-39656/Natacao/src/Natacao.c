#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "atleta.h"
#include "iterador.h"
#include "atletaGen.h"
#include "provaDic.h"

#define TAM 100


void registoFile(prova p, char *line);		//chamar as funções mais abaixo implementadas//
void MelhorTempoAtleta(prova p, char *line);
void AtletaOlimpico(prova p, float tempseg, char *line);
void listarAtletas(prova p);
void listarOlimpicos(prova p, float tempseg);
void listarAtletasClubeOlimpicos(prova p, char * clube);
void listarPodiumClubes();

int main(void) {
	prova pv = criaProva();
	comando (pv);
	DestroiProva(pv);
	return 1;
}

void comando (prova p) {		//operador de comandos//
	char linhaCMD[TAM], cmd;
	char *estilo;
	int distancia;
	int tempmin;
	float tempseg;

	printf("Prova (metros estilos): ");		//receber dados da distancia e do estilo da prova//
	scanf("%d %s", &distancia, estilo);
	getchar();
	printf("Tempo Olímpico (mm:ss.ss): ");		//receber dados relativos ao tempo olímpico//
	scanf("%d:%f", &tempmin, &tempseg);
	getchar();
	guardarRegistos(p, distancia, estilo);		//função do tad prova que altera o comprimento e o estilo da prova p//
	tempseg=tempoParaSeg(tempmin, tempseg);		//função do tad atleta que converte o tempo para segundos
	tempoOlimpico(p, tempseg);	//função do tad prova que altera tempoolimpico na prova p//

	printf("-");
	gets(linhaCMD);
	cmd = toupper (linhaCMD[0]);
	while (cmd!='X') {
		switch (cmd) {		//operador switch que irá interpretar os comandos do utilizador
			case 'R' : if(linhaCMD[1]=='C')
						listarPodiumClubes(); //fun��o que ir� listar o podium de Clubes com um maior numero de atletas ol�mpicos//
				else
				registoFile(p, linhaCMD); break;		//função que irá registar o ficheiro pedido pelo utilizador//
			case 'A' : if(linhaCMD[1]=='O')
							AtletaOlimpico(p, tempseg, linhaCMD);		//função que irá encarregar de verificar o tempo do atleta com o tempo olimpico previemente registado//
						else
							MelhorTempoAtleta(p, linhaCMD); break;		//função que se encarregará de mostrar o melhor tempo do atleta//
			case 'L' : if(linhaCMD[1]=='O')
							listarOlimpicos(p, tempseg);		//função que mostra todos os atletas com tempos olimpicos nessa prova//
						else
							listarAtletas(p); break;		//função que mostra todos os atletas na referida prova
			case 'C' :if (linhaCMD[1]=='O'){
							listarAtletasClubeOlimpicos(p, LinhaCMD); break; //função que irá listar toda a informação referente aos atletas do clube indicado que podem competir nos Jogos Olímpicos na prova em causa//
						}
						else printf("comando inválido"); break;
			default: printf("Comando Invalido\n"); break;
		}
		printf(">");
		gets(linhaCMD);
		cmd = toupper (linhaCMD[0]);
	}
}
void lerFile(prova p, char *linha){
	char ficheiro[TAM], c;
	char prova[TAM], estilos[TAM], nome[TAM], clube[TAM], str[LINHA], str2[TAM];
	int numestilos, metros, atletas, min, numAtleta, i, j;
	float seg, seg2;

	FILE *fp;

	if(sscanf(linha,"%c %s", &c, ficheiro)!=2){
		printf("Dados invalidos.\n");
	} else {
		fp = fopen(ficheiro, "r");
		strcpy(prova, fgets(str, LINHA, fp));
		fgets(str, LINHA, fp);
		numestilos=atoi(str);

		for(i=0;i<numestilos;i++){
			fgets(str, LINHA, fp);
			sscanf(str,"%d %s", &metros, estilos);
			fgets(str, LINHA, fp);
			atletas=atoi(str);

			for(j=0;j<atletas;j++){
				fgets(str, LINHA, fp);
				strcpy(str2, strtok(str, ";"));
				numAtleta=atoi(str2);
				strcpy(nome, strtok(NULL, ";"));
				strcpy(clube, strtok(NULL, ";"));
				strcpy(str2, strtok(NULL, ":"));
				min=atoi(str2);
				strcpy(str2, strtok(NULL, ";"));
				seg=atof(str2);

				if(comparaME(p, metros, estilos)==1){
					seg=TempoParaSeg(min, seg);
					if(existeAtleta(p,numAtleta)==1){
						atleta a=qualAtleta(p, numAtleta);
						seg2=tempoAtleta(a);

						if(seg<seg2){
							melhoraTempo(seg, a, prova);}
					} else {
						adicionaAtleta(p, numAtleta, nome, clube, prova, seg);
					}
				}
			}
		}
	}
	fclose(fp);
}

void registoFile(prova p, char *line){		//função que verá se o nome de ficheiro é valido, e caso seja irá para a função ler file//
	char ch, *ficheiro;

	if(sscnaf(line,"%c %s",&c , ficheiro)!=2)
		printf("dados invalidos");
	else
		lerFile(p, ficheiro);
}

void MelhorTempoAtleta(prova p, char *line){
	int numero;
	char ch;
	atleta t;
	if(sscnaf(line,"%c %d",&ch , &numero)!=2)
		printf("dados invalidos");
	else{
		t=qualAtleta(p, num);//função do tad prova
		if(t==NULL)
			printf("atleta inexistente\n");
		else
			printf("Melhor tempo: %d:%f\n",minutoAtleta(t), segundoAtleta(t));
	}
}

void AtletaOlimpico(prova p, float tempseg, char *line){
	int numero;
	char ch;
	atleta t;
	if(sscnaf(line,"%c %d",&ch , &numero)!=2)
		printf("dados invalidos");
	else{
		t=qualAtleta(p, numero);// tad prova
		if(t==NULL)
			printf("atleta inexistente\n");
		else
			if(comparatempo(tempseg, t))
				printf("Atleta pode participar nos Olimpicos");

			else printf("Atleta não pode participar nos Olimpicos");
	}
}

void listarAtletas(prova p){
	atleta t;
	iterador it;
	if(nAtletas(p)!=0){
		it=iteradorAtletas(p);
		while(temSeguinteIterador(it)){
			t=seguiteIterador(it);
			printf("%d;%s;%s;%s;%d:%f",numeroAtleta(t), nomeAtleta(t), nomeClubeAtleta(t), nomeProvaAtleta(t), minutoAtleta(t), segundoAtleta(t));
		}
	}
	detroiIterador(it);
}

void listarOlimpicos(prova p, float tempseg){
	atleta t;
	iterador it;
	if(tamanhoConjunto(p->atletasOlimpicos)!=0){
		it=iteradorConjunto(p->atletasOlimpicos);
		while(temSeguinteIterador(it)){
				t=seguiteIterador(it);
			printf("%d;%s;%s;%s;%d:%f",numeroAtleta(t), nomeAtleta(t), nomeClubeAtleta(t), nomeProvaAtleta(t), minutoAtleta(t), segundoAtleta(t));
		}
	detroiIterador(it);
	}
	else printf("Não há atletas olímpicos na prova em causa");
}

void listarAtletasClubeOlimpicos(char * ch){
	atleta t;
	iterador it;
	int contador=0;
	if(existeElemDicionario(p->clubes, ch)==1){
		it=iteradorConjunto(atletasOlimpicosClube(elemDicionario(p->clubes, ch));
			while(temSeguinteIterador(it)){
				t=seguinteIterador(it);
				printf("%d;%s;%s;%s;%d:%f",numeroAtleta(t), nomeAtleta(t), nomeClubeAtleta(t), nomeProvaAtleta(t), minutoAtleta(t), segundoAtleta(t));
			}
	}
	else printf("N�o existem atletas com tempos para os Jogos Olimpicos.");
}

void listarPodiumClubes(prova p){
	
	
	
	
	iterador it;
	if(vazioDicionario==1){
		printf("N�o h� clubes com atletas ol�mpicos");
	}
	else{
		it=iteradorDicionario(p->clubes);
			while(temSeguinteIterador(it)){
			clube c=seguinteIterador(it);	
		


}

