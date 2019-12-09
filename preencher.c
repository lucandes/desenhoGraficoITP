#include "preencher.h"

/****************************************************
Função: criarPreenchimento
Parâmetros: ponto p, tipo Cor, ponteiro tipo Imagem
Retorno: nenhum

Descrição: armazena as informações sobre o preenchimento numa estrutura
tipo Preencher e insere na estrutura de desenhos
*****************************************************/
Preencher criarPreenchimento(Ponto p, Cor novaCor, Imagem *imagem){
	Preencher fill;
	fill.novaCor = novaCor;

	/* atribuindo coordenadas do pixel selecionado */
	fill.ponto.x = p.x;
	fill.ponto.y = p.y;

	return fill;
}

/****************************************************
Função: lerPreencher
Parâmetros: inteiro temArquivo, arquivo de especificação, ponteiro tipo Imagem
Retorno: nenhum

Descrição: faz a leitura dos paramêtros necessários para a criação
de um novo desenho na imagem, chama a função de criação
*****************************************************/
void lerPreencher(int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
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

/****************************************************
Função: inserirPreenchimento
Parâmetros: coordenadas do pixel, estrutura Preencher, ponteiro tipo Imagem
Retorno: nenhum

Descrição: altera os pixels de uma área de mesma cor. Funciona de maneira
recursiva, verificando os pixels em 4 sentidos opostos a partir do pixel
inicial. (ERRO DE SEGMENTAÇÃO EM ÁREAS EXTENSAS)
*****************************************************/
void inserirPreenchimento(int x, int y, Preencher p, Imagem *imagem){
	/* se o pixel estiver fora das dimensões da imagem */
	if (x > imagem->lar - 1 || x < 0 || y > imagem->alt - 1 || y < 0)
		return;

	Cor corAtual;
	corAtual = imagem->pixelsCopy[y][x]; // cor do pixel atual

	/* se a cor do pixel atual for diferente da cor do pixel pai (anterior) */
	if (corAtual.r != p.cor.r || corAtual.g != p.cor.g || corAtual.b != p.cor.b)
		return;

	//printf("preenchendo (%d,%d)\n", x, y);
	
	/* pintando pixel com nova cor */
	imagem->pixelsCopy[y][x] = p.novaCor;

	/* chamada recursiva para os pixels vizinhos */
	inserirPreenchimento(x+1, y, p, imagem);
	inserirPreenchimento(x-1, y, p, imagem);
	inserirPreenchimento(x, y+1, p, imagem);
	inserirPreenchimento(x, y-1, p, imagem);
}

/****************************************************
Função: editarPreencher
Parâmetros: numero do desenho, ponteiro tipo Imagem, inteiro temArquivo, arquivo de especificação
Retorno: nenhum

Descrição: permite que o usuário reescreva as informações de
um determinado desenho.
*****************************************************/
void editarPreencher(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao){
	/* verifica se o preenchimento existe */
	if (dnum < 1 || dnum > imagem->desenho.numPreencher){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	Ponto p;
	lerPontos(&p, 1, temArquivo, arqEspecificacao);

	Cor novaCor;
	novaCor = criarCor(temArquivo, arqEspecificacao);

	Preencher fill = criarPreenchimento(p, novaCor, imagem);
	imagem->desenho.preencher[dnum - 1] = fill;
}

/****************************************************
Função: moverPreencher
Parâmetros: numero do desenho, vetor distancia do deslocamento, ponteiro tipo Imagem,
Retorno: nenhum

Descrição: permite que o usuário mova um determinado desenho.
*****************************************************/
int moverPreencher(int dnum, int dist[2], Imagem *imagem){
	/* verifica se o preenchimento existe */
	if (dnum < 1 || dnum > imagem->desenho.numPreencher){
		return 0;
	}

	/* inserindo deslocamento no preencher */
	imagem->desenho.preencher[dnum - 1].ponto.x += dist[0];
	imagem->desenho.preencher[dnum - 1].ponto.y += dist[1];

	return 1;
}

/****************************************************
Função: copiarPreencher
Parâmetros: numero do desenho, ponteiro tipo Imagem,
Retorno: inteiro que indica se o desenho existe

Descrição: permite que o usuário copie um determinado desenho.
*****************************************************/
int copiarPreencher(int dnum, Imagem *imagem){
	/* verifica se o preenchimento existe */
	if (dnum < 1 || dnum > imagem->desenho.numPreencher){
		return 0;
	}

	Preencher new = imagem->desenho.preencher[dnum - 1];
	int n = imagem->desenho.numPreencher++;
	imagem->desenho.preencher[n] = new;

	int numOrdem = imagem->desenho.numOrdem++;
	imagem->desenho.ordem[numOrdem] = 4;

	return 1;
}

/****************************************************
Função: removerPreencher
Parâmetros: numero do desenho, ponteiro tipo Imagem,
Retorno: inteiro que indica se o desenho existe

Descrição: permite que o usuário remova um determinado desenho.
*****************************************************/
int removerPreencher(int dnum, Imagem *imagem){
	Desenho *d = &imagem->desenho;

	/* verifica se o preenchimento existe */
	if (dnum < 1 || dnum > imagem->desenho.numPreencher){
		return 0;
	}

	/* movendo todos os preenchimentos seguintes para a casa anterior */
	for (int i = dnum - 1; i < d->numPreencher; i++)
		d->preencher[i] = d->preencher[i + 1];
	d->numPreencher--;

	int ord = 0; //contador
	int ordIndex;

	/* buscando a posição do desenho removido no vetor de ordem */
	for (int i = 0; i < d->numOrdem; ++i){
		if (d->ordem[i] == 4){ // representa preencher
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