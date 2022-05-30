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
    
    - Contabilizar o tempo_passado que demora cada estimaç˜ao do valor de PI e medir a qualidade de cada estimativa.

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
//#define RAIO 1

// x^2 + y^2 > 1

float gerarPontoAleatorio(){
    
    //srand(time(NULL)); meter a seed em miliseconds
    float num = (rand() % 20001);
    float calisto =  (num / 10000) - 1;
    return calisto;
}

int verificarDistancia(float x, float y){
    if((x*x) + (y*y) < 1){
        return 1;
    }
    return 0;
}

/* 
 * Calcular quantos pontos estão dento do cirulo.
 * args = o numero de pontos que cada thread them de gerar.
 */
void* calcular_pontos(void* args){
    float pontoRandomX;
    float pontoRandomY;
    int dentroCirculo;
    float contarPontos;
    for(int i = 20000; i < 20000; i++){
        pontoRandomX = gerarPontoAleatorio();
        pontoRandomY = gerarPontoAleatorio();
        if(verificarDistancia(pontoRandomX,pontoRandomY)){
            contarPontos += 1;
        }  
    }
    *(float*) args = contarPontos;
    return args;
}


int main(){
    clock_t tempo_passado_inicial;
    double tempo_passado;
    float pontoRandomX;
    float pontoRandomY;
    int dentroCirculo; //bool
    float contarPontos;
    float pontosTotails;
    float pi;
    contarPontos = 0.0;
    pontosTotails = 10000.0;
    tempo_passado_inicial = clock();
    /*
    for(int cnt = 0; cnt < pontosTotails; cnt++){
        pontoRandomX = gerarPontoAleatorio();
        pontoRandomY = gerarPontoAleatorio();
        //printf("X: %f\n",pontoRandomX);
        //printf("Y: %f\n",pontoRandomY);
        dentroCirculo = verificarDistancia(pontoRandomX,pontoRandomY);
        if(dentroCirculo){
            contarPontos += 1;
        }        
        printf("\n");
        //Contar tempo_passado
        /tempo_passado = (double)(clock() - tempo_passado_inicial) / CLOCKS_PER_SEC;
    }*/
    pi = (contarPontos/pontosTotails) * 4.0;
    printf("\n%f\n",pi);
    printf("tempo_passado Passado: %f segundos\n",tempo_passado);
    //Verificar





    return 0;
}

