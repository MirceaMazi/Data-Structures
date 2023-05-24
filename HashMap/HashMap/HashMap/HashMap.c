#include <stdio.h>
#include <malloc.h>
#include<string.h>


//Aici ar trebui sa fie schimbarea
#include "Hashtable.h"

#define PRIME1 151
#define PRIME2 163

//AICI E LUCRUL CU OBIECTELE DIN CADRUL HASHTABLE-ULUI  
//Aici o sa folosim static fiindca functiile o sa fie chemate
//doar de cod intern hashtable-ului
static struct Item* addNewItem(const char* key, const char* value) { 
    struct Item* newItem = malloc(sizeof(struct Item));
    newItem->key = _strdup(key);
    newItem->value = _strdup(value);
    return newItem;
}

static void deleteItem(struct Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

//AICI E LUCRUL CU HASHTABLE-UL PROPRIU ZIS
struct Hashtable* newHashtable() {
    struct Hashtable* newHashtable = malloc(sizeof(struct Hashtable));

    newHashtable->size = 53; //Asta e un numar ales arbitrar
    newHashtable->count = 0;
    newHashtable->items = calloc((size_t)newHashtable->size, sizeof(struct Item*));
    //Aici e putin mai complex:
    //1. void *calloc( size_t num, size_t size ); asta e structura lui calloc;
    //2. El aloca memorie pentru un vector de num obiecte, de marimea size si ii initializeaza pe toti cu 0;
    //3. Size_t de acolo e marimea maxima posibila a unui obiect
    //4. In termeni simpli, acolo alocam memorie pentru un vector de obiecte Item, 
    //si initializam spatiul ala din memorie cu 0;
}

void deleteHashtable(struct Hashtable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        struct Item* item = hashtable->items[i];
        if (item != NULL) {
            deleteHashtable(item);
        }
    }
    free(hashtable->items);
    free(hashtable);
}

//AICI E IMPLEMENTATA FUNCTIA HASH
//Ideea la functia hash e asta, sunt 3 pasi:
//1. Iei un string
//2. String-ul ala il convertesti intr-un numar si il prelucrezi
//3. Imparti la numarul de elemente pe care le are tabela ta,
//pentru a avea o distributie uniforma; distributie neuniforma => mai multe coliziuni => big no-no
static int hashFunction(const char* string, const int a, const int numBuckets) {
    long hash = 0;
    const int lenString = strlen(string);
    for (int i = 0; i < lenString; i++) {
        hash += (long)pow(a, lenString - (i + 1) * string[i]);
        hash = hash % numBuckets;
    }
    return (int)hash;
}

//AICI E IMPLEMENTATA METODA DOUBLE-HASHING DE EVITARE A COLIZIUNILOR
static int getHash(const char* string, const int numBuckets, const int attempt) {
    const int hashA = hashFunction(string, PRIME1, numBuckets);
    const int hashB = hashFunction(string, PRIME2, numBuckets);

    return (hashA + (attempt * (hashB + 1))) % numBuckets;
}
int main()
{
    struct Hashtable* ht1 = newHashtable();
    deleteHashtable(ht1);
}

