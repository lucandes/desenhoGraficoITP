#ifndef EXECUTAR_H
#define EXECUTAR_H

#include <stdio.h>
#include <stdlib.h>

#include "func.h"
#include "struct.h"
#include "imagem.h"
#include "linha.h"
#include "poligono.h"
#include "circulo.h"
#include "preencher.h"

void executar(char entrada[10], int *autosave, Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao);
void editar(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void mover(char desenho[15], int dnum, int dist[2], int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void copiar(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void remover(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem);

#endif