#ifndef IMAGEM_H
#define IMAGEM_H

#include "struct.h"
#include "func.h"
#include "linha.h"
#include "poligono.h"
#include "circulo.h"

Imagem criarImagem(int *imagemAberta, int lar, int alt);
Imagem abrirImagem(int *imagemAberta, char caminho[100]);
void salvarImagem(Imagem *imagem);
void limparImagem(Imagem *imagem, Cor cor, int imagemAberta, int temArquivo, FILE *arqEspecificacao);
Preencher criarPreenchimento(Ponto p, Cor novaCor, Imagem *imagem);
int checaImagem(int imagemAberta, int temArquivo, FILE *arq);
Desenho criarDesenho(void);
void listarDesenhos(Desenho d, int temArquivo);
void inserirDesenhos(Imagem *imagem);
void inserirPreenchimento(int x, int y, Preencher p, Imagem *imagem);

#endif