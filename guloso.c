#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "guloso.h"


void guloso(iTEM* v, int n, int pesoMax,int tamanho, int *bitMask)
{
    float razao[n];
    int aux;
    int pesoMochila = 0;
    int peso = 0;

    for(int i = 0;i<n;i++){
        razao[i] = (float) getValor(v[i])/getPeso(v[i]);
    }

    
    int posicao;
    int op;
    while(peso <= pesoMax){
        for(int i = 0;i<n;i++){
            if(razao[aux]<razao[i]){
                aux =i;
            }

        }
        razao[aux] = 0;
        peso += getPeso(v[aux]);

        posicao = aux/32;
        op = (int) pow(2,aux%32);

        bitMask[posicao] = bitMask[posicao]|op;

       

    }


}