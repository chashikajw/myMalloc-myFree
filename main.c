#include <stdio.h>
#include <stdlib.h>

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
    int blocksize;
    char *nxtblock = head;
    char findflg = 'N';
    char *backblock;

    while((nxtblock != block )){
        blocksize = *(int *)(nxtblock+1);

        if(*nxtblock == endFlg){
            printf("invalid address");
            break;
        }
        backblock = nxtblock;
        nxtblock = nxtblock + blocksize;

    }
    if(*nxtblock != endFlg){
        *nxtblock = freeFlg;

        int num = *(int *)(nxtblck+1);
        char *isNxtblockFree = nxtblock + num;

       if(*isNxtblockFree == freeFlg){     //check wheter next blog is free and merge it
            *(int *)(nxtblock+1) = *(int *)(nxtblock+1)+  *(int *)(isNxtblockFree+1);
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

int main(){
    char *x = (char*)MyMalloc(110000);
    char *y = (char*)MyMalloc(100);
    char *z = (char*)MyMalloc(100);
    printMemory();
    MyFree(y);
    printMemory();
    MyFree(z);
    //MyFree(x);
    printMemory();
    return 0;
}





