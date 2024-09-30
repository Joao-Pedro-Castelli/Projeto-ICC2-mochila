#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "guloso.h"


int guloso(ITEM **v, int n, int pesoMax, int bitMask)
{
    float *razao = malloc(sizeof(float)*n);
    
    int aux = 0;
    int peso = 0;

    for(int i = 0;i<n;i++){
        razao[i] = ((float) getValor(v[i])) / ((float) getPeso(v[i]));
    }
    
    int op;
    while(peso < pesoMax){
        for(int i = 0;i<n;i++){
            if(razao[aux]<razao[i]){
                aux = i;
            }

        }
        razao[aux] = 0;
        peso += getPeso(v[aux]);
        if(peso>pesoMax){
            peso-=getPeso(v[aux]);
            break;
        }

        op = (int) pow(2,aux);

        bitMask = bitMask | op;
       

    }

    free(razao);

    return bitMask;
}
