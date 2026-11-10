#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack* Position;

typedef struct Stack {
    int broj;
    Position next;
} Stack;

int Push(Position head, int broj);
int Pop(Position head, char operacija);
int pretvoriBroj(char* znak, int* broj);
int readFile(char* ime, Position head);
int BrisiSve(Position head);

int main() {

    Stack Head = {
        .broj = 0,
        .next = NULL
    };

    Position p = &Head;

    if (!readFile("izraz.txt", p)) {
        printf("Greska pri citanju ili racunanju izraza!\n");
        BrisiSve(p);
        return 1;
    }

    printf("Rezultat izraza je:%d\n", p->next->broj);

    BrisiSve(p);

    return 0;
}

int Push(Position head, int broj) {

    Position newP = NULL;

    newP = (Position)malloc(sizeof(Stack));

    if (newP == NULL)
        return 0;

    newP->broj = broj;
    newP->next = head->next;

    head->next = newP;

    return 1;
}

int Pop(Position head, char operacija) {

    Position q, p;
    int rezultat;

    if (head->next == NULL || head->next->next == NULL)
        return 0;

    q = head->next;
    p = q->next;

    if (operacija == '+')
        rezultat = p->broj + q->broj;
    else if (operacija == '-')
        rezultat = p->broj - q->broj;
    else if (operacija == '*')
        rezultat = p->broj * q->broj;
    else if (operacija == '/') {

        if (q->broj == 0)
            return 0;

        rezultat = p->broj / q->broj;
    }
    else
        return 0;

    head->next = p->next;

    free(q);
    free(p);

    return Push(head, rezultat);
}

int pretvoriBroj(char* znak, int* broj) {

    int i = 0;
    int predznak = 1;
    int vrijednost = 0;

    if (znak[i] == '-') {
        predznak = -1;
        i++;
    }

    if (znak[i] == '\0')
        return 0;

    while (znak[i] != '\0') {

        if (znak[i] < '0' || znak[i]>'9')
            return 0;

        vrijednost = vrijednost * 10 + znak[i] - '0';
        i++;
    }

    *broj = vrijednost * predznak;

    return 1;
}

int readFile(char* ime, Position head) {

    FILE* fp;
    char znak[50];
    int broj;

    fp = fopen(ime, "r");

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%s", znak) == 1) {

        if (strlen(znak) == 1 && (znak[0] == '+' || znak[0] == '-' || znak[0] == '*' || znak[0] == '/')) {

            if (!Pop(head, znak[0])) {
                fclose(fp);
                return 0;
            }
        }
        else if (pretvoriBroj(znak, &broj)) {

            if (!Push(head, broj)) {
                fclose(fp);
                return 0;
            }
        }
        else {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    if (head->next == NULL || head->next->next != NULL)
        return 0;

    return 1;
}

int BrisiSve(Position head) {

    Position temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 1;
}
