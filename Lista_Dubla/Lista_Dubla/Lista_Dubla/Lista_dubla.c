#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#pragma warning(disable: 4996)

typedef struct node {
	int val;
	struct node* next;
	struct node* prev;
};

void printList(struct node* head) {
	struct node* current = head;

	printf("\nLista: ");

	while (current != NULL) {
		printf("%d ", current->val);
		current = current->next;
	}

	printf("\n");
}

void reversePrint(struct node* head) {
	struct node* tail = head;

	while (tail->next != NULL) {
		tail = tail->next;
	}

	printf("\nLista inversata: ");

	while (tail != head) {
		printf("%d ", tail->val);
		tail = tail->prev;
	}

	printf("%d ", tail->val);
}

void push(struct node* head, int val) {
	struct node* current = head;

	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(struct node));
	current->next->val = val;
	current->next->next = NULL;
	current->next->prev = current;
}

void pushBeginning(struct node** head, int val) {
	struct node* newNode = malloc(sizeof(struct node));

	newNode->val = val;
	newNode->next = *head;
	newNode->prev = NULL;

	if (*head != NULL) {
		(*head)->prev = newNode;
	}

	*head = newNode;
}

void pushMiddle(struct node** head, int position) {
	struct node* current = malloc(sizeof(struct node));
	current = *head;

	while (current->next->val < position) {
		current = current->next;
	}

	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = position;
	newNode->next = current->next;
	newNode->prev = current;
	current->next = newNode;	

	if (newNode->next != NULL) {
		newNode->next->prev = newNode;
	}
}

void pop(struct node** head) {
	struct node* nextNode = malloc(sizeof(struct node));

	if (*head == NULL) {
		return;
	}

	nextNode = (*head)->next;
	free(*head);
	*head = nextNode;
	nextNode->prev = NULL;

}

void popLast(struct node* head) {
	struct node* current = head;

	while (current->next->next != NULL) {
		current = current->next;
	}

	free(current->next);
	current->next = NULL;
}

void removeNode(struct node** head, int position) {
	struct node* current = *head;
	struct node* temporary = NULL;
	int i = 0;

	if (position == 0) {
		pop(head);
		return;
	}

	while (i < position - 1) {
		
		//Aici e o eroare de implementare, daca ii dai pozitia 50, dar ai doar 3 elemente, ti-l sterge pe ultimul.
		//Repar alta data, ca e tarziu.
		if (current->next->next == NULL) {
			popLast(*head);
			return;
		}

		current = current->next;
		i++;
	}

	if (current->next == NULL) {
		printf("Pozitia ceruta depaseste numarul de elemente din lista");
		return;
	}

	temporary = current->next;
	current->next = current->next->next;
	current->next->prev = current;
	free(temporary);

}

void deleteList(struct node** head) {
	struct node* current = *head;

	if (*head == NULL) {
		printf("Lista nu exista");
		return;
	}

	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		
	}else{
		do {
			current = (*head)->next;
			free(*head);
			current->prev = NULL;
			*head = current;
		} while (current->next != NULL);

		current = (*head)->next;
		free(*head);
		*head = current;
	}
}

//Din nou, identic ca la lista simpla, lucram cu valorile
//propriu-zise ale nodurilor, nu cu pointerii next sau prev
void sortList(struct node** head) {
	int variable;
	struct node* temporary1;
	struct node* temporary2;

	for (temporary1 = *head; temporary1 != NULL; temporary1 = temporary1->next) {
		for (temporary2 = temporary1->next; temporary2 != NULL; temporary2 = temporary2->next) {
			if (temporary1->val > temporary2->val) {
				variable = temporary1->val;
				temporary1->val = temporary2->val;
				temporary2->val = variable;
			}
		}
	}
}

int main() {
	struct node* head;
	struct node* one = malloc(sizeof(struct node));
	struct node* two = malloc(sizeof(struct node));
	struct node* three = malloc(sizeof(struct node));

	one->val = 1;
	two->val = 2;
	three->val = 3;

	one->next = two;
	one->prev = NULL;

	two->next = three;
	two->prev = one;

	three->next = NULL;
	three->prev = two;

	head = one;

	printf("Aveti lista cu valorile:\n");
	printList(head);
	printf("\n1)Adauga un element la final");
	printf("\n2)Adauga un element la inceput");
	printf("\n3)Sterge primul element");
	printf("\n4)Sterge ultimul element");
	printf("\n5)Elimina un element de la o pozitie data");
	printf("\n6)Sterge intreaga lista");
	printf("\n7)Sorteaza elementele listei");
	printf("\n8)Afisati lista in ordine inversa");
	printf("\n0)Iesi din program");

	bool done = 0;

	while (!done) {
		printf("\nCe operatie doritia sa realizati?\n");

		int parameter = -1;
		int element = -1;

		scanf("%d", &parameter);

		if (parameter == 0) {
			printf("Lista finala:");
			printList(head);
			done = 1;
		}

		if (parameter == 1) {
			printf("Ce element doriti sa adaugati?");
			scanf("%d", &element);
			push(head, element);
			printList(head);
		}

		if (parameter == 2) {
			printf("Ce element doriti sa adaugati?");
			scanf("%d", &element);
			pushBeginning(&head, element);
			printList(head);
		}

		if (parameter == 3) {
			pop(&head);
			printList(head);
		}

		if (parameter == 4) {
			popLast(head);
			printList(head);
		}

		if (parameter == 5) {
			printf("Ce element doriti sa eliminati?");
			scanf("%d", &element);
			removeNode(&head, element);
			printList(head);
		}

		if (parameter == 6) {
			deleteList(&head);
			printf("Lista a fost eliminata din memorie");
		}

		if (parameter == 7) {
			sortList(&head);
			printList(head);
		}

		if (parameter == 8) {
			reversePrint(head);
		}
	}
	return 0;
}