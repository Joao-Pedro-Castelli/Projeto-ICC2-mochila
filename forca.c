#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "item.h"
#include "forca.h"


void forcaBruta(ITEM **v, int tamVetor, int *bitMask, int camada, int *auxValor, int *auxBitMask, int pesoMax){

    int peso = 0;
    int valor = 0;

    //se a camada de recursao eh a ultima, ou seja estou na ultima folha, ao inves de entrar mais na recursao,
    //vou calcular o bitMask que foi definido e ver se eh o melhor ate agora
    if(camada == tamVetor){

        for(int i = 0; i < tamVetor; i++){
		    if((*bitMask & ((int) pow(2, i))) == ((int) pow(2, i))){ //bitMask precisa ser um ponteiro para as mudancas se
									     //propagarem pelas funcoes

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



    int op = (int)pow(2,camada); //coloco o bit daquela camada como i

    *bitMask = *bitMask & (~op); //not op significa que vou tirar, colocar como 0 o bit, daquela camada, o item i com i = camada
    
    forcaBruta(v, tamVetor, bitMask, camada+1, auxValor, auxBitMask, pesoMax);

    *bitMask = *bitMask | op; //agora vamos calcular o bitMask mas com o bit daquela camada como 1, com o item na mochila

    forcaBruta(v, tamVetor, bitMask, camada+1, auxValor, auxBitMask, pesoMax);
    
    return;
}
