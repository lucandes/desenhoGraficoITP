#include "func.h"

/****************************************************
Função: executar
Parâmetros: entrada do usuário, estrutura tipo Imagem
Retorno: nenhum

Descrição: lê e interpreta a entrada do usuário, caso a entrada
seja compatível com um comando do programa, este será executado.
*****************************************************/
void executar(char entrada[10], Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao){
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
		
		criarPoligono(numFaces, pontos, imagem);
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

		criarPoligono(numFaces, pontos, imagem);
	}

	/* comando circulo */
	else if (!strcmp(entrada, "circulo") || !strcmp(entrada, "circle")){
		Ponto centro;
		lerPontos(&centro, 1, temArquivo, arqEspecificacao);

		int raio;
		lerInteiros(&raio, 1, temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		criarCirculo(centro, raio, imagem->cor, imagem);
	}

	/* comando preencher */
	else if (!strcmp(entrada, "preencher") || !strcmp(entrada, "fill")){
		Ponto p;
		lerPontos(&p, 1, temArquivo, arqEspecificacao);

		Cor novaCor;
		novaCor = criarCor(temArquivo, arqEspecificacao);
		limparBuffer(temArquivo, arqEspecificacao);

		criarPreenchimento(p, novaCor, imagem);
	}

	else if (!strcmp(entrada, "salvar") || !strcmp(entrada, "save")){
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

		salvarImagem(imagem);
	}

	/* comando desenhos */
	else if (!strcmp(entrada, "listar") || !strcmp(entrada, "list")){
		listarDesenhos(imagem->desenho, temArquivo);
	}

	/* comando inválido */
	else {
		if (temArquivo) printf("\n"); // quebra de linha final
		printf("Erro: '%s' comando invalido. Digite 'ajuda' para ver a lista de comandos\n", entrada);
		limparBuffer(temArquivo, arqEspecificacao);
	}
}

/****************************************************
Função: printAjuda
Parâmetros: int temArquivo
Retorno: nenhum

Descrição: imprime a lista de comandos do programa, caso
tenha arquivo de especificação será realizada uma quebra
de linha antes da impressão
*****************************************************/
void printAjuda(int temArquivo){
	if (temArquivo) printf("\n");
	printf("---------------------------------------\n");
	printf("ajuda                         (imprime a lista de comandos)\n");
	printf("imagem <lar> <alt>            (gera uma nova imagem)\n");
	printf("cor <r> <g> <b>               (altera a cor atual do pincel)\n");
	printf("linha <x1> <y1> <x2> <y2>     (gera uma nova linha)\n");
	printf("poligono <N> <p1> ... <pN>    (gera um novo poligono)\n");
	printf("retangulo <x> <y> <lar> <alt> (gera um novo retangulo)\n");
	printf("circulo <xc> <yc> <raio>      (gera um novo circulo)\n");
	printf("preencher <x> <y> <r> <g> <b> (preenche a area determinada)\n");
	printf("lista                         (lista os desenhos da imagem)\n");
	printf("limpar <r> <g> <b>            (preenche toda a imagem)\n");
	printf("salvar <nome_do_arquivo.ppm>  (salva em um arquivo ppm)\n");
	printf("abrir <nome_do_arquivo.ppm>   (carrega uma imagem ppm)\n");
	printf("ler <nome_do_arquivo>         (le um arquivo de especificacao)\n");
	printf("sair                          (encerra o programa)\n\n");
}

/****************************************************
Função: liberaAD
Parâmetros: ponteiro de estrutura Imagem, matriz do tipo Cor
Retorno: nenhum

Descrição: libera toda alocação dinâmica utilizada ao longo do
programa, esta função será chamada quando o usuário desejar sair.
*****************************************************/
void liberarAD(Imagem *imagem, Cor **pixels){
	for (int i = 0; i < imagem->alt; ++i)
		free(pixels[i]);
	free(pixels);
}

