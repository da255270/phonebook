#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    clock_t start, end;
    double cpuTimeUsed1, cpuTimeUsed2;

    /* check file opening*/     
    fp = fopen("./dictionary/words.txt", "r");
    if (fp == NULL){
        printf("cannot open the file\n");
        return 0;
    }

    /* create hash table. table size is a prime number*/
    int tableSize = 65536;
    hashTable *ht = createHashTable(tableSize);
    printf("hash table size : %d\n", tableSize);

    /* build the lastNameEntry */
    lastNameEntry *pHead, *lne;
    pHead = (lastNameEntry *) malloc(sizeof(lastNameEntry));
    printf("size of entry : %lu bytes\n", sizeof(lastNameEntry));
    lne = pHead;
    lne->pNext = NULL;
    start = clock();
    while (fgets(line, sizeof(line), fp)){
        while(line[i] != '\0'){
            i++;
        }
        line[i-1] = '\0';
        i = 0;
        append(line, ht);
    }
    end = clock();
    cpuTimeUsed1 = ((double) (end - start)) / CLOCKS_PER_SEC;

    /* input lastName */
    char input[INPUT_SIZE][MAX_LAST_NAME_SIZE] = {"uninvolved","zyxel","whiteshank", 
                "odontomous", "pungoteague", "reweighted", "xiphisternal", "yakattalo"};
    
    /* compute the execution time */
    int j;
    lne = pHead;
    start = clock();
    for(j = 0; j < INPUT_SIZE; j++){
        findName(input[j], ht);
        lne = pHead;
    }
    end = clock();
    cpuTimeUsed2 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("execution time of appendHash() : %lf\n", cpuTimeUsed1);
    printf("execution time of findNameHash() : %lf\n", cpuTimeUsed2);

    /* release the resource */
    free(pHead);
    fclose(fp);

    return 0;
}
