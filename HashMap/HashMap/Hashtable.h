<<<<<<< HEAD
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
=======
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
>>>>>>> 73b1af65c80b4b8ad8f0b536e9fa91f584fc2095
