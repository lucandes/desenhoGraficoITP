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

void executar(char entrada[10], int *autosave, Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao);
void editar(int temArquivo, FILE *arqEspecificacao, Imagem *imagem);

#endif