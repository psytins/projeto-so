/*
Passos:
    Usar um counter por thread para contar os pontos

    - Primeiro vamos ter que criar uma função que vá gerar um ponto aleatório dentro 
        de um quandrado que está circunscrito numa circunferência

    - considerar que o quadrado está centrado na origem e tem o canto
        superior direito de coordenadas (1, 1).

    - Pontos a gerar:
        - 20.000 pontos aleatórios utilizando 2 threads = 10.000 por thead
        - 100.000 pontos aleatórios utilizando 4 threads
        - 1.000.000 pontos aleatórios utilizando 6 threads
        - 10.000.000 pontos aleatórios utilizando 8 threads
    
    - Contabilizar o tempo que demora cada estimaç˜ao do valor de PI e medir a qualidade de cada estimativa.

Ter em conta:
    - Aq = 4r^2
    - Ac = PIr^2
    - PI = 4 * (Ac/Aq) 
    - Pontos no circulo = Ac
    - Pontos no quadrado = Aq

-Algoritmo Base
    Um algoritmo
    utilizando simula¸c˜ao de monte carlo pode gerar n pontos aleat´orios dentro do quadrado, contar quantos
    desses est˜ao no círculo e dividir essa contagem pelo total de pontos gerados
*/ 
#include<stdio.h>
#include<math.h>
#include <time.h>
#include <stdlib.h>

//Global
#define RAIO 1

// x^2 + y^2 > 1

float gerarPontoAleatorio(){
    
    //srand(time(NULL));
    float num = (rand() % 1000000);
    float calisto =  (num / 500000) - 1;
    return calisto;
}


int main(){
    float pontoRandom;
    while(1){
        pontoRandom = gerarPontoAleatorio();
        printf("%f\n", pontoRandom);  
    }
    
    return 0;
}

