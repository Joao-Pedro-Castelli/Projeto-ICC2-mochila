#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "item.h"
#include "forca.h"

int* forcaBruta(ITEM **v,int tamVetor, int *bitMask,int tamBitMask,int camada){

    if(camada == tamVetor+1){
        
    }

    
    forcaBruta(v,tamVetor,bitMask,tamBitMask,camada+1);

    for(int i = 0; i < tamVetor; i++){

			
		
	}

    int op = (int)pow(2,camada%32);

    bitMask[camada/32] = bitMask[camada/32]|op;

    int *aux2 = forcaBruta(v,tamVetor,bitMask,tamBitMask,camada+1);
    
    
    
}