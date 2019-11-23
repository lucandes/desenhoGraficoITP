#include "struct.h"

#ifndef IMAGEM_H
#define IMAGEM_H

Imagem criarImagem(int *imagemAberta, int lar, int alt);
Imagem abrirImagem(int *imagemAberta, char caminho[100]);
void salvarImagem(Imagem *imagem);
void limparImagem(Imagem *imagem, Cor cor);
Desenho criarDesenho(void);
void listarDesenhos(Desenho d);
void inserirDesenhos(Imagem *imagem);
void inserirPreenchimento(int x, int y, Preencher p, Imagem *imagem);

#endif