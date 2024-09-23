#ifndef ITEM_H
	#define ITEM_H
	#include <stdbool.h>
	
	typedef struct item_ ITEM;
	ITEM *itemCriar(int valor, int peso);
	bool itemApagar(ITEM **item);
	int getPeso(ITEM *item);
	int getValor(ITEM *item);
#endif
