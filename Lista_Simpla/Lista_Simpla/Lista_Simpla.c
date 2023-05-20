#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#pragma warning(disable:4996)

typedef struct node {
    int val;
    struct node* next;
};

void print_list(struct node* head) {
    struct node* current = head;

    printf("\nLista: ");

    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }

    printf("\n");
}

void push(struct node* head, int val) {
    struct node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(struct node));
    current->next->val = val;
    current->next->next = NULL;
}

void push_beginning(struct node** head, int val) {
    struct node* newNode = malloc(sizeof(struct node));

    newNode->val = val;
    newNode->next = *head;
    *head = newNode;
}

void pop(struct node** head) {
    struct node* nextNode = malloc(sizeof(struct node));

    if (*head == NULL) {
        return;
    }

    nextNode = (*head)->next;
    free(*head);
    *head = nextNode;

}

void pop_last(struct node* head) {
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

    while (i < position-1) {
        if (current->next == NULL) {
            printf("Unul din nodurile parcurse pana a ajunge la pozitia ceruta nu are un pointer next");
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
    free(temporary);

}

void deleteList(struct node** head) {
    struct node* current = *head;
    
    if (*head == NULL) {
        return;
    }

    do{
        current = (*head)->next;
        free(*head);
        *head = current;
    } while (current->next != NULL);
    
    current = (*head)->next;
    free(*head);
    *head = current;
}

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
//Aici avem si o varianta foarte analog a unui meniu, nu l-ai facut ca sa arate frumos sau sa fie bine facut,
//l-ai facut ca sa iti vina mai usor sa repeti pentru test. 
int main()
{   
    struct node* head = NULL;
    head = malloc(sizeof(struct node));

    if (head == NULL) {
        return 1;
    }

    head->val = 3;
    head->next = malloc(sizeof(struct node));
    head->next->val = 2;
    head->next->next = malloc(sizeof(struct node));
    head->next->next->val = 1;
    head->next->next->next = NULL;
    
    printf("Aveti lista cu valorile:\n");
    print_list(head);
    printf("\n1)Adauga un element la final");
    printf("\n2)Adauga un element la inceput");
    printf("\n3)Sterge primul element");
    printf("\n4)Sterge ultimul element");
    printf("\n5)Elimina un element de la o pozitie data");
    printf("\n6)Sterge intreaga lista");
    printf("\n7)Sorteaza elementele listei");
    printf("\n0)Iesi din program");

    bool done = 0;
    
    while (!done) {
        printf("\nCe operatie doritia sa realizati?\n");

        int parameter = -1;
        int element = -1;
        
        scanf("%d", & parameter);
        
        if (parameter == 0) {
            printf("Lista finala:");
            print_list(head);
            done = 1;
        }
        
        if (parameter == 1) {
            printf("Ce element doriti sa adaugati?");
            scanf("%d", &element);
            push(head, element);
            print_list(head);
        }
        
        if (parameter == 2) {
            printf("Ce element doriti sa adaugati?");
            scanf("%d", &element);
            push_beginning(&head, element);
            print_list(head);
        }

        if (parameter == 3) {
            pop(&head);
            print_list(head);
        }

        if (parameter == 4) {
            pop_last(head);
            print_list(head);
        }

        if (parameter == 5) {
            printf("Ce element doriti sa eliminati?");
            scanf("%d", &element);
            removeNode(&head, element);
            print_list(head);
        }

        if(parameter == 6) {
            deleteList(&head);
            printf("Lista a fost eliminata din memorie");
        }

        if (parameter == 7) {
            sortList(&head);
            print_list(head);
        }
    }
}

