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
#include <stdio.h>
#include <math.h>
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
 * ppt = pontos por thread.
 */
void* calcular_pontos(void *ppt){
    float pontoRandomX, pontoRandomY, *pontosdentro = malloc(sizeof(float));
    int dentroCirculo;
    float contarPontos;
    for(int i = 0; i < ppt; i++){
        pontoRandomX = gerarPontoAleatorio();
        pontoRandomY = gerarPontoAleatorio();
        if(verificarDistancia(pontoRandomX,pontoRandomY)){
            contarPontos += 1;
        }  
    }
    *pontosdentro = contarPontos;
    //printf("pontosdentro: %lu\n",pontosdentro);
    return pontosdentro;
}


int calcular_pi(int pontos){
  clock_t tempo_passado_inicial;
  double tempo_passado;
  float pontoRandomX;
  float pontoRandomY;
  int ppt, pontosdentro = 0; 
  float contarPontos;
  float pontosTotails;
  float pi_calculado;
  float *aux;
  contarPontos = 0.0;
  pontosTotails = 10000.0;
  tempo_passado_inicial = clock();
  srand(time(NULL));
  

  

  if (pontos == 20000){
    printf("Para 2 Threads:\n");
    pthread_t thread_id[2];
    ppt = pontos / 2;
    for (int i = 0; i < 2; i++){
      pthread_create(&thread_id[i], NULL, (void**) &calcular_pontos, ppt);
      pthread_join(thread_id[i], (void **)&aux);
      pontosdentro = pontosdentro + *aux;
    }
  }else if(pontos == 100000){
    printf("Para 4 Threads:\n");
    pthread_t thread_id[4];
    ppt = pontos / 4;
    for (int i = 0; i < 4; i++){
      pthread_create(&thread_id[i], NULL, (void**) &calcular_pontos, ppt);
      pthread_join(thread_id[i], (void **)&aux);
      pontosdentro = pontosdentro + *aux;
    }
  }else if(pontos == 1000000){
    printf("Para 6 Threads:\n");
    pthread_t thread_id[6];
    ppt = pontos / 6;
    for (int i = 0; i < 6; i++){
      pthread_create(&thread_id[i], NULL, (void**) &calcular_pontos, ppt);
      pthread_join(thread_id[i], (void **)&aux);
      pontosdentro = pontosdentro + *aux;
    }
  }else if(pontos == 10000000){
    printf("Para 8 Threads:\n");
    pthread_t thread_id[8];
    ppt = pontos / 8;
    for (int i = 0; i < 8; i++){
      pthread_create(&thread_id[i], NULL, (void**) &calcular_pontos, ppt);
      pthread_join(thread_id[i], (void **)&aux);
      pontosdentro = pontosdentro + *aux;
    }
  }else return 0;
  
  
  // Calculamos o pi com o numero de pontos dentro do circulo
  pi_calculado = ((float)(pontosdentro)/(float)(pontos)) * 4.0;
  printf("\nValor pi calculado: %f\n",pi_calculado);

  // Calcular erro percentual
  float pi_tabelado = 3.141592;
  float erro;

  if (pi_tabelado > pi_calculado){
    erro = (pi_tabelado - pi_calculado) / pi_tabelado * 100;
  }else {
    erro = (pi_calculado - pi_tabelado) / pi_tabelado * 100;
  }
  printf("Erro percentual: %f%\n",erro);

  // Obter tempo passado e enviar para a consola
  tempo_passado = (double)(clock() - tempo_passado_inicial) / CLOCKS_PER_SEC;
  printf("Tempo passado: %f segundos\n\n",tempo_passado);

  return 0;
}

int main(){
  // 20000 Pontos, 2 Threads
  calcular_pi(20000);
  // 100000 Pontos, 4 Threads
  calcular_pi(100000);
  // 1000000 Pontos, 6 Threads
  calcular_pi(1000000);
  // 10000000 Pontos, 8 Threads
  calcular_pi(10000000);

  return 0;
}
