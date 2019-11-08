#include "default.h"
#include "structs.h"
/****************************************************
Função: criarImagem
Parâmetros: ponteiro de inteiro imagemAberta, ponteiro de ponteiro do tipo Pixel
Retorno: estrutura Imagem

Descrição: serve para inicializar uma nova imagem, recebendo as entradas necessárias
e retornando os valores atribuídos em uma estrutura do tipo Imagem.
*****************************************************/
Imagem criarImagem(int *imagemAberta, Pixel **pixels){
	Imagem imagem;

	scanf("%d %d", &imagem.lar, &imagem.alt);
	imagem.numDePixels = imagem.lar * imagem.alt;

	pixels = (Pixel **) malloc(imagem.lar * sizeof(Pixel *));
	if (pixels == NULL)
		exit(1);

	for (int i=0; i<imagem.lar; i++){
		pixels[i] = (Pixel *) calloc(imagem.alt, sizeof(Pixel));
		
		if (pixels[i] == NULL){
			printf("falha de alocação\n");
			exit(1);
		}
	}

	*imagemAberta = 1;

	return imagem;
}

/****************************************************
Função: liberaAD
Parâmetros: ponteiro de estrutura Imagem, matriz do tipo Pixel
Retorno: nenhum

Descrição: libera toda alocação dinâmica utilizada ao longo do
programa, esta função será chamada quando o usuário desejar sair.
*****************************************************/
void liberaAD(Imagem *imagem, Pixel **pixels){
	for (int i = 0; i < imagem->lar; ++i)
		free(pixels[i]);
	printf("liberado\n");
	free(pixels);
}