
#include "mymalloc.h"

void* MyMalloc(size_t);
void MyFree(void*);
char* bestFitBlock(size_t);
void printMemory();


char Mymemory[25000] = {'\0'};
char *head = Mymemory;
char alocatedFlg = 'a';
char freeFlg = 'f';
char endFlg = 'E';


void* MyMalloc(size_t size)
{

    if(!*head){
        *(head + 24999) = endFlg;
        *(int *)(head +1) = 24999;
        *head = freeFlg;

    }
    if(!size){
        return NULL;
    }

    char *canAllocateSize = bestFitBlock(size);

    if(canAllocateSize){

            int num = *(int *)(canAllocateSize +1);
           *(canAllocateSize) = alocatedFlg;
           *(int *)(canAllocateSize+1) = size + 5;

            if(*(canAllocateSize + size+5) != endFlg){
                *(canAllocateSize + size+5) = freeFlg;
                *(int *)(canAllocateSize + size+6) = num - size - 5;
            }
    }
    else{
        printf("not enough memory ");
    }

    return (void *)canAllocateSize;

}

void MyFree(void *ptr)
{
    char *block = (char *)ptr;
    int blcksize;
    char *nxtblck = head;
    char findflg = 'N';
    char *backblck;

    while((nxtblck != block )){
        blcksize = *(int *)(nxtblck+1);

        if(*nxtblck == endFlg){
            printf("invalid address");
            break;
        }
        backblck = nxtblck;
        nxtblck = nxtblck + blcksize;

    }
    if(*nxtblck != endFlg){
        *nxtblck = freeFlg;

        int num = *(int *)(nxtblck+1);
        char *isNxtblockFree = nxtblck + num;

       if(*isNxtblockFree == freeFlg){     //check wheter next blog is free and merge it
            *(int *)(nxtblck+1) = *(int *)(nxtblck+1)+  *(int *)(isNxtblockFree+1);
       }
       if(*backblck == freeFlg){     //check wheter prvious blog is free and merge it
            *(int *)(backblck+1) = *(int *)(backblck+1)+  *(int *)(nxtblck+1);
       }


    }
    else{
        printf("invalid address");
    }


}

char* bestFitBlock(size_t size)
{

    char *nxtblck = head;
    int blcksize;
    char *bestblck = NULL;
    int bestblcksiz = -1;

    while(*nxtblck != endFlg){

        blcksize = *(int *)(nxtblck+1);
        if((*nxtblck == freeFlg) && blcksize >= size + 5 ){
            if(bestblcksiz==-1){
                bestblck = nxtblck;
                bestblcksiz = blcksize;


            }
            else if(bestblcksiz> blcksize){
                bestblck = nxtblck;
                bestblcksiz = blcksize;

            }

        }

        nxtblck = nxtblck + blcksize;

    }

    return bestblck;
}

void printMemory()
{

    char *nxtblck = head;
    int blcksize;
    char *bestblck = NULL;
    int bestblcksiz = -1;

    while(*nxtblck != endFlg){

        blcksize = *(int *)(nxtblck+1);

        printf("%c   ",*nxtblck);
        printf("Address: %u   ",nxtblck);
        printf("blockSize: %d\n",*(int *)(nxtblck+1));
        nxtblck = nxtblck + blcksize;

    }
    printf("++++++\n");

}



