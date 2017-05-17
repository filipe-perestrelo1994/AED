#ifndef ATLETA_H_
#define ATLETA_H_

typedef struct _atleta * atleta;


/*criarProva - Reserva espaço na memoria para uma instancia da estrutura do tipo atleta e
inicializa os seus valores.
Parâmetros: numAtleta - numero do atleta
			*nome - nome do atleta
			*clube - nome do clube do atleta
			*prova - nome da prova onde obteve melhor classificacao
			segundos - melhor tempo em segundos do atleta
Retorna: uma instancia do tipo atleta
Pré-condições:  */

atleta criarAtleta(int numAtleta, char *nome, char *clube, char *prova, float segundos );


/*destruirProva - Liberta espaço na memoria da instancia da estrutura do tipo atleta
Parâmetros: t - atleta
Retorna:
Pré-condições: */

void destruirAtleta(atleta t);


/*numeroAtleta - Devolve o número do atleta
Parâmetros: t - atleta
Retorna:  Numero do atleta
Pré-condições: t!=NULL*/

int numeroAtleta(atleta t);


/*nomeAtleta - Devolve o nome do atleta
Parâmetros: t - atleta
Retorna:  Nome do atleta
Pré-condições: t!=NULL*/

char* nomeAtleta(atleta t);


/*nomeClubeAtleta - Devolve o nome do clube do atleta
Parâmetros: t - atleta
Retorna:  Nome do clube do atleta
Pré-condições: t!=NULL*/

char* nomeClubeAtleta(atleta t);


/*nomeAtleta - Devolve o nome da prova onde o atleta obteve melhor tempo
Parâmetros: t - atleta
Retorna:  o nome da prova onde o atleta obteve melhor tempo
Pré-condições: t!=NULL*/

char* nomeProvaAtleta(atleta t);


/*copararTempo - Compara o tempo do atleta com o dos jogos olimpicos
Parâmetros: t - atleta
Retorna:  1 caso tempo do atleta seja menor que o olimpico, 0 caso contrario
Pré-condições: t!=NULL*/

int copararTempo(float tempseg, atleta t);


/*tempoMelhorAtleta - Devolve o melhor tempo do atleta
Parâmetros: t - atleta
Retorna:  o melhor tempo do atleta
Pré-condições: t!=NULL*/

float tempoMelhorAtleta(atleta t);

#endif
