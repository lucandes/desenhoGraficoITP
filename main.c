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
			eof = lerArquivo(arqEspecificacao, entrada);

			/* se o arquivo chegou ao fim */
			if (eof == 1){
				printf("Arquivo lido com sucesso!\n\n");
				temArquivo = 0;
				continue;
			}
			/* se encontrou um comentário */
			else if (eof == -1){
				continue;
			}

			printf("%s", entrada);
		}
		else {
			setbuf(stdin, NULL);
			scanf("%s", entrada);
		}

	

		/* aqui são checados apenas os comandos que não dependem de imagem aberta para serem executados */

		if (!strcmp(entrada, "imagem") || !strcmp(entrada, "image")){
			/* se já existir uma imagem aberta, sua alocação será liberada */
			if (imagemAberta)
				liberarAD(&imagem, imagem.pixels);

			/* leitura das dimensões da imagem */
			int dim[2];
			lerInteiros(dim, 2, temArquivo, arqEspecificacao);
			limparBuffer(temArquivo, arqEspecificacao);

			imagem = criarImagem(&imagemAberta, dim[0], dim[1]);
		}

		else if (!strcmp(entrada, "abrir") || !strcmp(entrada, "open")){
			/* se já existir uma imagem aberta, sua alocação será liberada */
			if (imagemAberta)
				liberarAD(&imagem, imagem.pixels);

			/* leitura do caminho do arquivo */
			if (!temArquivo){
				getc(stdin); // pegando o espaço entre o comando e o nome do arquivo
				fgets(imagem.caminho, 100, stdin);
				imagem.caminho[strlen(imagem.caminho) - 1] = '\0';
			}
			else {
				fgets(imagem.caminho, 100, arqEspecificacao);
				imagem.caminho[strlen(imagem.caminho) - 1] = '\0';
				printf(" %s\n", imagem.caminho);
			}

			imagem = abrirImagem(&imagemAberta, imagem.caminho);
			
			if (!imagemAberta){
				printf("Erro: nao foi possivel abrir a imagem\n");
				continue;
			}
		}

		else if (!strcmp(entrada, "sair") || !strcmp(entrada, "quit")){
			/* limpa alocação dinâmica */
			if (imagemAberta)
				liberarAD(&imagem, imagem.pixels);

			/* fecha o arquivo de especificação */
			if (temArquivo){
				fclose(arqEspecificacao);
				printf("\n"); // quebra de linha final
			}
			
			sair = 1;
		}

		else if (!strcmp(entrada, "ler") || !strcmp(entrada, "read")){
			/* leitura do caminho do arquivo de especificação */
			getc(stdin); // pegando o espaço entre o comando e o nome do arquivo
			fgets(imagem.caminho, 100, stdin);
			imagem.caminho[ strlen(imagem.caminho) - 1 ] = '\0'; // removendo o '\n' do final da string

			arqEspecificacao = novoArquivo(&temArquivo, imagem);

			if (!temArquivo){
				printf("Erro: caminho de arquivo invalido\n");
				continue;
			}
		}

		else if (!strcmp(entrada, "cor") || !strcmp(entrada, "color")){
			Cor cor;
			cor = criarCor(temArquivo, arqEspecificacao);
			limparBuffer(temArquivo, arqEspecificacao);

			imagem.cor = cor;
		}

		else if (!strcmp(entrada, "ajuda") || !strcmp(entrada, "help")){
			printAjuda(temArquivo);
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
	printf("*************************************\n");
	printf("Digite 'ajuda' para ver a lista de comandos\n\n");
}