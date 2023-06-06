#pragma warning(disable: 4996)

#include <stdio.h>
#include <malloc.h>

struct Cofetarie {
    int id;
    char* nume;
};

struct Nod {
    struct Cofetarie info;
    struct Nod* stanga;
    struct Nod* dreapta;
};

struct Cofetarie* initializareCofetarie(int id, char* nume) {
    struct Cofetarie* c = malloc(sizeof(struct Cofetarie));
    c->id = id;
    c->nume = malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(c->nume, nume);
    return c;
}

void afisareCofetarie(struct Cofetarie c) {
    printf("Cofetaria %s are id-ul %d\n", c.nume, c.id);
}

void inserareArbore(struct Cofetarie c, struct Nod** root) {
    if (*root == NULL) {
        struct Nod* newNode = malloc(sizeof(struct Nod));
        newNode->info = c;
        newNode->stanga = NULL;
        newNode->dreapta = NULL;
        *root = newNode;
    }
    else {
        if (c.id > (*root)->info.id) {
            inserareArbore(c, &(*root)->dreapta);
        }
        else {
            inserareArbore(c, &(*root)->stanga);
        }

    }
}
//In ordine se refera la marime 1 > 2 > 3 > 4 s.a.m.d
void afisareInordine(struct Nod* root) {
    if (root != NULL) {
        afisareInordine(root->stanga);
        afisareCofetarie(root->info);
        afisareInordine(root->dreapta);
    }
}

//Pre ordine se refera la arbore, adica incepe cu radacina, dupa ramura stanga, dupa aia dreapta
void afisarePreordine(struct Nod* root) {
    if (root != NULL) {
        afisareCofetarie(root->info);
        afisareInordine(root->stanga);
        afisareInordine(root->dreapta);
    }
}

void dezalocareArbore(struct Nod** root) {
    if (*root != NULL) {
        dezalocareArbore(&(*root)->stanga);
        dezalocareArbore(&(*root)->dreapta);
        free((*root)->info.nume);
        free(*root);
        *root = NULL;
    }
    
}

void cautareId(struct Cofetarie** c, struct Nod* root, int id) {

    if (root != NULL) {
        if (root->info.id == id) {
            *c = initializareCofetarie(id, root->info.nume);
        }
        else {
            if (id < root->info.id) {
                cautareId(c, root->stanga, id);
            }
            else {
                cautareId(c, root->dreapta, id);
            }
        }
    }
    else {
        c = initializareCofetarie(-1, "");
    }
}

int calculInaltime(struct Nod* root) {
    if (root != NULL) {
        int inaltimeS = calculInaltime(root->stanga);
        int inaltimeD = calculInaltime(root->dreapta);

        if (inaltimeD > inaltimeS) {
            return inaltimeD + 1;
        }
        else {
            return inaltimeS + 1;
        }
    }
    else {
        return 0;
    }
}

int main()
{
    struct Cofetarie* c = initializareCofetarie(1, "Cofetaria 1");
    struct Cofetarie* c2 = initializareCofetarie(2, "Cofetaria 2");
    struct Cofetarie* c3 = initializareCofetarie(3, "Cofetaria 3");
    struct Cofetarie* c4 = initializareCofetarie(4, "Cofetaria 4");
    struct Cofetarie* c5 = initializareCofetarie(5, "Cofetaria 5");
    afisareCofetarie(*c);
    struct Nod* root = malloc(sizeof(struct Nod));
    root = NULL;
    inserareArbore(*c3, &root);
    inserareArbore(*c, &root);
    inserareArbore(*c2, &root);
    inserareArbore(*c4, &root);
    inserareArbore(*c5, &root);
    afisareInordine(root);
    afisarePreordine(root);
    struct Cofetarie* c6 = malloc(sizeof(struct Cofetarie));
    cautareId(&c6, root, 4);
    afisareCofetarie(*c6);

    int inaltime = calculInaltime(root);
    printf("\nInaltimea este %d ", inaltime);
    
    afisarePreordine(root);
    dezalocareArbore(&root);
}


