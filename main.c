#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "forca.h"
#include "guloso.h"

void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens);
void arrayItemColocar(FILE *fileptr, ITEM **itemarr, int numItens);
void itensPrintar(ITEM **itemnarr, int numItens, int *bitMask);

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
	printf("array feito\n");
	int bitMask[numItens / 32 + (numItens % 32 != 0)];
	for(int i = 0;i<=numItens/32;i++){
		bitMask[i] = 0;
	}

	printf("Peso Máximo: %d\n",pesoMax);
	guloso(itemarr, numItens, pesoMax, bitMask);

	for(int i = 0;i<=numItens/32;i++){
		printf("%x\n",bitMask[i]);
	}
	printf("guloso feito\n");
	itensPrintar(itemarr, numItens, bitMask);
	return 0;

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

void itensPrintar(ITEM **itemarr, int numItens, int *bitMask){
	for(int i = 0; i < numItens; i++){
		if((bitMask[i/32] & ((int) pow(2, i))) == pow(2,i)){
			printf("item %d: peso->%d | valor->%d\n", i, getPeso(itemarr[i]), getValor(itemarr[i]));
		}
	}
}
