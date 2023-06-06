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

struct Cofetarie generareCofetarie(int id, char* nume) {
    struct Cofetarie* c = malloc(sizeof(struct Cofetarie));
    c->id = id;
    c->nume = malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(c->nume, nume);
    return *c;
}

void afisareCofetarie(struct Cofetarie c) {
    printf("Cofetaria %s are id-ul %d", c.nume, c.id);
}

void inserareArbore(struct Nod** root, struct Cofetarie c) {
    if (*root == NULL) {
        struct Nod* newNode = malloc(sizeof(struct Nod));
        newNode->info = c;
        newNode->dreapta = NULL;
        newNode->stanga = NULL;
        *root = newNode;
    }
    else {
        if (c.id < (*root)->info.id)
            inserareArbore(&(*root)->stanga, c);
        else
            inserareArbore(&(*root)->dreapta, c);
    }
}

void afisareInOrdine(struct Nod* root) {
    if (root == NULL) {
        return;
    }
    else {
        afisareInOrdine(root->stanga);
        afisareCofetarie(root->info);
        printf("\n");
        afisareInOrdine(root->dreapta);
    }
}

void afisarePreOrdine(struct Nod* root) {
    if (root == NULL) {
        return;
    }
    else {
        afisareCofetarie(root->info);
        printf("\n");
        afisarePreOrdine(root->stanga);
        afisarePreOrdine(root->dreapta);
    }
}

void dezalocareArbore(struct Nod** root) {
    if (*root == NULL) {
        return;
    }
    else {
        dezalocareArbore(&(*root)->stanga);
        dezalocareArbore(&(*root)->dreapta);
        free((*root)->info.nume);
        free(*root);
        *root = NULL;
    }
}

void cautareDupaId(struct Nod* root, int id) {
    if (root == NULL) {
        return;
    }
    else {
        if (id == root->info.id) {
            printf("\nCofetaria pe care o cautati este aceasta: ");
            afisareCofetarie(root->info);
        }
        else if (id > root->info.id) {
            cautareDupaId(root->dreapta, id);
        }
        else if (id < root->info.id) {
            cautareDupaId(root->stanga, id);
        }
    }
}

int calculInaltime(struct Nod* root) {
    if (root == NULL) {
        return 0;
    }
    else {
        int inaltimeStanga = calculInaltime(root->stanga);
        int inaltimeDreapta = calculInaltime(root->dreapta);
        if (inaltimeDreapta > inaltimeStanga) {
            return inaltimeDreapta + 1;
        }
        else {
            return inaltimeStanga + 1;
        }
    }
}

void echilibrareArbore(struct Nod** root) {
    if (*root == NULL) {
        return;
    }
    else {
        //Calculam diferenta dintre ramuri, daca nu e mai mare sau egala cu 2, arborele nu e dezechilibrat
        int inaltimeStanga = calculInaltime((*root)->stanga);
        int inaltimeDreapta = calculInaltime((*root)->dreapta);

        //Daca arborele prezinta o ramura stanga prea lunga
        if (inaltimeStanga - inaltimeDreapta >= 2) {
            struct Nod* temp = (*root)->stanga;
            (*root)->stanga = temp->dreapta;
            temp->dreapta = *root;
            *root = temp;
        }
        //Daca arborele prezinta o ramura dreapta prea lunga
        else if (inaltimeStanga - inaltimeDreapta <= -2) {
            struct Nod* temp = (*root)->dreapta;
            (*root)->dreapta = temp->stanga;
            temp->stanga = *root;
            *root = temp;
        }
        else {
            printf("Arborele nu are dezechilibru mai mare decat 2");
        }

    }
}

void inserareArboreAVL(struct Nod** root, struct Cofetarie c) {
    if (*root == NULL) {
        struct Nod* newNode = malloc(sizeof(struct Nod));
        newNode->info = c;
        newNode->stanga == NULL;
        newNode->dreapta == NULL;
        *root = newNode;
    }
    else {
        if (c.id < (*root)->info.id)
            inserareArbore(&(*root)->stanga, c);
        else
            inserareArbore(&(*root)->dreapta, c);
    }

    echilibrareArbore(&(*root));
}

int main()
{
    
    struct Nod* root = NULL;
    inserareArbore(&root, generareCofetarie(10, "Cofetaria 3"));
    inserareArbore(&root, generareCofetarie(5, "Cofetaria 1"));
    inserareArbore(&root, generareCofetarie(15, "Cofetaria 2"));
    inserareArbore(&root, generareCofetarie(3, "Cofetaria 4"));
    inserareArbore(&root, generareCofetarie(1, "Cofetaria 5"));

    printf("\nAfisare InOrdine:\n");
    afisareInOrdine(root);

    printf("\nAfisare PreOrdine:\n");
    afisarePreOrdine(root);

    cautareDupaId(root, 4);

    printf("\n\nInaltime este: %d", calculInaltime(root));

    inserareArboreAVL(&root, generareCofetarie(7, "Cofetarie aaa"));
    printf("\nAfisare PreOrdine:\n");
    afisarePreOrdine(root);

    //echilibrareArbore(&root);
    //printf("\nAfisare PreOrdine:\n");
    //afisarePreOrdine(root);

    dezalocareArbore(&root);
}

