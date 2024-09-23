#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

struct item_{
	int peso;
	int valor;
};

ITEM *itemCriar(int valor, int peso){
	ITEM *item = (ITEM *)malloc(sizeof(ITEM));
	if(item != NULL){
		item->peso = peso;
		item->valor = valor;
	}
	return item;
}

bool itemApagar(ITEM **item){
	if((*item) != NULL){
		free(*item);
		(*item) = NULL;
		return(true);
	}
	return(false);
}

int getPeso(ITEM *item){
	return item->peso;
}

int getValor(ITEM *item){
	return item->valor;
}
