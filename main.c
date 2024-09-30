#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "item.h"
#include "forca.h"
#include "guloso.h"
//#include "dp.h"

typedef struct cronos_{
	clock_t inicio;
	clock_t fim;
	double delta;
} CRONOS;

void tempoDeltaSet(CRONOS *tempo);
void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens);
void arrayItemColocar(FILE *fileptr, ITEM **itemarr, int numItens);
void itensPrintar(ITEM **itemnarr, int numItens, int bitMask, CRONOS *tempo);

int main(int argc, char *argv[]){
	if(argc != 2){
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
	ITEM *itemarr[numItens];
	arrayItemColocar(fileptr, itemarr, numItens);
	int bitMask = 0;
	int auxBitMask = 0;
	
	CRONOS *tempoGuloso = malloc(sizeof(CRONOS));
	tempoGuloso->inicio = clock();
	bitMask = guloso(itemarr, numItens, pesoMax, bitMask);
	tempoGuloso->fim = clock();
	tempoDeltaSet(tempoGuloso);
	printf("Guloso:\n");
	itensPrintar(itemarr, numItens,bitMask, tempoGuloso);
	free(tempoGuloso);
/*
	bitMask = 0;
	CRONOS *tempoDP = malloc(sizeof(CRONOS));
	tempoDP->inicio = clock();
	progDinamica()
	tempoDP->fim = clock();
	tempoDeltaSet(tempoDP);
	printf("Programacao Dinamica:\n");
	itensPrintar(itemarr, numItens, bitMask, tempoDP);
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
	
	return 0;

}

void tempoDeltaSet(CRONOS *tempo){
	tempo->delta = tempo->fim - tempo->inicio;
	return;
}

void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens){
	fseek(fileptr, 0, SEEK_SET);
	int c;
	*numItens = 0;
	*pesoMax = 0;
	while((c = fgetc(fileptr)) != ','){
		*numItens *= 10;
		*numItens += c - '0';
	}
	while((c = fgetc(fileptr)) != '\r' && c != '\n'){
		*pesoMax *= 10;
		*pesoMax += c - '0';
	}
	if(c == '\r')
		fgetc(fileptr);
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
		if((bitMask & ((int) pow(2, i))) == ((int) pow(2, i))){
			printf("item %d: peso->%d | valor->%d\n", i, getPeso(itemarr[i]), getValor(itemarr[i]));
		}
	}
	printf("Tempo de execucao: %lfms\n", tempo->delta);
}
