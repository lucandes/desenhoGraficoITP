#include "struct.h"

#ifndef IMAGEM_H
#define IMAGEM_H

Imagem criarImagem(void);
Imagem abrirImagem(void);
void salvarImagem(Imagem *imagem);
void limparImagem(Imagem *imagem);
Desenho criarDesenho(void);
void listarDesenhos(Desenho d);
void inserirDesenhos(Imagem *imagem);
void mudarCor(Imagem *imagem);

#endif