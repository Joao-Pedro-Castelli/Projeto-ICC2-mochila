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
    int isupremo = 0;
    while(peso < pesoMax){
	if(isupremo > n){
		break;
	}
        for(int i = 0;i<n;i++){
            if(razao[aux]<razao[i]){
                aux = i; //encontro o melhor item de acordo com valor/peso
            }

        }
        razao[aux] = 0; //nao posso repetir esse item
        peso += getPeso(v[aux]); //vou acumulando o peso dos itens que acumulo na mochila para ver quando ultrapasso
	isupremo++;
        if(peso>pesoMax){
            peso-=getPeso(v[aux]);
            continue;
        }

        op = (int) pow(2,aux); //numero binario com tudo 0 e 1 na posicao aux
			       //na interpretacao de bitMask, isso significa que o item i esta na mochila e o resto nao

        bitMask = bitMask | op; //agora o bit na posicao i no int bitMask eh 1, ou seja, coloquei o item i na mochila
       

    }

    free(razao);

    return bitMask;
}
