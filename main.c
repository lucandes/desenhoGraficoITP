#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "func.h"

void imprimirApresentacao();

int main(){
	/* inicialização de variáveis */
	char entrada[10];          // recebe o comando do usuario
	int sair = 0;              // indica se o usuraio deseja sair do programa
	int imagemAberta = 0;      // indica se existe uma imagem aberta no programa
	Imagem imagem;             // receberá todas as informações correspondentes a imagem
	FILE *arqEspecificacao;    // guarda o arquivo de especificação, se existir
	int lerStdin = 1;          // se houver um arquivo de especificação, ler será 0

	/* variáveis de leitura */
	char nomeDoArquivo[50];
	char c;
	int eof = 0;

	imprimirApresentacao();
	do {
		/* leitura do comando */
		if (lerStdin){
			setbuf(stdin, NULL);
			scanf("%s", entrada);
		}

		else {
			c = 'a';
			for(int i=0; c != ' ' && c != '\n'; i++){
				c = getc(arqEspecificacao);
				c == ' ' || c == '\n' ? (entrada[i] = '\0') : (entrada[i] = c);

				if (feof(arqEspecificacao)){
					printf("Arquivo lido com sucesso!\n");
					eof = 1;
					break;
				}
			}

			if (eof){
				lerStdin = 1;
				continue;
			}

			printf("%s\n", entrada);
		}

		

		/* aqui são checados apenas os comandos principais */
		if (!strcmp(entrada, "imagem") || !strcmp(entrada, "image")){
			/* se nao houver arquivo de especificação */
			if (lerStdin){
				printf("  Largura: ");
				scanf(" %d", &imagem.lar);

				printf("  Altura:  ");
				scanf(" %d", &imagem.alt);
			}
			else {
				fscanf(arqEspecificacao, " %d %d\n", &imagem.lar, &imagem.alt);
			}

			imagem = criarImagem(&imagemAberta, imagem.lar, imagem.alt);
		}

		else if (!strcmp(entrada, "abrir") || !strcmp(entrada, "open")){
			/* se nao houver arquivo de espeicação */
			if (lerStdin){
				printf("  Caminho: ");
				fgets(imagem.caminho, 100, stdin);
			}
			else {
				fgets(imagem.caminho, 100, arqEspecificacao);
				printf("caminho lido: %s\n", imagem.caminho);
			}

			imagem = abrirImagem(&imagemAberta, imagem.caminho);
			if (!imagemAberta){
				printf("Erro: nao foi possivel abrir a imagem\n");
				continue;
			}
		}

		else if (!strcmp(entrada, "sair") || !strcmp(entrada, "quit")){
			if (imagemAberta)
				liberarAD(&imagem, imagem.pixels);
			if (lerStdin){
				fclose(arqEspecificacao);
			}
			
			sair = 1;
		}

		else if (!strcmp(entrada, "salvar") || !strcmp(entrada, "save")){
			if (!imagemAberta){
				printf("Erro: imagem nao aberta\n");
				limparBuffer();
				continue;
			}

			if (lerStdin){
				limparBuffer();
				printf("  Nome do arquivo: ");
				fgets(imagem.nomeDoArquivo, 50, stdin);
			}
			else {
				fgets(imagem.nomeDoArquivo, 50, arqEspecificacao);
			}

			imagem.nomeDoArquivo[strlen(imagem.nomeDoArquivo) - 1] = '\0';
			salvarImagem(&imagem);
		}

		else if (!strcmp(entrada, "ler") || !strcmp(entrada, "read")){
			limparBuffer();
			printf("  Caminho do arquivo: ");
			fgets(imagem.caminho, 100, stdin);

			arqEspecificacao = lerArquivo(&lerStdin, imagem);

			if (arqEspecificacao == NULL){
				printf("Erro: caminho de arquivo invalido\n");
				continue;
			}
			else
				lerStdin = 0;
		}
		
		else {
			executar(entrada, &imagem, imagemAberta, lerStdin, arqEspecificacao);
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