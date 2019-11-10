#include "safestdlib.h"
#include "struct.h"
#include "default.h"
#include "linha.h"


/****************************************************
Função: criarDesenho
Parâmetros: nenhum
Retorno: estrutura Desenho

Descrição: responsável por criar uma estrutura Desenho e retorná-la
*****************************************************/
Desenho criarDesenho(void){
	Desenho d;

	d.numLinhas = 0;

	return d;
};

/****************************************************
Função: listarDesenhos
Parâmetros: tipo Desenho
Retorno: nenhum

Descrição: imprime na tela todos os desenhos feitos na imagem
*****************************************************/
void listarDesenhos(Desenho d){
	/* listar linhas */
	for (int i = 0; i < d.numLinhas; ++i)
		printf("linha %02d - p1 (%d,%d), p2 (%d,%d)\n", 
			i+1, 
			d.linhas[i].inicio.x,
			d.linhas[i].inicio.y,
			d.linhas[i].fim.x,
			d.linhas[i].fim.y);
}

/****************************************************
Função: inserirDesenhos
Parâmetros: nenhum
Retorno: ponteiro tipo Imagem

Descrição: aplica todos os desenhos na matriz de pixel, essa função é
chamada apenas na etapa de salvamento do arquivo ppm
*****************************************************/
void inserirDesenhos(Imagem *imagem){
	/* inserindo linhas */
	for (int i = 0; i < imagem->desenho.numLinhas; ++i){
		inserirLinha(imagem->desenho.linhas[i], imagem);
	}
}

/****************************************************
Função: criarCor
Parâmetros: nenhum
Retorno: tipo Cor

Descrição: cria uma cor com valores RGB informados pelo usuário
*****************************************************/
Cor criarCor(void){
	Cor cor;
	int r,g,b;

	limparBuffer();

	printf("  Valores de cor RGB\n");

	printf("    R: ");
	scanf(" %d", &r);

	printf("    G: ");
	scanf(" %d", &g);

	printf("    B: ");
	scanf(" %d", &b);

	cor.r = r;
	cor.g = g;
	cor.b = b;

	return cor;
}

/****************************************************
Função: criarImagem
Parâmetros: nenhum
Retorno: estrutura Imagem

Descrição: serve para inicializar uma nova imagem, recebendo as entradas necessárias
e retornando os valores atribuídos em uma estrutura do tipo Imagem.
*****************************************************/
Imagem criarImagem(void){
	Imagem imagem;

	/* atribuindo configurações padrão */
	strcpy(imagem.id, "P3");
	imagem.max = 255;
	strcpy(imagem.nomeDoArquivo, "./imagens/"); // toda imagem gerada será salva na pasta imagens

	limparBuffer();

	/* leitura das dimensões da imagem a ser criada */
	printf("  Largura: ");
	scanf(" %d", &imagem.lar);

	printf("  Altura:  ");
	scanf(" %d", &imagem.alt);

	imagem.numDePixels = imagem.lar * imagem.alt;

	/* alocação dinâmica da matriz pixels */
	imagem.pixels = (Pixel **) safeMalloc(imagem.alt * sizeof(Pixel *));
	for (int i = 0; i < imagem.alt; i++){
		imagem.pixels[i] = (Pixel *) safeCalloc(imagem.lar, sizeof(Pixel));

		/* a imagem será criada com a cor branca */
		for (int j = 0; j < imagem.lar; j++){
			imagem.pixels[i][j].r = 255;
			imagem.pixels[i][j].g = 255;
			imagem.pixels[i][j].b = 255;
		}
	}

	/* atribuindo a cor preta ao pincel */
	imagem.cor.r = 0;
	imagem.cor.g = 0;
	imagem.cor.b = 0;

	/* inicia uma estrutura de desenho */
	imagem.desenho = criarDesenho();

	return imagem;
}

