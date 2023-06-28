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

// Implementa o algoritmo LRU (Least Recently Used)
void LRU(char value[9])
{
	AddNewPage(value); // Adiciona uma nova página

	if (usedPages == numPages)
		first = first->next; // Se todas as páginas estiverem sendo usadas, remove a página mais antiga (a primeira)
}

// Implementa o algoritmo FIFO (First-In-First-Out)
void FIFO(char value[9])
{
	AddNewPage(value); // Adiciona uma nova página

	if (usedPages == numPages)
		first = first->next; // Se todas as páginas estiverem sendo usadas, remove a página mais antiga (a primeira)
}

// Procura por um endereço na lista de páginas
bool Find(char value[9])
{
	Page *tmp = first, *prev = NULL;

	while (tmp != NULL)
	{
		if (strcmp(tmp->address, value) == 0) // Compara o endereço atual com o endereço procurado
		{
			if (strcmp(alg, "lru") == 0)
			{
				if (prev != NULL)
				{
					if (tmp->next != NULL)
						prev->next = tmp->next; // Remove a página encontrada da lista
				}
				else
				{
					first = first->next; // Se a página encontrada for a primeira, atualiza o ponteiro "first"
				}

				last->next = tmp; // Move a página encontrada para o final da lista
				last = tmp; // Atualiza o ponteiro "last" para a nova última página
				tmp->next = NULL; // Define o próximo ponteiro da página encontrada como NULL
			}

			return true; // Retorna true se o endereço for encontrado
		}

		prev = tmp; // Atualiza o ponteiro "prev" para o nó atual
		tmp = tmp->next; // Atualiza o ponteiro "tmp" para o próximo nó
	}

	return false; // Retorna false se o endereço não for encontrado
}

// Substitui uma página na memória de acordo com o algoritmo especificado
void ReplacePage(char value[9])
{
	if (strcmp(alg, "lru") == 0)
	{
		LRU(value);
	}
	else if (strcmp(alg, "random") == 0)
	{
		Random(value);
	}
	else if (strcmp(alg, "fifo") == 0)
	{
		FIFO(value);
	}
}

// Realiza uma operação de escrita no endereço especificado
void WriteAddress(char value[9])
{
	if (usedPages < numPages)
	{
		AddNewPage(tmpAddress); // Se ainda houver espaço disponível na memória, adiciona uma nova página
	}
	else
	{
		faults++; // Contabiliza uma falha (page fault)
		ReplacePage(tmpAddress); // Substitui uma página de acordo com o algoritmo especificado
	}
}

// Libera a memória alocada para as páginas
void FreeMemory()
{
	Page *tmp = first;
	Page *tmp2;

	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2); // Libera a memória alocada para cada página
	}
}
