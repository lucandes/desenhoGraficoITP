#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "func.h"

void imprimirApresentacao();

int main(){
	/* inicialização de variáveis */
	char entrada[10];     // recebe o comando do usuario
	int sair = 0;         // indica se o usuraio deseja sair do programa
	int imagemAberta = 0; // indica se existe uma imagem aberta no programa
	Imagem imagem;        // receberá todas as informações correspondentes a imagem


	imprimirApresentacao();
	do {
		/* leitura do comando */
		setbuf(stdin, NULL);
		scanf("%s", entrada);

		/* aqui são checados apenas os comandos principais */
		if (!strcmp(entrada, "imagem")){
			imagem = criarImagem();
			imagemAberta = 1;
		}

		else if (!strcmp(entrada, "abrir")){
			imagem = abrirImagem();
			if (imagem.arquivo == NULL){
				printf("Erro: nao foi possivel abrir a imagem\n");
				continue;
			}
			imagemAberta = 1;
		}

		else if (!strcmp(entrada, "sair")){
			if (imagemAberta)
				liberarAD(&imagem, imagem.pixels);
			
			sair = 1;
		}

		else if (!strcmp(entrada, "salvar")){
			if (!imagemAberta){
				printf("Erro: imagem nao aberta\n");
				limparBuffer();
				continue;
			}

			salvarImagem(&imagem);
		}
		
		else {
			executar(entrada, &imagem, imagemAberta);
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