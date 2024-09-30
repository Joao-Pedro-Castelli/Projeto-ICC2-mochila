#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "item.h"
#include "dp.h"

/*A ideia do programação dinâmica é guaradarmos certos resultados. Para isso podemos guardar os resultados 
que são a sequência de potências de 2. Por exemplo: 4 representa a sequencia 100. ou seja pegar apenas 
o 3 elemento, bem como 16 seria a sequência 10000 e pegaria apenas o 5 elemento.
*/


/*No caso do 23 ele não é uma potência de 2 mas podemos escrevê-lo como sendo a soma de potencias de 2:
        23 = 16+7 = 16+4+3 = 16+4+2+1
    Assim podemos utilizar os resultados guardados das potências de 2 para calcular o 23. Além disso podemos ainda 
    guardar o resultado da soma do 23 e utilizá-lo futuramente para outro número. Ex:

        55 = 32+ 23; Ou seja não precisamos mais abrir o 23 em potências de 2 pois já o calculamos anteriormente. 

        A minha ideia é guardar os resultados no vetor memória para podermos acessá-los quando necessário.
        
 */
bool calculoSequencia(ITEM **v, int tamVetor,int *bitMask,int tamBitMask,int camada,int * vetPesos, int * vetValor){

    if(camada == tamVetor){

        for(int i = 0; i < tamVetor; i++){
		    if((bitMask[i/32] & ((int) pow(2, i%32))) == ((int) pow(2, i%32))){
                
		    }
	    }

        
        

    }

        
    int op = (int)pow(2,camada%32);

    bitMask[camada/32] = bitMask[camada/32] & (((int)(pow(2, 32) - 1)) - op);

   

   calculoSequencia(v,tamVetor,bitMask,tamBitMask,camada+1);


    bitMask[camada/32] = bitMask[camada/32]|op;

    calculoSequencia(v,tamVetor,bitMask,tamBitMask,camada+1);

}

void progDinamica(ITEM **v,int tamVetor, int * memoria, int pesoMax,int* bitMask){
    
    calculoSequencia(v,tamVetor,bitMask,tamBitMask,0);

    

}    
                        
