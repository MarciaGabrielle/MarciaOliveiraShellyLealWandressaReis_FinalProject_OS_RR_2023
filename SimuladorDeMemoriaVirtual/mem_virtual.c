#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
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