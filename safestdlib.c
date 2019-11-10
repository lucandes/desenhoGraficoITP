#include "safestdlib.h"

/*********************************
funções que verificam se a alocação foi 
realizada com sucesso antes de retornar 
*********************************/

void *safeMalloc(size_t size){
	void *p;
	p = malloc(size);

	if (p == NULL)
		exit(1);

	return p;
}

void *safeCalloc(int times, size_t size){
	void *p;
	p = calloc(times, size);

	if (p == NULL)
		exit(1);

	return p;
}
