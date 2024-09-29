#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "item.h"
#include "dp.h"

/*A ideia do programação dinâmica é guaradarmos certos resultados. Para isso podemos guardar os resultados 
que são a sequência de potências de 2. Por exemplo: 4 representa a sequencia 100. ou seja pegar apenas 
o 3 elemento, bem como 16 seria a sequência 10000 e pegaria apenas o 5 elemento.*/

/*No caso do 23 ele não é uma potência de 2 mas podemos escrevê-lo como sendo a soma de potencias de 2:
        23 = 16+7 = 16+4+3 = 16+4+2+1
    Assim podemos utilizar os resultados guardados das potências de 2 para calcular o 23. Além disso podemos ainda 
    guardar o resultado da soma do 23 e utilizá-lo futuramente para outro número. Ex:

        55 = 32+ 23; Ou seja não precisamos mais abrir o 23 em potências de 2 pois já o calculamos anteriormente. 

        A minha ideia é guardar os resultados no vetor memória para podermos acessá-los quando necessário.
        
 */
int calculoSequencia(ITEM **v, int sequencia,int *memoria){

    int aux = sequencia;
    int i =0;
    int peso =0;

    if (memoria[sequencia]!=0){
        peso += getPeso(memoria[sequencia]);
        return peso;
    }
    

    while(aux%2){
        aux=aux/2;
        i++;

    }
    aux = sequencia;
    sequencia = sequencia -pow(2,i);
    peso+= getPeso(v[pow(2,i)]);

    peso+= calculoSequencia(v,sequencia,memoria);

    memoria[aux] = peso;

    return peso;



}

void progDinamica(ITEM **v,int tamVetor, int * memoria, int pesoMax){
    long long int i;
    int peso;
    int melhor = 0;
    for(i=1;i<=pow(2,tamVetor);i++){
        peso = calculoSequencia(v,i,memoria);

        if(melhor<peso && peso<pesoMax){
            melhor = peso;
        }



        
    }
    



}