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

		limparImagem(imagem, cor, imagemAberta, temArquivo, arqEspecificacao);
	}

	/* comando linha */
	else if (!strcmp(entrada, "linha") || !strcmp(entrada, "line")){
		Ponto pontos[2];
		lerPontos(pontos, 2, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		/* verifica se as entradas são válidas */
		int valido;
		valido = verificaCoordenadas(pontos[0].x, pontos[0].y, imagem) &&
				 verificaCoordenadas(pontos[1].x, pontos[1].y, imagem);
		if (!valido)
			return;
		
		Linha l;
		l = criarLinha(pontos, imagem->cor, imagem);

		/* adicionando linha à estrutura linha */
		int n = imagem->desenho.numLinhas++;
		imagem->desenho.linhas[n] = l;

		/* adicionando a linha à ordem */
		int i = imagem->desenho.numOrdem++;
		imagem->desenho.ordem[i] = 1; // 1 representa linhas
	}

	/* comando retangulo */
	else if (!strcmp(entrada, "retangulo") || !strcmp(entrada, "rect")){
		/* leitura do ponto inicial e das dimensões */
		Ponto pontoInicial;
		lerPontos(&pontoInicial, 1, temArquivo, arqEspecificacao);
		int dimensoes[2];
		lerInteiros(dimensoes, 2, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		/* definindo coordenadas dos pontos a partir das dimensões */
		int numFaces = 4;
		Ponto pontos[numFaces];
		gerarPontosRet(pontoInicial, pontos, dimensoes);
		
		Poligono pol = criarPoligono(numFaces, pontos, imagem);

		int n = imagem->desenho.numPoligonos++;
		imagem->desenho.poligonos[n] = pol;

		/* adicionando o poligono à ordem */
		int m = imagem->desenho.numOrdem++;
		imagem->desenho.ordem[m] = 2; // 2 representa poligonos
	}

	/* comando poligono */
	else if (!strcmp(entrada, "poligono") || !strcmp(entrada, "polygon")){
		int numFaces; 
		lerInteiros(&numFaces, 1, temArquivo, arqEspecificacao);

		/* verificando se o número de faces é válido */
		if (numFaces < 3 || numFaces > 100){
			printf("Erro: numero inválido de faces inserido\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		Ponto pontos[numFaces];
		lerPontos(pontos, numFaces, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		Poligono pol = criarPoligono(numFaces, pontos, imagem);

		int n = imagem->desenho.numPoligonos++;
		imagem->desenho.poligonos[n] = pol;

		/* adicionando o poligono à ordem */
		int m = imagem->desenho.numOrdem++;
		imagem->desenho.ordem[m] = 2; // 2 representa poligonos
	}

	/* comando circulo */
	else if (!strcmp(entrada, "circulo") || !strcmp(entrada, "circle")){
		Ponto centro;
		lerPontos(&centro, 1, temArquivo, arqEspecificacao);

		int raio;
		lerInteiros(&raio, 1, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		Circulo c = criarCirculo(centro, raio, imagem->cor, imagem);

		/* adicionando aos desenhos da imagem */
		int n = imagem->desenho.numCirculos++;
		imagem->desenho.circulos[n] = c;

		/* adicionando o circulo a ordem */
		int i = imagem->desenho.numOrdem++;
		imagem->desenho.ordem[i] = 3; // 3 representa círculos
	}

	/* comando preencher */
	else if (!strcmp(entrada, "preencher") || !strcmp(entrada, "fill")){
		Ponto p;
		lerPontos(&p, 1, temArquivo, arqEspecificacao);

		Cor novaCor;
		novaCor = criarCor(temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		Preencher fill = criarPreenchimento(p, novaCor, imagem);

		/* inserindo preenchimento na estrutura de desenho */
		int n = imagem->desenho.numPreencher++;
		imagem->desenho.preencher[n] = fill;

		/* adicionando o preenchimento à ordem */
		int i = imagem->desenho.numOrdem++;
		imagem->desenho.ordem[i] = 4; // 4 representa preencher
	}

	/* comando salvar */
	else if (!strcmp(entrada, "salvar") || !strcmp(entrada, "save")){
		if (!*autosave)
			lerString(imagem->nomeDoArquivo, 100, temArquivo, arqEspecificacao);
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
	}
	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = moverPoligono(dnum, dist, imagem);
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = moverCirculo(dnum, dist, imagem);
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = moverPreencher(dnum, dist, imagem);
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
	}
	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = copiarPoligono(dnum, imagem);
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = copiarCirculo(dnum, imagem);
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = copiarPreencher(dnum, imagem);
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
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}

	int retorno;

	/********************* verificando tipo de desenho *********************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		retorno = removerLinha(dnum, imagem);
	}

	/* retangulos e poligonos gerais são alterados da mesma forma */
	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect") ||
		!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		retorno = removerPoligono(dnum, imagem);
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		retorno = removerCirculo(dnum, imagem);
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		retorno = removerPreencher(dnum, imagem);
	}

	if (!retorno){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	printf("Erro: o desenho selecionado nao existe\n");
}