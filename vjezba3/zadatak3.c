
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

int insertAfterPerson(char* ime, char* prezime, int god, char* trazenoPrezime, Position head);
int insertBeforePerson(char* ime, char* prezime, int god, char* trazenoPrezime, Position head);
int sort(Position P);
int writeFile(Position head);
int readFile(Position head);
int BrisiSve(Position head);

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
    char trazenoPrezime[50];
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
        BrisiSve(p);
        return 1;
    }


    printf("\nLista nakon dodavanja na kraj:\n");
    printlist(p->next);

    // a) Dodavanje iza odredene osobe
    printf("\nUnesite ime, prezime i godinu rodenja nove osobe:\n");
    scanf("%s %s %d", ime, prezime, &godina);

    printf("Unesite prezime osobe iza koje zelite dodati novu osobu:\n");
    scanf("%s", trazenoPrezime);

    if (insertAfterPerson(ime, prezime, godina, trazenoPrezime, p))
        printf("Osoba je dodana iza trazene osobe.\n");
    else
        printf("Osoba nije dodana.\n");

    // b) Dodavanje ispred odredene osobe
    printf("\nUnesite ime, prezime i godinu rodenja nove osobe:\n");
    scanf("%s %s %d", ime, prezime, &godina);

    printf("Unesite prezime osobe ispred koje zelite dodati novu osobu:\n");
    scanf("%s", trazenoPrezime);

    if (insertBeforePerson(ime, prezime, godina, trazenoPrezime, p))
        printf("Osoba je dodana ispred trazene osobe.\n");
    else
        printf("Osoba nije dodana.\n");

    printf("\nLista nakon dodavanja osoba:\n");
    printlist(p->next);

    // c) Sortiranje po prezimenima
    if (sort(p)) {
        printf("\nSortirana lista:\n");
        printlist(p->next);
    }
    else
        printf("\nLista je prazna.\n");

    // d) Upis liste u datoteku
    if (writeFile(p))
        printf("\nLista je upisana u datoteku osobe.txt.\n");
    else
        printf("\nGreska pri otvaranju datoteke.\n");

    // e) Citanje liste iz datoteke
    if (readFile(p)) {
        printf("\nLista procitana iz datoteke:\n");
        printlist(p->next);
    }
    else
        printf("\nGreska pri citanju datoteke.\n");

    // Trazenje osobe po prezimenu
    printf("\nUnesite prezime koje trazite:\n");
    scanf("%s", prezime);

    pronadena = findlastName(prezime, p);

    if (pronadena != NULL)
        printf("%s %s %d\n", pronadena->ime,
            pronadena->prezime, pronadena->godina);
    else
        printf("Osoba nije pronadena.\n");

    // Brisanje osobe po prezimenu
    printf("\nUnesite prezime osobe koju zelite obrisati:\n");
    scanf("%s", prezime);

    if (deletePerson(prezime, p))
        printf("Osoba je obrisana.\n");
    else
        printf("Osoba nije pronadena.\n");

    printf("\nKonacna lista:\n");
    printlist(p->next);

    // Oslobadanje memorije
    BrisiSve(p);

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

// a) Dodavanje iza odredene osobe
int insertAfterPerson(char* ime, char* prezime, int god,
    char* trazenoPrezime, Position head) {

    Position pronadena = findlastName(trazenoPrezime, head);
    Position newPerson = NULL;

    if (pronadena == NULL)
        return 0;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = god;
    newPerson->next = NULL;

    return insertAfter(pronadena, newPerson);
}

// b) Dodavanje ispred odredene osobe
int insertBeforePerson(char* ime, char* prezime, int god,
    char* trazenoPrezime, Position head) {

    Position pronadena = findlastName(trazenoPrezime, head);
    Position prev = head;
    Position newPerson = NULL;

    if (pronadena == NULL)
        return 0;

    while (prev->next != pronadena)
        prev = prev->next;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = god;

    newPerson->next = pronadena;
    prev->next = newPerson;

    return 1;
}

// c) Sortiranje po prezimenima
int sort(Position P) {

    Position j, prev_j, temp, end;

    if (P->next == NULL)
        return 0;

    end = NULL;

    while (P->next != end) {

        prev_j = P;
        j = P->next;

        while (j->next != end) {

            if (strcmp(j->prezime, j->next->prezime) > 0) {

                temp = j->next;
                prev_j->next = temp;
                j->next = temp->next;
                temp->next = j;

                j = temp;
            }

            prev_j = j;
            j = j->next;
        }

        end = j;
    }

    return 1;
}

// d) Upis liste u datoteku
int writeFile(Position head) {

    FILE* fp;
    Position p;

    fp = fopen("osobe.txt", "w");

    if (fp == NULL)
        return 0;

    for (p = head->next; p != NULL; p = p->next) {
        fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->godina);
    }

    fclose(fp);

    return 1;
}

// e) Citanje liste iz datoteke
int readFile(Position head) {

    FILE* fp;
    char ime[50];
    char prezime[50];
    int god;

    fp = fopen("osobe.txt", "r");

    if (fp == NULL)
        return 0;

    BrisiSve(head);

    while (fscanf(fp, "%s %s %d", ime, prezime, &god) == 3) {

        if (!insertEnd(ime, prezime, god, head)) {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    return 1;
}

// Brisanje svih elemenata liste
int BrisiSve(Position head) {

    Position temp = NULL;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 1;
}
