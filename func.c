#include <stdio.h>
#include <string.h>

#include "struct.h"
#include "imagem.h"
#include "linha.h"
#include "poligono.h"
#include "circulo.h"
#include "safestdlib.h"
#include "func.h"


/****************************************************
Função: criarCor
Parâmetros: nenhum
Retorno: tipo Cor

Descrição: cria uma cor com valores RGB informados pelo usuário
*****************************************************/
Cor criarCor(void){
	Cor cor;
	int r,g,b;

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

/****************************************************
Função: liberaAD
Parâmetros: ponteiro de estrutura Imagem, matriz do tipo Pixel
Retorno: nenhum

Descrição: libera toda alocação dinâmica utilizada ao longo do
programa, esta função será chamada quando o usuário desejar sair.
*****************************************************/
void liberarAD(Imagem *imagem, Pixel **pixels){
	for (int i = 0; i < imagem->alt; ++i)
		free(pixels[i]);
	free(pixels);
}

/****************************************************
Função: limparBuffer
Parâmetros: nenhum
Retorno: nenhum

Descrição: responsável por limpar o buffer de entrada, deve ser chamada
após um comando inválido, desconsiderando todas as demais 
informações inseridas pelo usuário
*****************************************************/
void limparBuffer(void){
	/* lê até encontrar uma quebra de linha */
	while (getchar() != '\n');
}

/****************************************************
Função: limparFileBuffer
Parâmetros: arquivo tipo FILE
Retorno: nenhum

Descrição: responsável por limpar o buffer de entrada, deve ser chamada
após um comando inválido, desconsiderando todas as demais 
informações inseridas pelo usuário
*****************************************************/
void limparFileBuffer(FILE *arq){
	/* lê até encontrar uma quebra de linha */
	while (getc(arq) != '\n');
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
FILE *lerArquivo(int *temArquivo, Imagem imagem){
	FILE *arquivo;

	arquivo = fopen(imagem.caminho, "r");

	if (!arquivo){
		*temArquivo = 0;
		fclose(arquivo);
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
(fim do arquivo). Retorna 1 se o arquivo acabou e 0 se ainda possui conteúdo.
*****************************************************/
int lerDoArquivo(FILE *arquivo, char *entrada){
	char c = 'a'; // iniciado com char genérico para satisfazer a condição do loop
	int eof;

	/* será repetido até encontrar um espaço ou quebra de linha no arquivo */
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
Função: executar
Parâmetros: entrada do usuário, estrutura tipo Imagem
Retorno: nenhum

Descrição: lê e interpreta a entrada do usuário caso a entrada
seja compatível com um comando do programa.
*****************************************************/
void executar(char entrada[10], Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao){
	/* comando ajuda */
	if (!strcmp(entrada, "ajuda") || !strcmp(entrada, "help")){
		if (temArquivo)
			printf("\n"); // quebra de linha final

		printf("---------------------------------------\n");
		printf("ajuda                         (imprime a lista de comandos)\n");
		printf("imagem <lar> <alt>            (gera uma nova imagem)\n");
		
		printf("cor <r> <g> <b>               (altera a cor atual do pincel)\n");
		printf("linha <x1> <y1> <x2> <y2>     (gera uma nova linha)\n");
		printf("poligono <N> <p1> ... <pN>    (gera um novo poligono)\n");
		printf("lista                         (lista os desenhos da imagem)\n");
		printf("limpar <r> <g> <b>            (preenche toda a imagem)\n");
		printf("salvar <nome_do_arquivo.ppm>  (salva em um arquivo ppm)\n");
		printf("abrir <nome_do_arquivo.ppm>   (carrega uma imagem ppm)\n");
		printf("ler <nome_do_arquivo>         (le um arquivo de especificacao)\n");
		printf("sair                          (encerra o programa)\n\n");
	}

	/* comando limpar */
	else if (!strcmp(entrada, "limpar") || !strcmp(entrada, "clear")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		int r, g, b;

		if (!temArquivo){
			scanf(" %d %d %d", &r, &g, &b);
		}
		else {
			fscanf(arqEspecificacao, " %d %d %d\n", &r, &g, &b);
			printf(" %d %d %d\n", r, g, b);
		}

		limparImagem(imagem, r, g, b);
	}

	/* comando linha */
	else if (!strcmp(entrada, "linha") || !strcmp(entrada, "line")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		Ponto p1, p2;

		/* leitura de entrada */
		if (!temArquivo){
			setbuf(stdin, NULL);
			scanf(" %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y);
		}
		else {
			fscanf(arqEspecificacao, " %d %d %d %d\n", &p1.x, &p1.y, &p2.x, &p2.y);
			printf(" %d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
		}

		/* verifica se as entradas são válidas */
		int maxX = imagem->lar - 1;
		int maxY = imagem->alt - 1;
		
		if (p1.x > maxX || p2.x > maxX ||
			p1.y > maxY || p2.y > maxY){
			printf("Erro: coordenada invalida inserida\n");
			return;
		}
		
		Linha l;
		l = criarLinha(p1, p2, imagem->cor);

		/* adicionando linha à estrutura linha */
		imagem->desenho.linhas[imagem->desenho.numLinhas] = l;
		imagem->desenho.numLinhas += 1;
	}

	/* comando poligono */
	else if (!strcmp(entrada, "poligono") || !strcmp(entrada, "polygon")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		int numFaces;  
		int maxX = imagem->lar - 1;
		int maxY = imagem->alt - 1;

		/* leitura de numero de faces do polígono */
		if (!temArquivo){
			setbuf(stdin, NULL);
			scanf(" %d", &numFaces);
		}
		else {
			fscanf(arqEspecificacao, " %d", &numFaces);
			printf(" %d\n", numFaces);
		}

		/* verificando se o número de faces é válido */
		if (numFaces < 3 || numFaces > 100){
			printf("Erro: numero inválido de faces inserido\n");
			temArquivo ? limparFileBuffer(arqEspecificacao) : limparBuffer();
		}

		Ponto pontos[numFaces];

		/* leitura de pontos*/
		if (!temArquivo){
			for (int i = 0; i < numFaces; ++i){
				scanf(" %d %d", &pontos[i].x, &pontos[i].y);

				if (pontos[i].x > maxX || pontos[i].y > maxY){
					printf("Erro: coordenada invalida inserida\n");
					return;
				}
			}
		}
		else {
			for (int i = 0; i < numFaces; ++i){
				fscanf(arqEspecificacao, " %d %d", &pontos[i].x, &pontos[i].y);

				if (pontos[i].x > maxX || pontos[i].y > maxY){
					printf("Erro: coordenada invalida inserida\n");
					while (getc(arqEspecificacao) != '\n');
					return;
				}
			}

			// ler quebra de linha
			while (getc(arqEspecificacao) != '\n');
		}
		
		Poligono pol;
		pol = criarPoligono(numFaces, pontos, imagem->cor);

		/* adicionando poligono à estrutura de desenhos */
		int n = imagem->desenho.numPoligonos;
		imagem->desenho.poligonos[n] = pol;
		imagem->desenho.numPoligonos += 1;
	}

	/* comando circulo */
	else if (!strcmp(entrada, "circulo") || !strcmp(entrada, "circle")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}

		int raio;
		Ponto centro;

		scanf(" %d %d %d", &raio, &centro.x, &centro.y);

		criarCirculo(centro, raio, imagem->cor);
	}

	/* comando cor */
	else if (!strcmp(entrada, "cor") || !strcmp(entrada, "color")){
		// pode ser alterado com a imagem fechada
		int r, g, b;

		if (!temArquivo){
			scanf(" %d %d %d", &r, &g, &b);
		}
		else {
			fscanf(arqEspecificacao, " %d %d %d\n", &r, &g, &b);
			printf(" %d %d %d\n", r, g, b);
		}

		imagem->cor.r = r;
		imagem->cor.g = g;
		imagem->cor.b = b;
	}

	/* comando desenhos */
	else if (!strcmp(entrada, "listar") || !strcmp(entrada, "list")){
		if (!imagemAberta){
			printf("Erro: imagem nao aberta\n");
			limparBuffer();
			return;
		}
		if (temArquivo)
			printf("\n"); // quebra de linha final

		listarDesenhos(imagem->desenho);
	}

	/* comando inválido */
	else {
		if (temArquivo)
			printf("\n"); // quebra de linha final

		printf("Erro: comando invalido. Digite 'ajuda' para ver a lista de comandos\n");
		limparBuffer();
	}
}