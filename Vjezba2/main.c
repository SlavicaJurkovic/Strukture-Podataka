#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
    char ime[50];
    char prezime[50];
    int godina;
    Position next;
} Person;

int insertAfter(Position p, Position newPerson);
int insertBegin(char* ime, char* prezime, int god, Position head);
int insertEnd(char* ime, char* prezime, int god, Position head);
int printlist(Position p);
Position findlastName(char* prezime, Position p);
int deletePerson(char* prezime, Position head);

int main() {

    Person Head = {
        .ime = { 0 },
        .prezime = { 0 },
        .godina = 0,
        .next = NULL
    };

    Position p = &Head;
    Position pronadena;

    char ime[50];
    char prezime[50];
    int godina;

    // a) Dodavanje na pocetak
    printf("Unesite ime, prezime i godinu rodenja:\n");
    scanf("%s %s %d", ime, prezime, &godina);

    if (!insertBegin(ime, prezime, godina, p)) {
        printf("Greska pri alokaciji memorije.\n");
        return 1;
    }

    // b) Ispis liste
    printf("\nLista:\n");
    printlist(p->next);

    // c) Dodavanje na kraj
    printf("\nUnesite ime, prezime i godinu rodenja:\n");
    scanf("%s %s %d", ime, prezime, &godina);

    if (!insertEnd(ime, prezime, godina, p)) {
        printf("Greska pri alokaciji memorije.\n");

        while (p->next != NULL) {
            Position temp = p->next;
            p->next = temp->next;
            free(temp);
        }

        return 1;
    }

    printf("\nLista nakon dodavanja na kraj:\n");
    printlist(p->next);

    // d) Trazenje osobe po prezimenu
    printf("\nUnesite prezime koje trazite:\n");
    scanf("%s", prezime);

    pronadena = findlastName(prezime, p);

    if (pronadena != NULL)
        printf("%s %s %d\n", pronadena->ime,
            pronadena->prezime, pronadena->godina);
    else
        printf("Osoba nije pronadena.\n");

    // e) Brisanje osobe po prezimenu
    printf("\nUnesite prezime osobe koju zelite obrisati:\n");
    scanf("%s", prezime);

    if (deletePerson(prezime, p))
        printf("Osoba je obrisana.\n");
    else
        printf("Osoba nije pronadena.\n");

    printf("\nKonacna lista:\n");
    printlist(p->next);

    while (p->next != NULL) {
        Position temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    return 0;
}

int insertAfter(Position p, Position newPerson) {

    newPerson->next = p->next;
    p->next = newPerson;

    return 1;
}

int insertBegin(char* ime, char* prezime, int god, Position head) {

    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = god;
    newPerson->next = NULL;

    return insertAfter(head, newPerson);
}

int insertEnd(char* ime, char* prezime, int god, Position head) {

    Position newPerson = NULL;
    Position p = head;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = god;
    newPerson->next = NULL;

    while (p->next != NULL)
        p = p->next;

    return insertAfter(p, newPerson);
}

int printlist(Position p) {

    if (p == NULL) {
        printf("Lista je prazna.\n");
        return 1;
    }

    while (p != NULL) {
        printf("%s %s %d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }

    return 1;
}

Position findlastName(char* prezime, Position p) {

    for (p = p->next; p != NULL; p = p->next) {
        if (strcmp(p->prezime, prezime) == 0)
            return p;
    }

    return NULL;
}

int deletePerson(char* prezime, Position head) {

    Position prev = head;
    Position curr = findlastName(prezime, head);

    if (curr == NULL)
        return 0;

    while (prev->next != curr)
        prev = prev->next;

    prev->next = curr->next;
    free(curr);

    return 1;
}
