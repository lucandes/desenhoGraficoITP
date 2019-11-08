#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "default.h"

void imprimirApresentacao();

int main(){
	char entrada[10];
	int sair = 0;
	int imagemAberta = 0;
	Imagem imagem;


	imprimirApresentacao();
	do {
		setbuf(stdin, NULL);
		scanf("%s", entrada);

		if (!strcmp(entrada, "imagem"))
			imagem = criarImagem(&imagemAberta, imagem.pixels);

		else if (!strcmp(entrada, "sair")){
			liberarAD(&imagem, imagem.pixels);
			sair = 1;
		}
		else
			printf("comando inexistente\n");

	} while (!sair);

	return 0;
}

void imprimirApresentacao(){
	printf("*************************************\n");
	printf("DESENHO GRAFICO - PROJETO UNIDADE III\n");
	printf("INTRODUCAO AS TECNICAS DE PROGRAMACAO\n\n");
	printf("Autor: Lucas Fernandes de Oliveira\n");
	printf("*************************************\n");
}