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
Desenho criaDesenho(void){
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
	scanf("%d %d %d", &r, &g, &b);

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

	/* leitura das dimensões da imagem a ser criada */
	scanf("%d %d", &imagem.lar, &imagem.alt);
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
	imagem.desenho = criaDesenho();

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

