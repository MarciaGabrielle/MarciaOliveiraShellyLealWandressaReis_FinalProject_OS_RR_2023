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

typedef struct Page{
	char address[9];
	struct Page *next;
} Page;

FILE *file;
Page *first, *last;
char *alg, *filePath, line[20], tmpAddress[9];
int pageSize, memSize, numPages;
int operations = 0, reads = 0, writes = 0, hits = 0, misses = 0, faults = 0, usedPages = 0;

int main(){

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
