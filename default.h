#include "struct.h"

#ifndef DEFAULT_H
#define DEFAULT_H

Imagem criarImagem();
void salvarImagem(Imagem *imagem);
void liberarAD(Imagem *imagem, Pixel **pixels);
void executar(char entrada[10], Imagem *imagem);

#endif