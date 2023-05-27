#include <stdio.h>
#include <malloc.h>
#include<string.h>
#include <math.h>
#include <stdbool.h>

#include "Hashtable.h"

#pragma warning(disable: 4996)

#define PRIME1 151
#define PRIME2 163

static struct Item deletedItem = { NULL, NULL };

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
    return newHashtable;
}

void deleteHashtable(struct Hashtable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        struct Item* item = hashtable->items[i];
        if (item != NULL) {
            deleteItem(item);
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
        hash += (long)pow(a, lenString - (i + 1)) * string[i];
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

//AICI IMPLMENTAM MEDODELE DE INSERARE, CAUTARE SI STERGERE
void insertItem(struct Hashtable* hashtable, const char* key, const char* value) {
    struct Item* newItem = addNewItem(key, value);  //Aici poti lua direct prin parametri un item, nu neaparat componentele sale
    //index e practic pozitia in hastable, dar trebuie la randul ei sa fie trecuta prin hash,
    //ca sa ii putem accesa valoarea prin intermediul codului obtinut
    //atunci cand generam index-ul cu attemp(al treile parametru 0), ajungem la inceputul hashtable-ului
    int index = getHash(newItem->key, hashtable->size, 0);  
    struct Item* currentItem = hashtable->items[index];
    int i = 1;
    while (currentItem != NULL && currentItem != &deletedItem) {   //Aici ii spunem "atat timp cat nu avem o coliziune in hashtable"
        index = getHash(newItem->key, hashtable->size, i);
        currentItem = hashtable->items[index];
        i++;
    }
    hashtable->items[index] = newItem;
    hashtable->count++;
}

char* searchHashtable(struct Hashtable* hashtable, const char* key) {
    int index = getHash(key, hashtable->size, 0);   //Din nou, aici index e pozitia, dar trebuie hash-uita mai intai
    struct Item* item = hashtable->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &deletedItem) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = getHash(key, hashtable->size, i);
        item = hashtable->items[index];
        i++;
    }
    return NULL;
}

//Explicatie pentru utilizarea variabilei globale deletedItem:
//odata ce un item e sters, poate sa fie problematic daca doar ii dai valoarea NULL(in special la cautare)
//asa ca odata ce un item e sters, ii asignam deletedItem ca valoarea
//e un mod de ai spune calculatorului "asta nu e un simplu spatiu gol, e un fost item care acum e sters"
//am gasit si alte moduri de stergere, dar asta pare cel mai ok ca si logica, fara sa trebuiasca
//sa ai 15 cazuri diferite la fiecare metoda care sa combata problema mai sus mentionata
void deleteHashtableItem(struct Hashtable* hashtable, const char* key) {
    int index = getHash(key, hashtable->size, 0);
    struct Item* item = hashtable->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &deletedItem) {
            if (strcmp(item->key, key) == 0) {
                deleteItem(item);
                hashtable->items[index] = &deletedItem;
            }
        }
        index = getHash(key, hashtable->size, i);
        item = hashtable->items[index];
        i++;
    }
    hashtable->count--;
}

//La printat trebuie sa luam in calcul ca nu se patreaza ordinea,
//Daca ai 5 iteme, poate sa fie in ordine, sau 3, 4, 5, 2, 1
//E dupa functia hash, de asta printarea e cam inutila in realitate
//Mai importanta e cautarea
void printHashtable(struct Hashtable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        struct Item* item = hashtable->items[i];
        if (item != NULL & item != &deletedItem) {
            printf("Item%d: { Key: %s, Value: %s } ", i, item->key, item->value);
        }
   }

}

int main()
{
    struct Hashtable* ht1 = newHashtable();
    insertItem(ht1, "key1", "value1");
    insertItem(ht1, "key2", "value2");
    insertItem(ht1, "key3", "value3");
    
    printf("Aveti hashtable-ul cu valorile:\n");
    printHashtable(ht1);
    printf("\n1)Adauga un element");
    printf("\n2)Sterge un element");
    printf("\n3)Cauta un element");
    printf("\n4)Sterge hashtable-ul");
    printf("\n0)Iesi din program");

    bool done = 0;

    while (!done) {
        printf("\nCe operatie doritia sa realizati?\n");

        int parameter = -1;
        char* key[100];
        char* value[100];


        scanf("%d", &parameter);

        if (parameter == 0) {
            printf("Hashtable final:");
            printHashtable(ht1);
            done = 1;
        }

        if (parameter == 1) {
            printf("Ce cheie doriti sa adaugati?");
            scanf("%s", key);
            printf("Ce valoare are?");
            scanf("%s", value);
            insertItem(ht1, key, value);
            printHashtable(ht1);
        }

        if (parameter == 2) {
            printf("Dati cheia elementului pe care doriti sa-l stergeti: ");
            scanf("%s", key);
            deleteHashtableItem(ht1, key);
            printHashtable(ht1);
        }

        if (parameter == 3) {
            printf("Dati cheia elementului pe care doriti sa-l cautati: ");
            scanf("%s", key);
            printf(searchHashtable(ht1, key));
        }

        if (parameter == 4) {
            deleteHashtable(ht1);
            printf("Hashtable-ul a fost eliminat");
        }
    }
}

