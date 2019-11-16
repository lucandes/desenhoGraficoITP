#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "func.h"

void imprimirApresentacao();

int main(){
	/* inicialização de variáveis */
	char entrada[10];       // recebe o comando do usuário
	int sair = 0;           // indica se o usuário deseja sair do programa
	int imagemAberta = 0;   // indica se existe uma imagem aberta no programa
	Imagem imagem;          // receberá todas as informações correspondentes a imagem
	FILE *arqEspecificacao; // armazena o arquivo de especificação
	int temArquivo = 0;     // se houver um arquivo de especificação 'temArquivo' será 1
	int eof;                // se o arquivo de especificação chegou ao fim 'eof' será 1

	imprimirApresentacao();
	do {
		/* leitura do comando */
		if (temArquivo){
			eof = lerDoArquivo(arqEspecificacao, entrada);

			/* se o arquivo chegou ao fim */
			if (eof){
				printf("Arquivo lido com sucesso!\n");
				temArquivo = 0;
				continue;
			}

			printf("%s", entrada);
		}
		else {
			setbuf(stdin, NULL);
			scanf("%s", entrada);
		}

	

		/* aqui são checados apenas os comandos principais */
		if (!strcmp(entrada, "imagem") || !strcmp(entrada, "image")){
			if (!temArquivo){
				scanf(" %d", &imagem.lar);
				scanf(" %d", &imagem.alt);
			}
			else {
				fscanf(arqEspecificacao, " %d %d\n", &imagem.lar, &imagem.alt);
				printf(" %d %d\n", imagem.lar, imagem.alt);
			}

			imagem = criarImagem(&imagemAberta, imagem.lar, imagem.alt);
		}

		else if (!strcmp(entrada, "abrir") || !strcmp(entrada, "open")){
			if (!temArquivo){
				getc(stdin); // pegando o espaço
				fgets(imagem.caminho, 100, stdin);
			}
			else {
				fgets(imagem.caminho, 100, arqEspecificacao);
				printf(" %s\n", imagem.caminho);
			}

			imagem = abrirImagem(&imagemAberta, imagem.caminho);
			if (!imagemAberta){
				printf("Erro: nao foi possivel abrir a imagem\n");
				continue;
			}
		}

		else if (!strcmp(entrada, "sair") || !strcmp(entrada, "quit")){
			if (imagemAberta){
				liberarAD(&imagem, imagem.pixels);

				/* liberando alocação de polígonos */
				for (int i = 0; i < imagem.desenho.numPoligonos; ++i)
					free(imagem.desenho.poligonos[i].linhas);
			}
			if (temArquivo){
				fclose(arqEspecificacao);
				printf("\n"); // quebra de linha final
			}
			
			sair = 1;
		}

		else if (!strcmp(entrada, "salvar") || !strcmp(entrada, "save")){
			if (!imagemAberta){
				printf("Erro: imagem nao aberta\n");
				limparBuffer();
				continue;
			}

			if (!temArquivo){
				limparBuffer();
				printf("  Nome do arquivo: ");
				fgets(imagem.nomeDoArquivo, 50, stdin);
			}
			else {
				fgets(imagem.nomeDoArquivo, 50, arqEspecificacao);
				printf(" %s\n", imagem.nomeDoArquivo);
			}

			imagem.nomeDoArquivo[strlen(imagem.nomeDoArquivo) - 1] = '\0';
			salvarImagem(&imagem);
		}

		else if (!strcmp(entrada, "ler") || !strcmp(entrada, "read")){
			scanf("%s", imagem.caminho);

			arqEspecificacao = lerArquivo(&temArquivo, imagem);

			if (!temArquivo){
				printf("Erro: caminho de arquivo invalido\n");
				continue;
			}
		}
		
		else {
			executar(entrada, &imagem, imagemAberta, temArquivo, arqEspecificacao);
		}

	} while (!sair);

	return 0;
}

void imprimirApresentacao(){
	limpaConsole();
	printf("*************************************\n");
	printf("DESENHO GRAFICO - PROJETO UNIDADE III\n");
	printf("INTRODUCAO AS TECNICAS DE PROGRAMACAO\n\n");
	printf("Aluno: Lucas Fernandes de Oliveira\n");
	printf("*************************************\n\n");
}