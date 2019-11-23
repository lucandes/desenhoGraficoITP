#include "imagem.h"
#include "struct.h"
#include "func.h"
#include "linha.h"
#include "poligono.h"
#include "circulo.h"

/****************************************************
Função: criarImagem
Parâmetros: nenhum
Retorno: estrutura Imagem

Descrição: serve para inicializar uma nova imagem, recebendo as entradas necessárias
e retornando os valores atribuídos em uma estrutura do tipo Imagem.
*****************************************************/
Imagem criarImagem(int *imagemAberta, int lar, int alt){
	Imagem imagem;

	/* atribuindo configurações padrão */
	strcpy(imagem.id, "P3");
	imagem.max = 255;

	imagem.lar = lar;
	imagem.alt = alt;
	imagem.numDePixels = imagem.lar * imagem.alt;

	/* alocação dinâmica da matriz pixels */
	imagem.pixels = (Cor **) safeMalloc(imagem.alt * sizeof(Cor *));
	for (int i = 0; i < imagem.alt; i++){
		imagem.pixels[i] = (Cor *) safeCalloc(imagem.lar, sizeof(Cor));

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

	*imagemAberta = 1;

	return imagem;
}

/****************************************************
Função: lerImagem
Parâmetros: nenhum
Retorno: tipo Imagem

Descrição: lê um arquivo ppm, atribui a uma estrutura Imagem e 
retorna essa estrutura.
*****************************************************/
Imagem abrirImagem(int *imagemAberta, char caminho[100]){

	Imagem imagem;
	imagem.arquivo = fopen(caminho, "r");
	if (imagem.arquivo == NULL){
		*imagemAberta = 0;
		return imagem;
	}

	/* leitura de conteudo */
	fscanf(imagem.arquivo, "%s\n", imagem.id);
	fscanf(imagem.arquivo, "%d %d", &imagem.lar, &imagem.alt);
	imagem.numDePixels = imagem.lar * imagem.alt;
	fscanf(imagem.arquivo, "%d", &imagem.max);

	/* alocação dinâmica da matriz pixels */
	imagem.pixels = (Cor **) safeMalloc(imagem.alt * sizeof(Cor *));
	for (int i = 0; i < imagem.alt; i++){
		imagem.pixels[i] = (Cor *) safeCalloc(imagem.lar, sizeof(Cor));
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

	/* inicia uma estrutura de desenho */
	imagem.desenho = criarDesenho();

	fclose(imagem.arquivo);

	*imagemAberta = 1;

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
	/* definindo a pasta galeria como local de salvamento */
	char nomeArq[50] = "./galeria/";
	strcat(nomeArq, imagem->nomeDoArquivo);
	strcpy(imagem->nomeDoArquivo, nomeArq);

	/* criando novo arquivo */
	imagem->arquivo = fopen(imagem->nomeDoArquivo, "w");

	/* inserindo desenhos na imagem */
	inserirDesenhos(imagem);

	/* inserindo informações de id, dimensões e valor de cor máximo */
	fprintf(imagem->arquivo, "%s\n", imagem->id);
	fprintf(imagem->arquivo, "%d %d\n", imagem->lar, imagem->alt);
	fprintf(imagem->arquivo, "%d\n", imagem->max);

	/* escrevendo matriz de pixels no arquivo */
	for (int y = 0; y < imagem->alt; y++){
		for (int x = 0; x < imagem->lar; x++){
			fprintf(imagem->arquivo, "%d ", imagem->pixels[y][x].r);
			fprintf(imagem->arquivo, "%d ", imagem->pixels[y][x].g);
			fprintf(imagem->arquivo, "%d ", imagem->pixels[y][x].b);
			fprintf(imagem->arquivo, "\n");
			/*fprintf(imagem->arquivo, "%d %d %d\n",
				imagem->pixels[y][x].r,
				imagem->pixels[y][x].g,
				imagem->pixels[y][x].b);*/
		}
	}

	fclose(imagem->arquivo);
}

/****************************************************
Função: limparImagem
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: limpa toda a imagem para uma cor especificada
*****************************************************/
void limparImagem(Imagem *imagem, Cor cor){
	for (int i = 0; i < imagem->alt; ++i)
		for (int j = 0; j < imagem->lar; ++j){
			imagem->pixels[i][j].r = cor.r;
			imagem->pixels[i][j].g = cor.g;
			imagem->pixels[i][j].b = cor.b;
		}

	/* liberando alocação de polígonos */
	if (imagem->desenho.numPoligonos > 0){
		for (int i = 0; i < imagem->desenho.numPoligonos; ++i)
			free(imagem->desenho.poligonos[i].linhas);
	}

	/* todos os desenhos serão apagados */
	imagem->desenho = criarDesenho();
}

void inserirPreenchimento(int x, int y, Preencher p, Imagem *imagem){
	if (x > imagem->lar - 1 || x < 0 || y > imagem->alt - 1 || y < 0)
		return;

	Cor cor;
	cor = imagem->pixels[y][x]; // cor do pixel atual

	/* se a cor do pixel atual for diferente da cor do pixel pai (anterior) */
	if (cor.r != p.cor.r || cor.g != p.cor.g || cor.b != p.cor.b)
		return;

	printf("preenchendo (%d, %d)\n", x, y);
	
	/* pintando pixel com nova cor */
	imagem->pixels[y][x].r = p.novaCor.r;
	imagem->pixels[y][x].g = p.novaCor.g;
	imagem->pixels[y][x].b = p.novaCor.b;

	/* chamada recursiva para os pixels vizinhos */
	inserirPreenchimento(x+1, y, p, imagem);
	inserirPreenchimento(x-1, y, p, imagem);
	inserirPreenchimento(x, y+1, p, imagem);
	inserirPreenchimento(x, y-1, p, imagem);
}

/****************************************************
Função: criarDesenho
Parâmetros: nenhum
Retorno: estrutura Desenho

Descrição: responsável por criar uma estrutura Desenho e retorná-la
*****************************************************/
Desenho criarDesenho(void){
	Desenho d;

	d.numLinhas = 0;
	d.numPoligonos = 0;
	d.numCirculos = 0;
	d.numPreencher = 0;

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

	/* listar poligonos */
	for (int i = 0; i < d.numPoligonos; ++i){
		printf("poligono %02d -", i+1);
		
		for (int j = 0; j < d.poligonos[i].numFaces; ++j){
			printf(" p%d (%d,%d)", 
				j+1,
				d.poligonos[i].pontos[j].x,
				d.poligonos[i].pontos[j].y);
		}
		printf("\n");
	}

	/* listar circulos */
	for (int i = 0; i < d.numCirculos; ++i){
		printf("circulo %02d - raio: %d, centro: (%d,%d)\n", 
			i+1,
			d.circulos[i].raio,
			d.circulos[i].centro.x,
			d.circulos[i].centro.y);
	}
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

	/* inserindo poligonos */
	for (int i = 0; i < imagem->desenho.numPoligonos; ++i){
		inserirPoligono(imagem->desenho.poligonos[i], imagem);
	}

	/* inserindo circulos */
	for (int i = 0; i < imagem->desenho.numCirculos; ++i){
		inserirCirculo(imagem->desenho.circulos[i], imagem);
	}

	/* inserindo preenchimentos */
	for (int i = 0; i < imagem->desenho.numCirculos; ++i){
		Preencher p = imagem->desenho.preencher[i];
		inserirPreenchimento(p.ponto.x, p.ponto.y, p, imagem);
	}
}