/****************************************************
Função: limparBuffer
Parâmetros: inteiro temArquivo, arquivo tipo FILE
Retorno: nenhum

Descrição: responsável por limpar o buffer de entrada, deve ser chamada
após um comando inválido, desconsiderando todas as demais 
informações inseridas pelo usuário
*****************************************************/
void limparBuffer(int temArquivo, FILE *arq){
	if (temArquivo){
		while (getc(arq) != '\n');
		printf("\n");
	}
	else
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
Função: lerArquivo
Parâmetros: ponteiro de int temArquivo, tipo Imagem
Retorno: ponteiro tipo FILE

Descrição: abre um arquivo no caminho determinado pelo usuário,
verifica se o foi aberto corretamente e retorna o arquivo.
*****************************************************/
FILE *novoArquivo(int *temArquivo, Imagem imagem){
	FILE *arquivo;

	arquivo = fopen(imagem.caminho, "r");

	if (arquivo == NULL){
		*temArquivo = 0;
	}
	else
		*temArquivo = 1;

	return arquivo;
}

/****************************************************
Função: lerDoArquivo
Parâmetros: ponteiro de arquivo FILE, string entrada
Retorno: int eof

Descrição: lê o arquivo até encontrar um espaço, quebra de linha ou EOF 
(fim do arquivo) e armazena no vetor "entrada". Retorna 1 se o arquivo 
acabou e 0 se ainda possui conteúdo.
*****************************************************/
int lerArquivo(FILE *arquivo, char *entrada){
	char c = 'a'; // iniciado com char genérico para satisfazer a condição do loop
	int eof;

	/* repetirá até encontrar um espaço ou quebra de linha */
	for(int i = 0; c != ' ' && c != '\n'; i++){
		c = getc(arquivo);

		/* se o char for letra será inserido na string, se for 
		   espaço ou quebra de linha o '\0' é inserido */
		c == ' ' || c == '\n' ? (entrada[i] = '\0') : (entrada[i] = c);

		/* verifica se chegou ao fim do arquivo */
		if (feof(arquivo))
			return 1;
	}

	return 0;
}

/****************************************************
Função: lerInteiros
Parâmetros: ponteiro de inteiro, numero de inteiros a serem lidos, inteiro temArquivo, arquivo tipo FILE
Retorno: nenhum

Descrição: lê a quantidade determinada de inteiros e os insere 
no endereço passado por parâmetro, se houver um arquivo de 
especificação a leitura será realizada no arquivo
*****************************************************/
void lerInteiros(int *inteiros, int numInteiros, int temArquivo, FILE *arq){
	for (int i = 0; i < numInteiros; ++i){
		if (!temArquivo)
			scanf(" %d", &inteiros[i]);
		else {
			fscanf(arq, " %d", &inteiros[i]);
			printf(" %d", inteiros[i]);
		}
	}
}

/****************************************************
Função: lerPontos
Parâmetros: ponteiro de ponto, numero de pontos a serem lidos, inteiro temArquivo, arquivo tipo FILE
Retorno: nenhum

Descrição: lê a quantidade determinada de pontos e os insere 
no endereço que foi passado por parâmetro, se houver um arquivo de 
especificação a leitura será realizada nesse arquivo
*****************************************************/
void lerPontos(Ponto *pontos, int numPontos, int temArquivo, FILE *arq){
	for (int i = 0; i < numPontos; ++i){
		if (!temArquivo)
			scanf(" %d %d", &pontos[i].x, &pontos[i].y);
		else {
			fscanf(arq, " %d %d", &pontos[i].x, &pontos[i].y);
			printf(" %d %d", pontos[i].x, pontos[i].y);
		}
	}
}

/****************************************************
Função: verificaCoordenadas
Parâmetros: inteiro x, inteiro y, ponteiro de imagem
Retorno: inteiro

Descrição: verifica se o ponto passado por parâmetro está dentro
das dimensôes da imagem, se sim, retornará 1.
*****************************************************/
int verificaCoordenadas(int x, int y, Imagem *imagem){
	int maxX = imagem->lar - 1;
	int maxY = imagem->alt - 1;

	if (x > maxX || x < 0 || y > maxY || y < 0){
		printf("Erro: coordenada invalida inserida\n");
		return 0;
	}

	return 1;
}