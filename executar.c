#include "executar.h"

/****************************************************
Função: executar
Parâmetros: entrada do usuário, estrutura tipo Imagem
Retorno: nenhum

Descrição: lê e interpreta a entrada do usuário, caso a entrada
seja compatível com um comando do programa, este será executado.
*****************************************************/
void executar(char entrada[10], int *autosave, Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao){
	if (!imagemAberta){
		printf("Erro: nao existe uma imagem aberta\n");
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}
	/* comando limpar */
	if (!strcmp(entrada, "limpar") || !strcmp(entrada, "clear")){
		Cor cor = criarCor(temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);
		limparImagem(imagem, cor);
	}

	/* comando linha */
	else if (!strcmp(entrada, "linha") || !strcmp(entrada, "line")){
		lerLinha(temArquivo, arqEspecificacao, imagem);
	}

	/* comando retangulo */
	else if (!strcmp(entrada, "retangulo") || !strcmp(entrada, "rect")){
		lerRetangulo(temArquivo, arqEspecificacao, imagem);
	}

	/* comando poligono */
	else if (!strcmp(entrada, "poligono") || !strcmp(entrada, "polygon")){
		lerPoligono(temArquivo, arqEspecificacao, imagem);
	}

	/* comando circulo */
	else if (!strcmp(entrada, "circulo") || !strcmp(entrada, "circle")){
		lerCirculo(temArquivo, arqEspecificacao, imagem);
	}

	/* comando preencher */
	else if (!strcmp(entrada, "preencher") || !strcmp(entrada, "fill")){
		lerPreencher(temArquivo, arqEspecificacao, imagem);
	}

	/* comando salvar */
	else if (!strcmp(entrada, "salvar") || !strcmp(entrada, "save")){
		if (!*autosave){
			lerString(imagem->nomeDoArquivo, 100, temArquivo, arqEspecificacao);
			limparBuffer(temArquivo, arqEspecificacao);
		}
		salvarImagem(imagem);
		printf("imagem salva em './galeria/%s'\n", imagem->nomeDoArquivo);
	}

	/* comando listar desenhos */
	else if (!strcmp(entrada, "listar") || !strcmp(entrada, "list")){
		listarDesenhos(imagem->desenho, temArquivo);
	}

	/* comando salvar automaticamente */
	else if (!strcmp(entrada, "autosave")){
		char nome[50];
		lerString(nome, 100, temArquivo, arqEspecificacao);

		if (!strcmp(nome, "cancelar")){
			if (*autosave == 1){
				*autosave = 0;
				printf("Salvamento automatico encerrado\n");
				return;
			}
			printf("Erro: salvamento automatico nao foi habilitado\n");
			return;
		}

		strcpy(imagem->nomeDoArquivo, nome);
		*autosave = 1;
	}

	/* comando editar desenhos */
	else if (!strcmp(entrada, "editar") || !strcmp(entrada, "edit")){
		char d[15];
		int dnum;

		lerString(d, 15, temArquivo, arqEspecificacao);
		lerInteiros(&dnum, 1, temArquivo, arqEspecificacao);

		editar(d, dnum, temArquivo, arqEspecificacao, imagem);
	}

	/* comando mover desenhos */
	else if (!strcmp(entrada, "mover") || !strcmp(entrada, "move")){
		char d[15];
		int dnum;
		int dist[2];

		lerString(d, 15, temArquivo, arqEspecificacao);
		lerInteiros(&dnum, 1, temArquivo, arqEspecificacao);
		lerInteiros(dist, 2, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		mover(d, dnum, dist, temArquivo, arqEspecificacao, imagem);
	}

	/* comando mover desenhos */
	else if (!strcmp(entrada, "copiar") || !strcmp(entrada, "copy")){
		char d[15];
		int dnum;

		lerString(d, 15, temArquivo, arqEspecificacao);
		lerInteiros(&dnum, 1, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		copiar(d, dnum, temArquivo, arqEspecificacao, imagem);
	}

		/* comando remover desenhos */
	else if (!strcmp(entrada, "remover") || !strcmp(entrada, "remove")){
		char d[15];
		int dnum;

		lerString(d, 15, temArquivo, arqEspecificacao);
		lerInteiros(&dnum, 1, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		remover(d, dnum, temArquivo, arqEspecificacao, imagem);
	}

	/* comando inválido */
	else {
		if (temArquivo) printf("\n"); // quebra de linha final
		printf("Erro: '%s' comando invalido. Digite 'ajuda' para ver a lista de comandos\n", entrada);
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}

	/* autosave */
	if (*autosave)
		salvarImagem(imagem);
}







void editar(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	/* verificando se existem desenhos para mover */
	if (imagem->desenho.numOrdem == 0){
		printf("Erro: a imagem nao possui desenhos\n");
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}

	/********************* verificando tipo de desenho *********************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		editarLinha(dnum, imagem, temArquivo, arqEspecificacao);
	}

	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect")){
		editarRetangulo(dnum, imagem, temArquivo, arqEspecificacao);
	}

	else if (!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		editarPoligono(dnum, imagem, temArquivo, arqEspecificacao);
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		editarCirculo(dnum, imagem, temArquivo, arqEspecificacao);
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		editarPreencher(dnum, imagem, temArquivo, arqEspecificacao);
	}

	else {
		printf("Erro: o tipo de desenho inserido nao existe\n");
	}

	limparBuffer(temArquivo, arqEspecificacao);
}

void mover(char desenho[15], int dnum, int dist[2], int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	/* verificando se existem desenhos para mover */
	if (imagem->desenho.numOrdem == 0){
		printf("Erro: a imagem nao possui desenhos\n");
		return;
	}

	int retorno;

	/********************* verificando tipo de desenho *********************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		retorno = moverLinha(dnum, dist, imagem);
		return;
	}
	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = moverPoligono(dnum, dist, imagem);
		return;
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = moverCirculo(dnum, dist, imagem);
		return;
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = moverPreencher(dnum, dist, imagem);
		return;
	}

	if (!retorno){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	printf("Erro: o desenho selecionado nao existe\n");
}

void copiar(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	/* verificando se existem desenhos para mover */
	if (imagem->desenho.numOrdem == 0){
		printf("Erro: a imagem nao possui desenhos\n");
		return;
	}

	int retorno;

	/********************* verificando tipo de desenho *********************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		retorno = copiarLinha(dnum, imagem);
		return;
	}
	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = copiarPoligono(dnum, imagem);
		return;
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = copiarCirculo(dnum, imagem);
		return;
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = copiarPreencher(dnum, imagem);
		return;
	}

	if (!retorno){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	printf("Erro: o desenho selecionado nao existe\n");
}

void remover(char desenho[15], int dnum, int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	/* verificando se existem desenhos para mover */
	if (imagem->desenho.numOrdem == 0){
		printf("Erro: a imagem nao possui desenhos\n");
		return;
	}

	int retorno;

	/********************* verificando tipo de desenho *********************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		retorno = removerLinha(dnum, imagem);
		return;
	}

	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = removerPoligono(dnum, imagem);
		return;
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = removerCirculo(dnum, imagem);
		return;
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = removerPreencher(dnum, imagem);
		return;
	}

	if (!retorno){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	printf("Erro: o desenho selecionado nao existe\n");
}