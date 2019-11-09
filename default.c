#include "default.h"
#include "struct.h"
#include "safestdlib.h"
#include "linha.h"

#include <stdio.h>
#include <string.h>


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
Função: 
Parâmetros: 
Retorno: 

Descrição:
*****************************************************/
void limparBuffer(void){
	while (getchar() != '\n');
}
/****************************************************
Função: executar
Parâmetros: entrada do usuário, estrutura tipo Imagem
Retorno: nenhum

Descrição: lê e interpreta a entrada do usuário caso a entrada
seja compatível com um comando do programa.
*****************************************************/
void executar(char entrada[10], Imagem *imagem, int imagemAberta){
	/* comando ajuda */
	if (!strcmp(entrada, "ajuda")){
		printf("--------------------------------------\n");
		printf("ajuda    (imprime a lista de comandos)\n");
		printf("imagem   (cria uma imagem)\n");
		printf("cor   (muda a cor do cor)\n");
		printf("limpar   (preenche toda a imagem)\n");
		printf("salvar   (salva em um arquivo ppm)\n");
		printf("abrir    (carrega uma imagem ppm)\n\n");
	}
	/* comando limpar */
	else if (!strcmp(entrada, "limpar")){
		if (!imagemAberta){
			limparBuffer();
			return;
		}

		int r,g,b;
		scanf("%d %d %d", &r, &g, &b);

		for (int i = 0; i < imagem->lar; ++i)
			for (int j = 0; j < imagem->alt; ++j){
				imagem->pixels[i][j].r = r;
				imagem->pixels[i][j].g = g;
				imagem->pixels[i][j].b = b;
			}
	}
	/* comando linha */
	else if (!strcmp(entrada, "linha")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}
		
		criarLinha(imagem);
	}
	/* comando cor */
	else if (!strcmp(entrada, "cor")){
		scanf("%d %d %d",
			&imagem->cor.r,
			&imagem->cor.g,
			&imagem->cor.b);
	}
	else if (!strcmp(entrada, "pintar")){
		int x,y;
		scanf("%d %d", &x, &y);
		pintarPixel(x, y, imagem->pixels, imagem->cor);
	}
	else if (!strcmp(entrada, "desenhos")){
		listarDesenhos(imagem->desenho);
	}
	/* comando inválido */
	else {
		printf("Erro: comando invalido. Digite 'ajuda' para ver a lista de comandos\n");
		limparBuffer();
	}
}