/****************************************************
Função: salvarImagem
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: cria um novo arquivo ppm e escreve todas as informações
da imagem dentro dele.
*****************************************************/
void salvarImagem(Imagem *imagem){
	/* recebendo nome do arquivo */
	char arqNome[30]; 

	limparBuffer();

	printf("  Nome do arquivo: ");
	scanf("%s", (char *) &arqNome);
	strcat(imagem->nomeDoArquivo, arqNome);

	/* criando novo arquivo */
	imagem->arquivo = fopen(imagem->nomeDoArquivo, "w");

	/* inserindo desenhos na imagem */
	inserirDesenhos(imagem);

	/* inserindo informações de id, dimensões e valor de cor máximo */
	fprintf(imagem->arquivo, "%s\n", imagem->id);
	fprintf(imagem->arquivo, "%d %d\n", imagem->lar, imagem->alt);
	fprintf(imagem->arquivo, "%d\n", imagem->max);

	/* escrevendo matriz de pixels no arquivo */
	for (int x = 0; x < imagem->alt; x++){
		for (int y = 0; y < imagem->lar; y++){
			fprintf(imagem->arquivo, "%d %d %d\n",
				imagem->pixels[x][y].r,
				imagem->pixels[x][y].g,
				imagem->pixels[x][y].b);
		}
	}

	/* fechando arquivo */
	fclose(imagem->arquivo);
}

/****************************************************
Função: lerImagem
Parâmetros: nenhum
Retorno: tipo Imagem

Descrição: lê um arquivo ppm, atribui a uma estrutura Imagem e 
retorna essa estrutura.
*****************************************************/
Imagem abrirImagem(void){
	/* recebendo caminho da imagem */
	char caminho[100];
	limparBuffer();
	printf("  Caminho: ");
	fgets(caminho, 100, stdin);

	/* removendo o '\n' da string caminho */
	for (int i = 0; i < strlen(caminho); ++i){
		if (caminho[i] == '\n')
			caminho[i] = '\0';
	}

	Imagem imagem;
	imagem.arquivo = fopen(caminho, "r");
	if (imagem.arquivo == NULL){
		printf("%s: NULL\n", caminho);
		return imagem;
	}

	/* leitura de conteudo */
	fscanf(imagem.arquivo, "%s\n", imagem.id);
	fscanf(imagem.arquivo, "%d %d", &imagem.lar, &imagem.alt);
	imagem.numDePixels = imagem.lar * imagem.alt;
	fscanf(imagem.arquivo, "%d", &imagem.max);

	/* alocação dinâmica da matriz pixels */
	imagem.pixels = (Pixel **) safeMalloc(imagem.alt * sizeof(Pixel *));
	for (int i = 0; i < imagem.alt; i++){
		imagem.pixels[i] = (Pixel *) safeCalloc(imagem.lar, sizeof(Pixel));
	}

	/* lendo pixels da imagem e atribuindo à matriz */
	for (int i = 0; i < imagem.alt; ++i){
		for (int j = 0; j < imagem.lar; ++j){
			fscanf(imagem.arquivo, "%d %d %d\n",
				&imagem.pixels[i][j].r,
				&imagem.pixels[i][j].g,
				&imagem.pixels[i][j].b);
		}
	}

	/* atribuindo a cor preta ao pincel */
	imagem.cor.r = 0;
	imagem.cor.g = 0;
	imagem.cor.b = 0;

	strcpy(imagem.nomeDoArquivo, "./imagens/"); // toda imagem gerada será salva na pasta imagens

	/* inicia uma estrutura de desenho */
	imagem.desenho = criarDesenho();

	fclose(imagem.arquivo);

	return imagem;
}

/****************************************************
Função: pintarPixel
Parâmetros: coordenadas do pixel, matriz tipo Pixel, cor tipo Cor
Retorno: nenhum

Descrição: altera a cor do pixel na matriz
*****************************************************/
void pintarPixel(int x, int y, Pixel **pixels, Cor cor){
	// invertido pois a matriz foi inicializada a partir da altura
	pixels[y][x].r = cor.r;
	pixels[y][x].g = cor.g;
	pixels[y][x].b = cor.b;
}

