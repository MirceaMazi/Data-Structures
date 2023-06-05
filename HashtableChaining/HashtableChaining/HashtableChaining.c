#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

struct Biblioteca {
	long id;
	char* nume;
	int nrCarti;
};

struct Nod {
	struct Biblioteca info;
	struct Nod* next;
};

struct Hashtable {
	int size;
	struct Nod** chain;
};

struct List {
	struct Nod* head;
	struct List* next;
};

struct Biblioteca initializareBiblioteca(long id, char* nume, int nrCarti) {
	struct Biblioteca b;
	b.id = id;
	b.nrCarti = nrCarti;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);

	return b;
}

struct Biblioteca printBiblioteca(struct Biblioteca b) {
	printf("Biblioteca cu id-ul %ld are numele %s si %d carti", b.id, b.nume, b.nrCarti);
};

struct Hashtable initializareHashtable(int dim) {
	struct Hashtable h;
	h.size = dim;
	h.chain = malloc(sizeof(struct Nod*) * dim);

	for (int i = 0; i < dim; i++) {
		h.chain[i] = NULL;
	}

	return h;
}

int Hash(int dim, long id) {
	return id % dim;
}

void inserareFinal(struct Nod** head, struct Biblioteca b) {
	struct Nod* newNode = malloc(sizeof(struct Nod));
	newNode->info = b;
	newNode->next = NULL;
	if (*head != NULL) {
		struct Nod* current = *head;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}
	else {
		*head = newNode;
	}
}

void inserareHashtable( struct Biblioteca b, struct Hashtable h) {
	if (h.size > 0) {
		int pozitie = Hash(h.size, b.id);
		if (pozitie >= 0 && pozitie < h.size) {
			inserareFinal(&(h.chain[pozitie]), b);
		}
	}
}

void afisareHashtable(struct Hashtable h) {
	for (int i = 0; i < h.size; i++) {
		if (h.chain[i] != NULL) {
			printf("Pozitia %d contine informatiile:\n", i);
			struct Nod* current = h.chain[i];
			while (current) {
				printBiblioteca(current->info);
				printf("\n");
				current = current->next;
			}
		}
		else {
			printf("Pozitia %d este goala\n", i);
		}
	}
}

void deleteBiblioteca(struct Biblioteca* b) {
	free(b->nume);
}

void stergeHashtable(struct Hashtable* h) {
	for (int i = 0; i < h->size; i++) {
		struct Nod* current = h->chain[i];
		while (current != NULL) {
			struct Nod* next = current->next;
			deleteBiblioteca(&(current->info));
			free(current);
			current = next;
		}
	}
	free(h->chain);
}

struct List* hashtableToLists(struct Hashtable h) {
	struct List* result = NULL;

	for (int i = 0; i < h.size; i++) {
		if (h.chain[i] != NULL) {
			struct List* newList = malloc(sizeof(struct List));
			newList->head = h.chain[i];
			newList->next = NULL;

			if (result == NULL) {
				result = newList;
			}
			else {
				struct List* current = result;
				while (current->next != NULL) {
					current = current->next;
				}
				current->next = newList;
			}
		}
	}

	return result;
}

int main()
{
	struct Hashtable h = initializareHashtable(10);
	inserareHashtable(initializareBiblioteca(123, "Bib1", 130), h);
	inserareHashtable(initializareBiblioteca(128, "Bib2", 130), h);
	inserareHashtable(initializareBiblioteca(125, "Bib3", 130), h);
	inserareHashtable(initializareBiblioteca(228, "Bib4", 130), h);
	afisareHashtable(h);
	printf("\n\n\n\n");
	struct List* resultList = hashtableToLists(h);

	// Iterate over the list of lists and print the elements
	struct List* current = resultList;
	while (current != NULL) {
		struct Nod* currentNod = current->head;
		while (currentNod != NULL) {
			printBiblioteca(currentNod->info);
			printf("\n");
			currentNod = currentNod->next;
		}
		current = current->next;
	}

	stergeHashtable(&h);
}

