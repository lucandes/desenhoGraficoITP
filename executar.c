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
		if (!*autosave){
			char *nome = imagem->nomeDoArquivo;

			if (!temArquivo){
				getc(stdin); // pegando o espaço entre o comando e o nome do arquivo
				fgets(nome, 50, stdin);
				nome[strlen(nome) - 1] = '\0';
			}
			else {
				fgets(nome, 50, arqEspecificacao);
				if (nome[strlen(nome) - 1] == '\n')
					nome[strlen(nome) - 1] = '\0';
				printf(" %s\n", nome);
			}
		}

		salvarImagem(imagem);
	}

	/* comando listar desenhos */
	else if (!strcmp(entrada, "listar") || !strcmp(entrada, "list")){
		listarDesenhos(imagem->desenho, temArquivo);
	}

	/* comando editar desenhos */
	else if (!strcmp(entrada, "editar") || !strcmp(entrada, "edit")){
		/* verificando se existem desenhos para editar */
		if (imagem->desenho.numOrdem == 0){
			printf("Erro: a imagem nao possui desenhos\n");
			return;
		}

		editar(temArquivo, arqEspecificacao, imagem);
	}

	/* comando salvar automaticamente */
	else if (!strcmp(entrada, "autosave")){
		char *nome = imagem->nomeDoArquivo;

		if (!temArquivo){
			getc(stdin); // pegando o espaço entre o comando e o nome do arquivo
			fgets(nome, 50, stdin);
			nome[strlen(nome) - 1] = '\0';
		}
		else {
			fgets(nome, 50, arqEspecificacao);
			if (nome[strlen(nome) - 1] == '\n')
				nome[strlen(nome) - 1] = '\0';
			printf(" %s\n", nome);
		}

		*autosave = 1;
	}

	/* comando inválido */
	else {
		if (temArquivo) printf("\n"); // quebra de linha final
		printf("Erro: '%s' comando invalido. Digite 'ajuda' para ver a lista de comandos\n", entrada);
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}

	/* autosave */
	if (*autosave){
		salvarImagem(imagem);
	}
}








void editar(int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	/* leitura do tipo de desenho */
	char desenho[15];
	int dnum;
	if (temArquivo)
		fscanf(arqEspecificacao, "%s %d", desenho, &dnum);
	else
		scanf("%s %d", desenho, &dnum);

	/**************** verificando tipo de desenho ******************/

	if (!strcmp(desenho, "linha") || !strcmp(desenho, "line")){
		/* verifica se a linha existe */
		if (dnum < 1 || dnum > imagem->desenho.numLinhas){
			printf("Erro: o desenho selecionado nao existe\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		/**** mesmo código de criar linha da função "executar" ****/
		Ponto pontos[2];
		lerPontos(pontos, 2, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		int valido;
		valido = verificaCoordenadas(pontos[0].x, pontos[0].y, imagem) &&
				 verificaCoordenadas(pontos[1].x, pontos[1].y, imagem);
		if (!valido) return;
		
		Linha l;
		l = criarLinha(pontos, imagem->cor, imagem);
		/******************** fim do código ***********************/

		/* substituindo linha na estrutura desenho */
		imagem->desenho.linhas[dnum - 1] = l;
	}

	else if (!strcmp(desenho, "retangulo") || !strcmp(desenho, "rect")){
		/* verifica se o poligono existe */
		if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
			printf("Erro: o desenho selecionado nao existe\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		/**** mesmo código de criar linha da função "executar" ****/
		Ponto pontoInicial;
		lerPontos(&pontoInicial, 1, temArquivo, arqEspecificacao);
		int dimensoes[2];
		lerInteiros(dimensoes, 2, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		int numFaces = 4;
		Ponto pontos[numFaces];
		gerarPontosRet(pontoInicial, pontos, dimensoes);
		/******************** fim do código ***********************/

		
		Poligono pol = criarPoligono(numFaces, pontos, imagem);
		imagem->desenho.poligonos[dnum - 1] = pol;
	}

	else if (!strcmp(desenho, "poligono") || !strcmp(desenho, "polygon")){
		/* verifica se o poligono existe */
		if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
			printf("Erro: o desenho selecionado nao existe\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		int numFaces; 
		lerInteiros(&numFaces, 1, temArquivo, arqEspecificacao);

		/**** mesmo código de criar linha da função "executar" ****/
		if (numFaces < 3 || numFaces > 100){
			printf("Erro: numero inválido de faces inserido\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		Ponto pontos[numFaces];
		lerPontos(pontos, numFaces, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);
		/******************** fim do código ***********************/

		Poligono pol = criarPoligono(numFaces, pontos, imagem);
		imagem->desenho.poligonos[dnum - 1] = pol;
	}

	else if (!strcmp(desenho, "circulo") || !strcmp(desenho, "circle")){
		/* verifica se o círculo existe */
		if (dnum < 1 || dnum > imagem->desenho.numCirculos){
			printf("Erro: o desenho selecionado nao existe\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		/**** mesmo código de criar linha da função "executar" ****/
		Ponto centro;
		lerPontos(&centro, 1, temArquivo, arqEspecificacao);

		int raio;
		lerInteiros(&raio, 1, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);
		/******************** fim do código ***********************/

		Circulo c = criarCirculo(centro, raio, imagem->cor, imagem);
		imagem->desenho.circulos[dnum - 1] = c;
	}

	else if (!strcmp(desenho, "preencher") || !strcmp(desenho, "fill")){
		/* verifica se o preenchimento existe */
		if (dnum < 1 || dnum > imagem->desenho.numPreencher){
			printf("Erro: o desenho selecionado nao existe\n");
			limparBuffer(temArquivo, arqEspecificacao);
			return;
		}

		/**** mesmo código de criar linha da função "executar" ****/
		Ponto p;
		lerPontos(&p, 1, temArquivo, arqEspecificacao);

		Cor novaCor;
		novaCor = criarCor(temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);
		/******************** fim do código ***********************/

		Preencher fill = criarPreenchimento(p, novaCor, imagem);
		imagem->desenho.preencher[dnum - 1] = fill;
	}

	else {
		printf("Erro: o tipo de desenho inserido nao existe\n");
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}
}