#include "linha.h"

/****************************************************
Função: criarLinha
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: recebe os pontos do usuário e caso sejam válidos, 
cria uma linha e armazena na estrutura de desenhos da imagem
*****************************************************/
Linha criarLinha(Ponto pontos[2], Cor cor, Imagem *imagem){
	Linha linha;

	/* leitura das coordenadas */
	linha.inicio.x = pontos[0].x;
	linha.inicio.y = pontos[0].y;

	linha.fim.x = pontos[1].x;
	linha.fim.y = pontos[1].y;

	linha.cor = cor;
	
	return linha;
}	

void lerLinha(int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
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

/****************************************************
Função: inserirLinha
Parâmetros: tipo Linha, ponteiro tipo Imagem
Retorno: nenhum

Descrição: insere a linha na matriz de pixels da imagem,
essa função deve ser executada apenas na etapa de salvamento
da imagem
*****************************************************/
void inserirLinha(Linha linha, Imagem *imagem){
	/* declarando variaveis */
	int x1 = linha.inicio.x;
	int y1 = linha.inicio.y;

	int x2 = linha.fim.x;
	int y2 = linha.fim.y;

	/* variacao de x e y */
	float vx = (float) (x2 - x1) / (y2 - y1);
	if (vx < 0) vx *= -1;
	float vy = (float) (y2 - y1) / (x2 - x1);
	if (vy < 0) vy *= -1;

	/* determina se um pixel será avançado ou não */
	float sumx = vx;
	float sumy = vy;

	/* determina a direção na qual o pixel irá avançar */
	int countx = x1 < x2 ? 1 : -1;
	int county = y1 < y2 ? 1 : -1;

	/* pinta o pixel inicial */
	pintarPixel(x1, y1, imagem, linha.cor);

	/* enquanto a linha não alcançar o ponto final */
	while (x1 != x2 || y1 != y2){
		sumx += vx;
		sumy += vy;

		// se sumx for maior ou igual a um
		if (sumx >= 1){
			sumx -= 1;
			x1 += countx; //avance um pixel
		}

		// se sumy for maior ou igual a um
		if (sumy >= 1){
			sumy -= 1;
			y1 += county; //avance um pixel
		}

		pintarPixel(x1, y1, imagem, linha.cor);
	}
}

void editarLinha(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao){
	/* verifica se a linha existe */
	if (dnum < 1 || dnum > imagem->desenho.numLinhas){
		printf("Erro: o desenho selecionado nao existe\n");
	}

	/**** mesmo código de criar linha da função "executar" ****/
	Ponto pontos[2];
	lerPontos(pontos, 2, temArquivo, arqEspecificacao);

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

int moverLinha(int dnum, int dist[2], Imagem *imagem){
	/* verifica se a linha existe */
	if (dnum < 1 || dnum > imagem->desenho.numLinhas){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	/* inserindo deslocamento na linha */
	imagem->desenho.linhas[dnum - 1].inicio.x += dist[0];
	imagem->desenho.linhas[dnum - 1].fim.x += dist[0];
	imagem->desenho.linhas[dnum - 1].inicio.y += dist[1];
	imagem->desenho.linhas[dnum - 1].fim.y += dist[1];

	return 1;
}

int copiarLinha(int dnum, Imagem *imagem){
	/* verifica se a linha existe */
	if (dnum < 1 || dnum > imagem->desenho.numLinhas){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	Linha new = imagem->desenho.linhas[dnum - 1];
	int n = imagem->desenho.numLinhas++;
	imagem->desenho.linhas[n] = new;

	int numOrdem = imagem->desenho.numOrdem++;
	imagem->desenho.ordem[numOrdem] = 1;

	return 1;
}

int removerLinha(int dnum, Imagem *imagem){
	Desenho *d = &imagem->desenho;

	/* verifica se a linha existe */
	if (dnum < 1 || dnum > imagem->desenho.numLinhas){
		return 0;
	}

	/* movendo todas as linhas seguintes para a casa anterior */
	for (int i = dnum; i < d->numLinhas; i++)
		d->linhas[i - 1] = d->linhas[i];
	d->numLinhas--;

	int ord = 0; //contador
	int ordIndex;

	/* buscando a posição do desenho removido no vetor de ordem */
	for (int i = 0; i < d->numOrdem; ++i){
		if (d->ordem[i] == 1){ // representa linha
			ord++;

			if (ord == dnum){
				ordIndex = i; // pegando a posição atual do desenho
				break;
			}
		}

	}

	/* movendo todas os desenhos seguintes para a casa anterior */
	for (int i = ordIndex; i < d->numOrdem; i++){
		d->ordem[i] = d->ordem[i + 1];
	}
	d->numOrdem--;

	return 1;
}