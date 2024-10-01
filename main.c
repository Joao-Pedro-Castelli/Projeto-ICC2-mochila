#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "item.h"
#include "forca.h"
#include "guloso.h"
#include "dp.h"

//struct para facilitar a cronometracao dos algoritmos
typedef struct cronos_{
	clock_t inicio;
	clock_t fim;
	double delta;
} CRONOS;

void tempoDeltaSet(CRONOS *tempo); //coloca dentro da struct a diferenca entre fim e inicio
void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens); //pega o numero de itens e o peso maximo na primeira linha do arquivo
void arrayItemColocar(FILE *fileptr, ITEM **itemarr, int numItens); //coloca os pesos e valores dos itens no array da struct item
void itensPrintar(ITEM **itemnarr, int numItens, int bitMask, CRONOS *tempo); //printa os itens que estao no bitMask

int main(int argc, char *argv[]){
	if(argc != 2){ //o programa deve ser executado passando-se o nome do arquivo
		printf("erro! coloque o nome do arquivo na chamada do exe e apenas ele\n");
		return 0;
	}
	FILE *fileptr;
	int pesoMax, numItens;
	fileptr = fopen(argv[1], "r");
	if(fileptr == NULL){
		printf("erro! nome de arquivo nao existe neste diretorio\n");
		return 0;
	}
	linhaUmPegar(fileptr, &pesoMax, &numItens);
	printf("sai do linha um\n");
	ITEM *itemarr[numItens];
	arrayItemColocar(fileptr, itemarr, numItens);
	printf("sai do itemcolocar\n");
	int bitMask = 0; //inteiro em que cada bit representa se um item esta na mochila ou nao
	int auxBitMask = 0; //sera usado no forca bruta
	printf("peso: %d\n", pesoMax);
	
	CRONOS *tempoGuloso = malloc(sizeof(CRONOS));
	tempoGuloso->inicio = clock();
	bitMask = guloso(itemarr, numItens, pesoMax, bitMask);
	tempoGuloso->fim = clock();
	tempoDeltaSet(tempoGuloso);
	printf("Guloso:\n");
	itensPrintar(itemarr, numItens,bitMask, tempoGuloso);
	free(tempoGuloso);
	tempoGuloso = NULL;

	int **dp = malloc((numItens + 1) * sizeof(int *));
	for (int i = 0; i <= numItens; i++) {
    	dp[i] = malloc((pesoMax + 1) * sizeof(int));
	}

	for(int i=0;i<numItens;i++){
		for(int j = 0;j<=pesoMax;j++){
			dp[i][j] = -1;
		}
	}


/*
	bitMask = 0;
	CRONOS *tempoDP = malloc(sizeof(CRONOS));
	tempoDP->inicio = clock();
	progDinamica()
	tempoDP->fim = clock();
	tempoDeltaSet(tempoDP);
	printf("Programacao Dinamica:\n");
	itensPrintar(itemarr, numItens, bitMask, tempoDP);
	free(tempoDP);
	tempoDP = NULL;
*/	

	bitMask = 0;
	int auxValor = 0;
	CRONOS *tempoFB = malloc(sizeof(CRONOS));
	tempoFB->inicio = clock();
	forcaBruta(itemarr, numItens, &bitMask, 0, &auxValor, &auxBitMask, pesoMax);
	tempoFB->fim = clock();
	tempoDeltaSet(tempoFB);
	printf("Forca bruta:\n");
	itensPrintar(itemarr, numItens, auxBitMask, tempoFB);
	free(tempoFB);
	tempoFB = NULL;
	


	bool **resposta = malloc((numItens + 1) * sizeof(bool *));
	for (int i = 0; i <= numItens; i++) {
    	resposta[i] = malloc((pesoMax + 1) * sizeof(bool));
	}

	for(int i=0;i<numItens;i++){
		for(int j = 0;j<=pesoMax;j++){
			resposta[i][j] = false;
		}
	}
	
	progDinamica(itemarr, numItens,dp,0,pesoMax,resposta);
	
	int n = 0;
	while(true){
		if((n>numItens-1) || pesoMax<0){
			//printf("n: %d  peso: %d\n", n, pesoMax);
			break;
		}
		if(resposta[n][pesoMax]>0){
			printf("item %d: peso->%d | valor->%d\n",n,getPeso(itemarr[n]),getValor(itemarr[n]));
			//printf("final dp[%d][%d]: %d\n", n, pesoMax, dp[n][pesoMax]);
   			//printf("final  resposta[%d][%d]: %d\n", n, pesoMax,  resposta[n][pesoMax]);
			pesoMax-=getPeso(itemarr[n]);
			n++;
		}
		else{
			//printf("final else dp[%d][%d]: %d\n", n, pesoMax, dp[n][pesoMax]);
   			//printf("final else  resposta[%d][%d]: %d\n", n, pesoMax,  resposta[n][pesoMax]);
			n++;
		}
	}

return 0;
}

void tempoDeltaSet(CRONOS *tempo){
	tempo->delta = (tempo->fim - tempo->inicio) * 1000000 / (CLOCKS_PER_SEC);
	return;
}

void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens){
	fseek(fileptr, 0, SEEK_SET);
	int c;
	*numItens = 0;
	*pesoMax = 0;
	while((c = fgetc(fileptr)) != ','){ //cada numero eh separado por uma virgula, entao leio ate ela e computo o inteiro
		*numItens *= 10;
		*numItens += c - '0';
	}
	while((c = fgetc(fileptr)) != '\r' && c != '\n'){ // no linux a linha termina apenas com \n, mas no windows tem \r tambem
		*pesoMax *= 10;
		*pesoMax += c - '0';
	}
	if(c == '\r')
		fgetc(fileptr); //se tem um \r devo ler o \n para a proxima iteracao comecar na proxima linha
	return;
}

void arrayItemColocar(FILE *fileptr, ITEM **itemarr, int numItens){
	int c, valor, peso;
	for(int i = 0; i < numItens; i++){
		valor = 0;
		peso = 0;
		while((c = fgetc(fileptr)) != ','){
			valor *= 10;
			valor += c - '0';
		}
		while((c = fgetc(fileptr)) != '\n' && c != '\r'){
			peso *= 10;
			peso += c - '0';
		}
		if(c == '\r')
			fgetc(fileptr);
		itemarr[i] = itemCriar(valor, peso);
	}
	return;
}

void itensPrintar(ITEM **itemarr, int numItens, int bitMask, CRONOS *tempo){
	for(int i = 0; i < numItens; i++){
		//ao fazer and bitwise entre o int bitMask e uma potencia de 2, se o resultado nao eh 0, significa que
		//o bit na posicao i era 1 -> 10101010101 & 00010000 == 00010000 se aquele item esta na mochila ou 0000000000 se nao
		if((bitMask & ((int) pow(2, i))) == ((int) pow(2, i))){
			printf("item %d: peso->%d | valor->%d\n", i, getPeso(itemarr[i]), getValor(itemarr[i]));
		}
	}
	printf("Tempo de execucao: %lfus\n", tempo->delta);
}
