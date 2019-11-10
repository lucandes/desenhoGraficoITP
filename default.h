#include "struct.h"

#ifndef DEFAULT_H
#define DEFAULT_H

void liberarAD(Imagem *imagem, Pixel **pixels);
void mudarCor(Imagem *imagem);
void limparImagem(Imagem *imagem);
void limparBuffer(void);
void limpaConsole(void);
void executar(char entrada[10], Imagem *imagem, int imagemAberta);

#endif