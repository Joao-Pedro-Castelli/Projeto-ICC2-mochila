#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "forca.h"

void linhaUmPegar(FILE *fileptr, int *pesoMax, int *numItens);
void arrayItemColocar(FILE *fileptr, ITEM **itemarr, int numItens);

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
	while((c = fgetc(fileptr)) != '\n'){
		*pesoMax *= 10;
		*pesoMax += c - '0';
	}
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
		while((c = fgetc(fileptr)) != '\n'){
			peso *= 10;
			peso += c - '0';
		}
		itemarr[i] = itemCriar(valor, peso);
	}
	return;
}

