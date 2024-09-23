#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"


int guloso(iTEM* v, int n, int pesoMax)
{
    float media[n];
    int aux = 0;
    int pesoMochila = 0;

    for(int i = 0;i<n;i++){
        media[i] = (float) getValor(v[i])/getPeso(v[i]);
    }

    
    while(peso <= pesoMax){
        for(int i = 0;i<n;i++){
            if(media[aux]<media[i]){
                aux =i;
            }

        }
        media[aux] = 0;
        peso += getPeso(v[aux]);
    }

}