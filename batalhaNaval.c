#include <stdio.h>

// define as constantes para cálculos:
#define LINHAS 10
#define COLUNAS 10

#define TAMANHO_DO_NAVIO 3

// "códigos" dos objetos dentro do tabuleiro
#define VAZIO 0
#define EXPLOSAO 1
#define NAVIO 3


// define os vetores dos ataques:
unsigned int ataque_normal[3][5] = {
	{0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0}
};

unsigned int ataque_cruz[3][5] = {
	{0, 0, 1, 0, 0},
	{1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0}
};

unsigned int ataque_cone[3][5] = {
	{0, 0, 1, 0, 0},
	{0, 1, 1, 1, 0},
	{1, 1, 1, 1, 1}
};

unsigned int ataque_octaedro[3][5] = {
	{0, 0, 1, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 1, 0, 0}
};


// como eu não usarei números negativos,
// defino a lista como: unsigned int[];
unsigned int tabuleiro[LINHAS][COLUNAS];

// inicia/limpa os valores do tabuleiro
void iniciar_tabuleiro() {
	for (int y = 0; y < LINHAS; y++) {
		for (int x = 0; x < COLUNAS; x++) {
			tabuleiro[y][x] = VAZIO;
		}
	}
}

// posiciona um navio horizontalmente no tabuleiro
// x: posição da coluna, y: posição da linha
int posicionarNavioHorizontal(const unsigned int x, const unsigned int y) {
	// se a posição for maior que os limites do tabuleiro
	// ele retorna 0:
	if (x + TAMANHO_DO_NAVIO > COLUNAS)
		return 0;

	// se ele encontrar no tabuleiro outro navio
	// ele retorna 0:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		if (tabuleiro[y][x + i] != VAZIO)
			return 0;
	}

	// define o valor 3 para identificar que
	// o navio se localiza ali:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		tabuleiro[y][x + i] = NAVIO;
	}

	// retorna sucesso após realizar tudo:
	return 1;
}

// posiciona um navio verticalmente no tabuleiro
// x: posição da coluna, y: posição da linha
int posicionarNavioVertical(const unsigned int x, const unsigned int y) {
	// se a posição for maior que os limites do tabuleiro
	// ele retorna 0:
	if (y + TAMANHO_DO_NAVIO > LINHAS)
		return 0;

	// se ele encontrar no tabuleiro outro navio
	// ele retorna 0:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		if (tabuleiro[y + i][x] != VAZIO)
			return 0;
	}

	// define o valor 3 para identificar que
	// o navio se localiza ali:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		tabuleiro[y + i][x] = NAVIO;
	}

	// retorna sucesso após realizar tudo:
	return 1;
}

// posiciona um navio diagonalmente no tabuleiro
// x: posição da coluna, y: posição da linha
int posicionarNavioDiagonal(const unsigned int x, const unsigned int y) {
	// se a posição for maior que os limites do tabuleiro
	// ele retorna 0:
	if ((y + TAMANHO_DO_NAVIO > LINHAS) || (x + TAMANHO_DO_NAVIO > COLUNAS))
		return 0;

	// se ele encontrar no tabuleiro outro navio
	// ele retorna 0:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		if (tabuleiro[y + i][x + i] != VAZIO)
			return 0;
	}

	// define o valor 3 para identificar que
	// o navio se localiza ali:
	for (int i = 0; i < TAMANHO_DO_NAVIO; i++) {
		tabuleiro[y + i][x + i] = NAVIO;
	}

	// retorna sucesso após realizar tudo:
	return 1;
}

// função para testar ataques:
void realizar_ataque(const unsigned int x, const unsigned int y, const unsigned int ataque[3][5]) {
	for (int linha = 0; linha < 3; linha++) {
		for (int coluna = 0; coluna < 5; coluna++) {

			const unsigned int linha_atual = y + linha;
			const unsigned int coluna_atual = x + coluna;

			// eu verifico se o alvo está dentro
			// dos limites do tabuleiro
			if ((linha_atual >= LINHAS) || (coluna_atual >= COLUNAS)) {
				// se passar dos limites, ele simplesmente não acerta nada
				continue;
			}

			if (ataque[linha][coluna] != 0)
				tabuleiro[linha_atual][coluna_atual] = EXPLOSAO;
		}
	}
}

void mostrar_tabuleiro() {
	printf("Tabuleiro:\n");

	// faz um loop for para imprimir cada linha,
	// e cada coluna que ela possuir:
	for (int y = 0; y < LINHAS; y++) {
		for (int x = 0; x < COLUNAS; x++) {
			printf("%d ", tabuleiro[y][x]);

			// quando chegar na ultima coluna
			// ele pula a linha no console
			if (x + 1 >= COLUNAS)
				printf("\n");
		}
	}
}


int main() {
	printf("Bem vindo ao jogo Batalha Naval!\n\n");

	printf("Iniciando tabuleiro...\n");
	iniciar_tabuleiro();

	printf("Posicionando Navios...\n");

	// tenta posicionar navios, senão retorna erro:
	if (posicionarNavioHorizontal(1, 3) == 0) {
		printf("Falha ao posicionar o 1º Navio!");
		return 1;
	}

	if (posicionarNavioVertical(4, 5) == 0) {
		printf("Falha ao posicionar o 2º Navio!");
		return 1;
	}

	if (posicionarNavioVertical(8, 6) == 0) {
		printf("Falha ao posicionar o 3º Navio!");
		return 1;
	}

	if (posicionarNavioDiagonal(5, 1) == 0) {
		printf("Falha ao posicionar o 4º Navio!");
		return 1;
	}

	mostrar_tabuleiro();

	printf("Realizando ataque do tipo Cruz\n");
	realizar_ataque(4, 4, ataque_cruz);

	mostrar_tabuleiro();

	return 0;
}
