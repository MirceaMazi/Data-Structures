#pragma once

typedef struct Item {   //Structura unui element din tabela
    char* key;
    char* value;
};

typedef struct Hashtable {
    int size;   //Marimea tabelei
    int count;  //Variabila asta e folosita pentru a stii cat de multe elemente sunt deja in tabela
    struct Item** items;    //Folosim asta pentru a implementa chaining-ul in caz de coliziune
};
