
#ifndef mymalloc_h_   /* Include guard */
#define mymalloc_h_
#include <stdint.h>
#include <stddef.h> /* for size_t */

void* MyMalloc(size_t size);
void MyFree(void *ptr);
char* bestFitBlock(size_t size);
void printMemory();

#endif // mymalloc_h_
