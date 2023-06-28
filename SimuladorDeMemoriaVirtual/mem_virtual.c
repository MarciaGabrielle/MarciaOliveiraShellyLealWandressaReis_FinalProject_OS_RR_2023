#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Declaração das funções
void AddNewPage(char value[9]);
void Random(char value[9]);
void LRU(char value[9]);
void FIFO(char value[9]);
bool Find(char value[9]);
void ReplacePage(char value[9]);
void WriteAddress(char value[9]);
void FreeMemory();

typedef struct Page{
	char address[9];
	struct Page *next;
} Page;

FILE *file;
Page *first, *last;
char *alg, *filePath, line[20], tmpAddress[9];
int pageSize, memSize, numPages;
int operations = 0, reads = 0, writes = 0, hits = 0, misses = 0, faults = 0, usedPages = 0;

int main(int argc, char *argv[])
{
	alg = argv[1]; // Obtém o algoritmo a ser usado a partir do primeiro argumento da linha de comando
	filePath = argv[2]; // Obtém o caminho do arquivo de entrada a partir do segundo argumento da linha de comando
	pageSize = atoi(argv[3]); // Converte o terceiro argumento (tamanho da página) para inteiro
	memSize = atoi(argv[4]); // Converte o quarto argumento (tamanho da memória) para inteiro

	// Verifica se o tamanho da página está dentro da faixa esperada
	if (pageSize < 2 || pageSize > 64)
	{
		printf("ERRO: O tamanho de cada pagina deve estar entre 2 e 64.");
		return 0;
	}

	// Verifica se o tamanho da memória está dentro da faixa esperada
	if (memSize < 128 || memSize > 16384)
	{
		printf("ERRO: O tamanho da memoria deve estar entre 128 e 16384.");
		return 0;
	}

	// Verifica se o algoritmo especificado é válido
	if (strcmp(alg, "lru") && strcmp(alg, "fifo") && strcmp(alg, "random"))
	{
		printf("ERRO: O algoritmo deve ser lru, fifo ou random.");
		return 0;
	}

	numPages = memSize / pageSize; // Calcula o número de páginas com base no tamanho da memória e da página

	// Verifica se o caminho do arquivo de entrada foi especificado
	if (strlen(filePath) > 0)
	{
		file = fopen(filePath, "r"); // Abre o arquivo de entrada para leitura

		while (fgets(line, 20, file) != NULL)
		{
			operations++; // Contabiliza a operação

			strncpy(tmpAddress, line, 8); // Copia os primeiros 8 caracteres da linha (endereço)
			tmpAddress[8] = '\0'; // Adiciona o caractere nulo para finalizar a string

			if (line[9] == 'W' || line[9] == 'w')
			{
				WriteAddress(tmpAddress); // Realiza uma operação de escrita no endereço especificado
			}
			else if (line[9] == 'R' || line[9] == 'r')
			{
				if (Find(tmpAddress))
				{
					hits++; // Contabiliza um hit se o endereço já estiver na memória
				}
				else
				{
					misses++; // Contabiliza um miss se o endereço não estiver na memória
					WriteAddress(tmpAddress); // Realiza uma operação de escrita no endereço especificado
				}
				reads++; // Contabiliza uma leitura
			}
			else
			{
				printf("ERRO: Os dados do arquivo de entrada estao em formato incorreto.");
				return 0;
			}
		}

		fclose(file); // Fecha o arquivo de entrada
	}
	else
	{
		printf("ERRO: Arquivo de entrada invalido.");
		return 0;
	}

	printf("\nExecutando o simulador...\n");
	printf("Arquivo de entrada: %s\n", filePath);
	printf("Tamanho da memoria: %iKB\n", memSize);
	printf("Tamanho das paginas: %iKB\n", pageSize);
	printf("Tecnica de reposicao: %s\n", alg);
	printf("Paginas lidas: %i\n", faults);
	printf("Paginas escritas: %i\n", writes);

	FreeMemory(); // Libera a memória alocada para as páginas
	
    return 0;
}

// Adiciona uma nova página à lista de páginas de memória
void AddNewPage(char value[9]){
	Page *current = (Page *)malloc(sizeof(Page)); // Aloca memória para uma nova página
	strcpy(current->address, value); // Copia o endereço fornecido para a página
	current->next = NULL; // Define o próximo ponteiro como NULL

	if (usedPages == 0){
		first = current; // Se não houver páginas usadas, a nova página é a primeira
		last = first; // Como só há uma página, ela também é a última
	}else{
		last->next = current; // Adiciona a nova página no final da lista
		last = current; // Atualiza o ponteiro "last" para a nova última página
	}

	if (usedPages < numPages)
		usedPages++; // Se ainda houver espaço disponível na memória, incrementa o número de páginas usadas

	writes++; // Contabiliza uma escrita
}

// Implementa o algoritmo Random (Aleatório)
void Random(char value[9]){
	writes++; // Contabiliza uma escrita

	srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios com o tempo atual
	int index = rand() % usedPages; // Gera um índice aleatório dentro do intervalo das páginas usadas
	Page *tmp = first;

	for (int i = 0; i < index; i++){
		tmp = tmp->next; // Percorre a lista de páginas até o índice gerado
	}

	strcpy(tmp->address, value); // Substitui o endereço da página encontrada pelo novo endereço
}
