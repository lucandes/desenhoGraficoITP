#include "default.h"
#include "struct.h"
#include "safestdlib.h"

#include <stdio.h>
#include <string.h>

/****************************************************
Função: criarImagem
Parâmetros: nenhum
Retorno: estrutura Imagem

Descrição: serve para inicializar uma nova imagem, recebendo as entradas necessárias
e retornando os valores atribuídos em uma estrutura do tipo Imagem.
*****************************************************/
Imagem criarImagem(){
	Imagem imagem;

	/* atribuindo configurações padrão */
	strcpy(imagem.id, "P3");
	imagem.max = 255;

	/* leitura das dimensões da imagem a ser criada */
	scanf("%d %d", &imagem.lar, &imagem.alt);
	imagem.numDePixels = imagem.lar * imagem.alt;

	/* alocação dinâmica da matriz pixels */
	imagem.pixels = (Pixel **) malloc(imagem.lar * sizeof(Pixel *));
	if (imagem.pixels == NULL)
		exit(1);
	for (int i=0; i<imagem.lar; i++){
		imagem.pixels[i] = (Pixel *) calloc(imagem.alt, sizeof(Pixel));
		if (imagem.pixels[i] == NULL){
			exit(1);
		}
	}

	return imagem;
}

/****************************************************
Função: 
Parâmetros: 
Retorno: 

Descrição:
*****************************************************/
void salvarImagem(Imagem *imagem){
	scanf("%s", (char *) &imagem->nomeDoArquivo);

	imagem->arquivo = fopen(imagem->nomeDoArquivo, "w");

	fprintf(imagem->arquivo, "%s\n", imagem->id);
	fprintf(imagem->arquivo, "%d %d\n", imagem->lar, imagem->alt);
	fprintf(imagem->arquivo, "%d\n", imagem->max);

	for (int x = 0; x < imagem->lar; x++){
		for (int y = 0; y < imagem->alt; y++){
			fprintf(imagem->arquivo, "%d %d %d\n",
				imagem->pixels[x][y].r,
				imagem->pixels[x][y].g,
				imagem->pixels[x][y].b);
		}
	}

	fclose(imagem->arquivo);
}

/****************************************************
Função: liberaAD
Parâmetros: ponteiro de estrutura Imagem, matriz do tipo Pixel
Retorno: nenhum

Descrição: libera toda alocação dinâmica utilizada ao longo do
programa, esta função será chamada quando o usuário desejar sair.
*****************************************************/
void liberarAD(Imagem *imagem, Pixel **pixels){
	for (int i = 0; i < imagem->lar; ++i)
		free(pixels[i]);
	free(pixels);
}

/****************************************************
Função: executar
Parâmetros: entrada do usuário, estrutura tipo Imagem
Retorno: nenhum

Descrição: lê e interpreta a entrada do usuário caso a entrada
seja compatível com um comando do programa.
*****************************************************/
void executar(char entrada[10], Imagem *imagem){
	if (!strcmp(entrada, "help")){
		printf("--------------------------------------\n");
		printf("help    (imprime a lista de comandos)\n");
		printf("image   (cria uma imagem)\n");
		printf("color   (muda a cor do pincel)\n");
		printf("clear   (preenche toda a imagem)\n");
		printf("save    (salva em um arquivo ppm)\n");
		printf("open    (carrega uma imagem ppm)\n\n");
	}
	else if (!strcmp(entrada, "clear")){
		int r,g,b;
		scanf("%d %d %d", &r, &g, &b);

		for (int i = 0; i < imagem->lar; ++i)
			for (int j = 0; j < imagem->alt; ++j){
				imagem->pixels[i][j].r = r;
				imagem->pixels[i][j].g = g;
				imagem->pixels[i][j].b = b;
			}
	}
	else if (!strcmp(entrada, "linha")){
		printf("ainda nao implementado\n");
	}
}