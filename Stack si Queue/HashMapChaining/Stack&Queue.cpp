#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct Biblioteca Biblioteca;

struct Biblioteca
{
	long id;
	char* nume;
	int nrCarti;
};

struct Nod
{
	Biblioteca info;
	Nod* next;
};

Biblioteca initializeazaBib(long id, const char* nume, int nrCarti)
{
	Biblioteca b;
	b.id = id;
	b.nrCarti = nrCarti;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	return b;
}

void afisareBib(Biblioteca b)
{
	printf("Biblioteca %s are id-ul %ld si %i carti\n", b.nume, b.id, b.nrCarti);
}

void push(Biblioteca b, Nod** varf)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = *varf;
	nou->info = b;
	*varf = nou;

}

Biblioteca pop(Nod** varf)
{
	Biblioteca b;
	b.id = -1;
	b.nrCarti = 0;
	b.nume = NULL;
	if ((*varf) != NULL)
	{
		b = (*varf)->info;
		Nod* aux = (*varf);
		*varf = (*varf)->next;
		free(aux);
	}
	return b;
}

void Put(Nod** prim, Biblioteca b)
{
	Nod* aux = *prim;
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = b;
	nodNou->next = NULL;
	if ((*prim) != NULL)
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nodNou;

	}
	else
	{
		*prim = nodNou;
	}
}

Biblioteca cautatreIdStiva(Nod** varf, long id)
{
	Biblioteca b;
	b.id = 0;
	b.nume = NULL;
	b.nrCarti = 0;
	Nod* aux = NULL;
	while ((*varf) != NULL && id != (*varf)->info.id)
	{
		push(pop(varf), &aux);
	}
	if ((*varf) != NULL)
	{
		b = pop(varf);
	}
	while (aux)
	{
		push(pop(&aux), varf);
	}
	return b;
}

int main()
{
	Nod* stiva = NULL;
	push(initializeazaBib(12, "Bib centrala", 146), &stiva);
	push(initializeazaBib(13, "Bib nationala", 479), &stiva);
	push(initializeazaBib(16, "Bib bucuresti", 61), &stiva);

	Biblioteca b = cautatreIdStiva(&stiva, 13);
	afisareBib(b);
	Biblioteca bib;

	printf("\nAfisare stiva de biblioteci:\n");
	while (stiva != NULL)
	{
		bib = pop(&stiva);
		afisareBib(bib);
		free(bib.nume);
	}

	Nod* coada = NULL;
	Put(&coada, initializeazaBib(17, "Bib centrala", 147));
	Put(&coada, initializeazaBib(18, "Bib centrala", 148));
	Put(&coada, initializeazaBib(19, "Bib centrala", 149));
	printf("\nAfisare coada de biblioteci:\n");
	while (coada != NULL)
	{
		bib = pop(&coada);
		afisareBib(bib);
		free(bib.nume);
	}
	return 0;
}