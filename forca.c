#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "item.h"
#include "forca.h"


void forcaBruta(ITEM **v, int tamVetor, int *bitMask, int camada, int *auxValor, int *auxBitMask, int pesoMax){

    int peso = 0;
    int valor = 0;


    if(camada == tamVetor){

        for(int i = 0; i < tamVetor; i++){
		    if((*bitMask & ((int) pow(2, i))) == ((int) pow(2, i))){

                peso += getPeso(v[i]);
                valor += getValor(v[i]);
                
            
		    }
	    }

        if(peso<pesoMax)
        {
            if(*auxValor<valor){
                *auxValor = valor;
                *auxBitMask = *bitMask;
            }
            

            
            
        }

        return;
	
    }



    int op = (int)pow(2,camada);

    *bitMask = *bitMask & (~op);
    
    forcaBruta(v, tamVetor, bitMask, camada+1, auxValor, auxBitMask, pesoMax);

    *bitMask = *bitMask | op;

    forcaBruta(v, tamVetor, bitMask, camada+1, auxValor, auxBitMask, pesoMax);
    
}
