#include <stdlib.h>

#include "phonebook_opt.h"

hashTable *createHashTable(int tableSize)
{
    hashTable *ht = NULL;
    int i;

    if( tableSize < 1 ){
        return NULL;
    }

    /* Allocate the table itself. */
    if((ht = (hashTable *) malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }

    /* Allocate array of list. */
    if( (ht->list = (lastNameEntry **)malloc(sizeof(lastNameEntry *)*tableSize)) == NULL ) {
        return NULL;
    }

    /* Allocate list header */
    for( i = 0; i < tableSize; i++ ) {
        ht->list[i] = NULL;
    }

    ht->tableSize = tableSize;

    return ht;
}

lastNameEntry* findName(char *key, hashTable *ht)
{
    lastNameEntry *lne;
    hashIndex index = hash(key, ht);
    
    /* search the bucket */
    for(lne = ht->list[index]; lne != NULL; lne = lne->pNext){
        if ( strcasecmp(key, lne->lastName) == 0 ){
            printf(" %12s is found!\n", key);
            return lne;
        }
    }
    printf(" %12s is not found!\n", key);
    return NULL;
}

int append(char *key, hashTable *ht)
{
    hashIndex index = hash(key, ht);
    lastNameEntry *newEntry;
    
    /* attempt to allocate memory for lastNameEntry */
    if ((newEntry = (lastNameEntry *) malloc(sizeof(lastNameEntry))) == NULL){
        return 2;
    }

    /* Insert into list */
    strcpy(newEntry->lastName, key);
    newEntry->pNext = ht->list[index];
    ht->list[index] = newEntry;

    return 0;
}
/*djb2 + hash powers of 2 : 65536*/
int hash(char *key)
{
    unsigned long hashVal = 5381;   
    int c;
    while (c = *key++)
       hashVal = ((hashVal << 5) + hashVal ) + c; /* hashVal * 33 + c */
    return hashVal & 0x7fff;
}



