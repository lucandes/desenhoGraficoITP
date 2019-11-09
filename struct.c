#include "safestdlib.h"
#include "struct.h"
#include "default.h"
#include "linha.h"


/****************************************************
Função: criarImagem
Parâmetros: nenhum
Retorno: estrutura Imagem

Descrição: serve para inicializar uma nova imagem, recebendo as entradas necessárias
e retornando os valores atribuídos em uma estrutura do tipo Imagem.
*****************************************************/
Desenho criaDesenho(void){
	Desenho d;

	d.numLinhas = 0;

	return d;
};

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


void inserirDesenhos(Imagem *imagem){
	for (int i = 0; i < imagem->desenho.numLinhas; ++i){
		inserirLinha(imagem->desenho.linhas[i], imagem);
	}
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
	strcpy(imagem.nomeDoArquivo, "./imagens/");

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
Função: 
Parâmetros: 
Retorno: 

Descrição:
*****************************************************/
void salvarImagem(Imagem *imagem){
	char arqNome[30]; 
	scanf("%s", (char *) &arqNome);

	strcat(imagem->nomeDoArquivo, arqNome);

	imagem->arquivo = fopen(imagem->nomeDoArquivo, "w");

	inserirDesenhos(imagem);

	fprintf(imagem->arquivo, "%s\n", imagem->id);
	fprintf(imagem->arquivo, "%d %d\n", imagem->lar, imagem->alt);
	fprintf(imagem->arquivo, "%d\n", imagem->max);

	for (int x = 0; x < imagem->alt; x++){
		for (int y = 0; y < imagem->lar; y++){
			fprintf(imagem->arquivo, "%d %d %d\n",
				imagem->pixels[x][y].r,
				imagem->pixels[x][y].g,
				imagem->pixels[x][y].b);
		}
	}

	fclose(imagem->arquivo);
}

/****************************************************
Função: 
Parâmetros: 
Retorno: 

Descrição:
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

