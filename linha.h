#ifndef LINHA_H
#define LINHA_H

#include "struct.h"
#include "func.h"

Linha criarLinha(Ponto pontos[2], Cor cor, Imagem *imagem);
void inserirLinha(Linha linha, Imagem *imagem);

#endif