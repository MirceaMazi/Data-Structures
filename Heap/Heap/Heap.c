#pragma warning(disable: 4996)

#include <stdio.h>
#include <malloc.h>

struct Echipa {
	int prioritate;
	char* denumire;
	int nrJucatori;
};

struct Heap {
	int dimensiune;
	struct Echipa* vector;
};

struct Echipa generareEchipa(int prioritate, char* denumire, int nrJucatori) {
	struct Echipa* e = malloc(sizeof(struct Echipa));
	
	e->denumire = malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(e->denumire, denumire);
	e->prioritate = prioritate;
	e->nrJucatori = nrJucatori;

	return *e;
}

void afisareEchipa(struct Echipa e) {
	printf("Echipa %s are %d jucatori si este a %d-a", e.denumire, e.nrJucatori, e.prioritate);
}

void parcurgereHeap(struct Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisareEchipa(h.vector[i]);
		printf("\n");
	}
}

void filtrareHeap(struct Heap h, int index) {
	if (h.dimensiune > 0) {
		int indexS = 2 * index + 1;
		int indexD = 2 * index + 2;
		int pozMax = index;

		if (h.dimensiune > indexS && h.vector[indexS].prioritate > h.vector[pozMax].prioritate) {
			pozMax = indexS;
		}

		if (h.dimensiune > indexD && h.vector[indexD].prioritate > h.vector[pozMax].prioritate) {
			pozMax = indexD;
		}

		if (pozMax != index) {
			struct Echipa temp = h.vector[index];
			h.vector[index] = h.vector[pozMax];
			h.vector[pozMax] = temp;

			filtrareHeap(h, pozMax);
		}
	}
}

void extragere(struct Heap* h, struct Echipa* e) {
	*e = h->vector[0];
	struct Echipa temp = h->vector[0];
	h->vector[0] = h->vector[h->dimensiune - 1];
	h->vector[h->dimensiune - 1] = temp;
	h->dimensiune--;
	filtrareHeap(*h, 0);

}

int main()
{
	struct Heap h;
	h.dimensiune = 10;
	h.vector = malloc(sizeof(struct Echipa) * h.dimensiune);
	for (int i = 0; i < h.dimensiune; i++) {
		h.vector[i] = generareEchipa(i + 1, "Echipa", i + 2);
	}


	parcurgereHeap(h);

	for (int i = h.dimensiune / 2 - 1; i >= 0; i--) {
		filtrareHeap(h, i);
	}

	printf("\n\n Parcurgere dupa filtrare:\n");
	parcurgereHeap(h);

	struct Echipa e;
	extragere(&h, &e);

	printf("\n\n");
	afisareEchipa(e);
	printf("\n\n");
	parcurgereHeap(h);
}


