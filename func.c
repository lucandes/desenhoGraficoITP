#include "func.h"

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
acabou, 0 se ainda possui conteúdo e -1 se for um comentário (#).
*****************************************************/
int lerArquivo(FILE *arquivo, char *entrada){
	char c = 'a'; // iniciado com char genérico
	int i = 0; // contador

	while (c != ' ' && c != '\n'){
		c = getc(arquivo);

		/* verificando se é um comentário */
		if (c == '#'){
			limparBuffer(1, arquivo);
			return -1; // retorno de comentario
		}

		/* caso seja espaço, encerre a string */
		if (c == ' ' || c == '\n')
			entrada[i++] = '\0';
		else
			entrada[i++] = c;

		/* verificando se chegou ao fim do arquivo*/
		if (feof(arquivo))
			return 1; // retorno de fim de arquivo
	}
	return 0;
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