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
	for (int i = 0; i < imagem->alt; ++i)
		free(pixels[i]);
	free(pixels);
}

/****************************************************
Função: mudarCor
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: altera a cor do pincel da imagem
*****************************************************/
void mudarCor(Imagem *imagem){
	Cor novaCor;
	novaCor = criarCor();

		imagem->cor.r = novaCor.r;
		imagem->cor.g = novaCor.g;
		imagem->cor.b = novaCor.b;
}

/****************************************************
Função: limparImagem
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: limpa toda a imagem para uma cor especificada
*****************************************************/
void limparImagem(Imagem *imagem){
	Cor cor = criarCor();

	for (int i = 0; i < imagem->alt; ++i)
		for (int j = 0; j < imagem->lar; ++j){
			imagem->pixels[i][j].r = cor.r;
			imagem->pixels[i][j].g = cor.g;
			imagem->pixels[i][j].b = cor.b;
		}

	/* todos os desenhos serão apagados */
	imagem->desenho = criarDesenho();
}

/****************************************************
Função: limparBuffer
Parâmetros: nenhum
Retorno: nenhum

Descrição: responsável por limpar o buffer, deve ser chamada
após um comando inválido, desconsiderando todas as demais 
informações inseridas pelo usuário
*****************************************************/
void limparBuffer(void){
	/* lê até encontrar uma quebra de linha */
	while (getchar() != '\n');
}

/****************************************************
Função: limparConsole
Parâmetros: nenhum
Retorno: nenhum
Referência: https://pt.stackoverflow.com/questions/231870/descobrir-o-sistema-operacional-da-maquina-em-c

Descrição: responsável por limpar o console
*****************************************************/
void limpaConsole(void){
	#ifdef _WIN32 
	system("cls");
	#elif WIN32 
	system("cls");
	#else
	system("clear");
	return;
	#endif
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
		printf("---------------------------------------\n");
		printf("ajuda    (imprime a lista de comandos)\n");
		printf("imagem   (gera uma nova imagem)\n");
		printf("cor      (altera a cor atual do pincel)\n");
		printf("linha    (gera uma nova linha)\n");
		printf("desenhos (imprime os desenhos da imagem\n");
		printf("limpar   (preenche toda a imagem)\n");
		printf("salvar   (salva em um arquivo ppm)\n");
		printf("abrir    (carrega uma imagem ppm)\n\n");
		printf("sair     (encerra o programa)\n");
	}

	/* comando limpar */
	else if (!strcmp(entrada, "limpar")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		limparImagem(imagem);
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
		// pode ser alterado com a imagem fechada
		mudarCor(imagem);
	}

	/* comando desenhos */
	else if (!strcmp(entrada, "desenhos")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		listarDesenhos(imagem->desenho);
	}

	/* comando inválido */
	else {
		printf("Erro: comando invalido. Digite 'ajuda' para ver a lista de comandos\n");
		limparBuffer();
	}
}