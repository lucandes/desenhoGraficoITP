#include <stdlib.h>

#ifndef SAFESTD_H
#define SAFESTD_H

void *safeMalloc(size_t size);
void *safeCalloc(int times, size_t size);

#endif