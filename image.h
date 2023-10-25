#ifndef IMAGE_H_
#define IMAGE_H_

typedef struct Imagem Imagem;

//ler arquivo e armazena informações da imagem.
Imagem *ler_arquivo_salvar_imagem(char *path);

//cria uma cópia da imagem colorida e aplica o filtro preto e branco na cópia
Imagem *img_monocromatica(Imagem *img);

//escreve arquivo da imagem do tipo P2 (PRETO E BRANCO)
void escrever_em_arquivo(Imagem *img, char *path);

//libera as memórias alocadas de uma estrutura Imagem
void liberar_imagem(Imagem *img);

#endif