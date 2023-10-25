#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"


struct Imagem {
  int rows, cols, max; 
  char type[3];  
  unsigned int **matriz;
} ;

void aloca_matriz(Imagem *img) {
  // aloca memória para matriz de imagem colorida
  if (strcmp(img->type,"P3")==0){
  img->matriz = (unsigned int **)malloc(sizeof(unsigned int *) * img->rows);
  for (int i = 0; i < img->rows; i++) {
    img->matriz[i] = (unsigned int *)malloc(sizeof(unsigned int) * img->cols *3 );
  }
  }
  // aloca memória para matriz de imagem preta e branca.
  else{
    img->matriz = (unsigned int **)malloc(sizeof(unsigned int *) * img->rows);
    for (int i = 0; i < img->rows; i++) {
      img->matriz[i] = (unsigned int *)malloc(sizeof(unsigned int) * img->cols );
  }
}
  
}

void escrever_em_arquivo(Imagem *img, char *path){

  FILE *file = fopen(path, "w");

  if (file == NULL) {
    printf("Error! Could not open file\n");
    exit(-1);
  }

  fprintf(file, "%s\n", img->type);
  fprintf(file, "%d %d\n", img->rows, img->cols);
  fprintf(file, "%d\n", img->max);
  for (int i = 0; i < img->rows; i++) {
      for (int j = 0; j < img->cols; j++) {
          fprintf(file, "%d ", img->matriz[i][j]);
      }
      fprintf(file, "\n"); 
  }
  fclose(file);
}

Imagem *create() {
  Imagem *new_image = (Imagem *)malloc(sizeof(Imagem));
  return new_image;
}



void read_from_file(Imagem *img, char *path) {
// abre o arquivo
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error! Could not open file\n");
    exit(-1);
  }

// leitura do cabecalho do arquivo & armazenamento de informação
  fscanf(file, "%2s", img->type);
  fscanf(file, "%d %d", &img->rows, &img->cols);
  fscanf(file, "%d", &img->max);

  aloca_matriz(img);

// lendo o arquivo, armazenando a matriz
  for (int i = 0; i < img->rows; i++) {
    for (int j = 0; j < img->cols*3; j++) {
      fscanf(file, "%u", &img->matriz[i][j]);
    }
  }
// fecha o arquivo
  fclose(file);
}

Imagem* ler_arquivo_salvar_imagem(char *path){
  Imagem *img = create();
  read_from_file(img, path);
  return img;
}

void colorido_para_pretoEbranco(Imagem *img_cor, Imagem *img_mono){
  //Copia as informações de cabecalho da imagem original para a filtrada,
  //exceto o "tipo" da imagem, porque se tornará do tipo P2 (PRETO E BRANCO)
  img_mono->cols=img_cor->cols;
  img_mono->rows=img_cor->rows;
  img_mono->max=img_cor->max;
  strcpy(img_mono->type, "P2");

  aloca_matriz(img_mono);


  //aplicação do filtro preto e branco
  // pixel preto e branco = 0.299 * Red + 0.587 * Green + 0.114 * Blue
  unsigned int red, green, blue;
  for (int i = 0; i < img_cor->rows; i++) {
    for (int j = 0; j < img_cor->cols; j++) {
      
      red = img_cor->matriz[i][j*3];
      green = img_cor->matriz[i][(j*3)+1];
      blue = img_cor->matriz[i][(j*3)+2];
      
      img_mono->matriz[i][j] = 
        (0.299 * red) + 
        (0.587 * green) + 
        (0.114* blue);
    }
  }
}

Imagem* img_monocromatica(Imagem *img_cor){
  Imagem *img_mono = create();
  colorido_para_pretoEbranco(img_cor, img_mono);
  return img_mono;
}


// libera a matriz da imagem, depois a estrutura Imagem.
void liberar_imagem(Imagem *img){
  for (int i = 0; i < img->rows; i++) {
    free(img->matriz[i]);
  }
  free(img->matriz);
  free(img);
}

