#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "item.h"
#include "forca.h"


void forcaBruta(ITEM **v,int tamVetor, int *bitMask,int tamBitMask,int camada,int *auxValor, int *auxBitMask,int pesoMax){

    int peso = 0;
    int valor = 0;


    if(camada == tamVetor){

        for(int i = 0; i < tamVetor; i++){
		    if((bitMask[i/32] & ((int) pow(2, i%32))) == ((int) pow(2, i%32))){

                peso += getPeso(v[i]);
                valor += getValor(v[i]);
                
            
		    }
	    }

        if(peso<pesoMax)
        {
            if(auxValor[0]<valor){
                *auxValor = valor;
                for(int i=0;i<tamBitMask;i++){
                auxBitMask[i] = bitMask[i];
                }
            }
            

            
            
        }

        return;
        
    }



    int op = (int)pow(2,camada%32);

    bitMask[camada/32] = bitMask[camada/32] & (~op);
    
    forcaBruta(v,tamVetor,bitMask,tamBitMask,camada+1,auxValor,auxBitMask,pesoMax);

    bitMask[camada/32] = bitMask[camada/32]|op;

     forcaBruta(v,tamVetor,bitMask,tamBitMask,camada+1,auxValor,auxBitMask,pesoMax);
    
    
    
}