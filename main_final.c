#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Obtemos um inteiro aleatorio grande que
 * depois transformamos num float entre -1 e 1
 */
float gerarPontoAleatorio(){
  float num = (rand() % 2000001);
  float cordenada =  (num / 1000000) - 1;
  return cordenada;
}

/*
 * Função para verificar se o ponto está dentro do circulo.
 * Retorna 1(True) se estiver dentro do circulo.
 * Retorna 0(False) se estiver no perimetro ou fora do circulo.
 */
int verificarDistancia(float x, float y){
  // x^2 + y2 < r^2, r^2 = 1
  if((x*x) + (y*y) < 1){
      return 1;
  }
  return 0;
}

/* 
 * Calcular quantos pontos estão dento do cirulo.
 * ppt = pontos por thread
 * pontoRamdomX e Y são as cordenadas dos pontos aleatorios
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
  return pontosdentro;
}

/* 
 * Função que calcula o pi, tempo passado e o erro
 * percentual do calculo.
 *
 * Cada conjunto de threads corre 10 vezes 
 * e depois calcula a media dos 10 valores obtidos 
 * que nos dá o resultado final desse conjunto.
 * 
 * Calcula tambem a media dos valores obtidos
 * de cada conjunto de threads.
 *
 * Retorna o float media, que é a media dos valores
 * de todos os conjuntos de threads.
 */
float calcular_pi(int pontos){
  clock_t tempo_inicial = clock(), tempo_final;
  double tempo_passado;
  int ppt, pontosdentro = 0; 
  float contarPontos = 0.0, pi_calculado, *aux;
  int num_threads = 2;
  pthread_t thread_id[8];
  float pis_calculados[4], pis_iniciais[10];
  float pi_tabelado = 3.14159265358979323846264, erro;
  

  printf("\n####### Para %d Pontos #######\n",pontos);

  while (num_threads != 10){
    
    printf("Para %d Threads:\n", num_threads);
    ppt = pontos / num_threads;
    
    for (int y = 0; y < 10; y++){ // Corremos o conjunto de threads 10 vezes

      /*
       * Criamos as threads e só mais tarde lhes damos join
       * para o programa não ficar à espera de cada thread acabar.
       */
      
      for (int i = 0; i < num_threads; i++){
        pthread_create(&thread_id[i], NULL, (void*) &calcular_pontos, (void*) ppt);
      }
      for (int w = 0; w < num_threads; w++){
        pthread_join(thread_id[w], (void*) &aux);
        pontosdentro = pontosdentro + *aux;
      }
      
      // Calculamos o pi com o numero de pontos dentro do circulo
      pis_iniciais[y] = ((float)(pontosdentro)/(float)(pontos)) * 4.0;
      
      pontosdentro = 0;
    }

    pi_calculado = 0; // reset

    //Calculamos a media do algoritmo que foi corrido 10 vezes (pi final)
    for (int x = 0; x < 10; x++){
      pi_calculado = pi_calculado + pis_iniciais[x];
    }
    pi_calculado = pi_calculado / 10;
    
    printf("\nValor pi calculado: %f\n",pi_calculado);
  
    // Calcular erro percentual
    if (pi_tabelado > pi_calculado){
      erro = (pi_tabelado - pi_calculado) / pi_tabelado * 100;
    }else{
      erro = (pi_calculado - pi_tabelado) / pi_tabelado * 100;
    }
    printf("Erro percentual: %f%\n",erro);
  
    // Obter tempo passado e enviar para a consola
    tempo_passado = (double)(clock() - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo passado: %f segundos\n\n",tempo_passado);

    //Para calcular media
    pis_calculados[num_threads/2 - 1] = pi_calculado;
    
    pontosdentro = 0; // reset
    num_threads = num_threads + 2; // proximo numero de threads a ser utilizadas
    tempo_inicial = clock(); // reset
    }

  //Calculamos a media dos valores obtidos
  float media = 0.0;
  float erro_media;
  for(int i = 0; i < 4; i++){
    media = media + pis_calculados[i];
  }
  media = media/4.0;

  if (pi_tabelado > media){
    erro_media = (pi_tabelado - media) / pi_tabelado * 100;
  }else{
    erro_media = (media - pi_tabelado) / pi_tabelado * 100;
  }

  printf("### Media ###\nMedia calculada: %f\nErro da media: %f%\n", media, erro_media); 

  return media;
}

int main(){
  // Damos seed ao metodo random para dar sempre valores diferentes
  srand(time(NULL));
  // 20000 Pontos
  float a = calcular_pi(20000);
  // 100000 Pontos
  float b = calcular_pi(100000);
  // 1000000 Pontos
  float c = calcular_pi(1000000);
  // 10000000 Pontos
  float d = calcular_pi(10000000);

  // Media das medias
  float media = (a + b + c + d) / 4.0;
  
  float pi_tabelado = 3.14159265358979323846264;
  float erro_media;

  // Erro percentual da media das medias
  if (pi_tabelado > media){
    erro_media = (pi_tabelado - media) / pi_tabelado * 100;
  }else{
    erro_media = (media - pi_tabelado) / pi_tabelado * 100;
  }
  printf("\n**** Media das medias ****\n");
  printf("Media: %f\nErro percentual: %f%\n", media, erro_media);

  return 0;
}
