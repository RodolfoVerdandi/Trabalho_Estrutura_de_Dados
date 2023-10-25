#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main(void) {
  char path[100];
  char path2[100];
  int escolha=-1;
  Imagem *imagem_monocromatica = NULL;
  Imagem *imagem_colorida = NULL;
  
  while (escolha!=0){
    
    printf("O que deseja fazer? \n\n");
    
    printf("1-Carregar Imagem \n");
    printf("2-Aplicar Preto e Branco \n");  
    printf("3-Salvar imagem em preto e branco \n");
    printf("0-Fechar Programa \n\n");

    printf("Digite: ");
    if(scanf("%d", &escolha)==1){};
    printf("\n");
    
    if (escolha==1){
      printf("Digite o caminho da imagem: ");
      if(scanf("%99s", path)==1){};
      imagem_colorida = ler_arquivo_salvar_imagem(path);
      printf("\nArquivo lido, imagem salva!\n\n");
    }
    
    if (escolha==2){
      imagem_monocromatica = img_monocromatica(imagem_colorida);
      printf("\nTransformação feita!\n\n");
    }
    
    if (escolha==3){
      printf("Digite o caminho para converter a imagem: ");
      if(scanf("%99s", path2)==1){};
      escrever_em_arquivo(imagem_monocromatica, path2);
      printf("\nImagem arquivada!\n\n");
    }
    
  }
  liberar_imagem(imagem_colorida);
  liberar_imagem(imagem_monocromatica);
  return 0;
}