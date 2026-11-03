#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly{
    int coeff;
    int pow;
    Position next;
} Polynom;

int insertSorted(Position P, int coeff, int pow);
int readFile(char* ime, Position P1, Position P2);
int ispis(char* ime, Position P);
int suma(Position P1, Position P2, Position S);
int produkt(Position P1, Position P2, Position P);
int BrisiSve(Position P);


int main()
{
    Polynom HeadF ={ 0, 0, NULL};
    Polynom HeadS ={ 0, 0, NULL};
    Polynom HeadZ ={ 0, 0, NULL};
    Polynom HeadP ={ 0, 0, NULL};

    Position F=&HeadF;
    Position S=&HeadS;
    Position Z=&HeadZ;
    Position P=&HeadP;

    if (!readFile("polinomi.txt", F, S)) {
        printf("Greska pri citanju datoteke!\n");
        return 1;
    }

    printf("Prvi polinom:\n");
    ispis("polinomi.txt", F);

    printf("\nDrugi polinom:\n");
    ispis("polinomi.txt", S);

    suma(F, S, Z);

    printf("\nZbroj polinoma:\n");
    ispis("Zbroj", Z);

    produkt(F, S, P);

    printf("\nProdukt polinoma:\n");
    ispis("Produkt", P);

    BrisiSve(F);
    BrisiSve(S);
    BrisiSve(Z);
    BrisiSve(P);

    return 0;
}

int insertSorted(Position P, int coeff, int pow)
{
    Position newPoly;
    Position temp;

    while (P->next != NULL && P->next->pow > pow) {
        P = P->next;
    }

    if (P->next != NULL && P->next->pow == pow) {
        P->next->coeff += coeff;

        if (P->next->coeff == 0) {
            temp = P->next;
            P->next = temp->next;
            free(temp);
        }

        return 1;
    }

    if (coeff == 0) {
        return 1;
    }

    newPoly = (Position)malloc(sizeof(Polynom));

    if (newPoly == NULL) {
        return 0;
    }

    newPoly->coeff=coeff;
    newPoly->pow=pow;

    newPoly->next=P->next;
    P->next = newPoly;

    return 1;
}


int readFile(char* ime, Position P1, Position P2)
{
    FILE* fp;
    int n, coeff, pow, i;

    fp=fopen(ime, "r");

    if(fp == NULL){
        return 0;
    }

    //ucitavanje prvog polinoma 

    if (fscanf(fp, "%d", &n) != 1) {
        fclose(fp);
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(fp, "%d %d", &coeff, &pow) != 2) {
            fclose(fp);
            return 0;
        }

        if (!insertSorted(P1, coeff, pow)) {
            fclose(fp);
            return 0;
        }
    }

    //ucitavanje drugog polinoma

    if (fscanf(fp,"%d",&n) != 1) {
        fclose(fp);
        return 0;
    }

    for (i = 0;i<n;i++) {
        if (fscanf(fp, "%d %d",&coeff,&pow)!=2){
            fclose(fp);
            return 0;
        }

        if (!insertSorted(P2, coeff, pow)) {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    return 1;
}


int ispis(char* ime, Position P)
{
    Position temp = P->next;

    printf("%s: ", ime);

    if (temp == NULL) {
        printf("0\n");
        return 1;
    }

    while (temp != NULL){
        if (temp->coeff > 0 && temp != P->next) {
            printf(" + ");
        }

        if (temp->coeff < 0){
            printf(" - ");
        }

        if (temp->pow == 0){
            printf("%d", abs(temp->coeff));
        }
        else if (temp->pow == 1){
            printf("%dx", abs(temp->coeff));
        }
        else {
            printf("%dx^%d", abs(temp->coeff), temp->pow);
        }

        temp = temp->next;
    }

    printf("\n");

    return 1;
}


int suma(Position P1, Position P2, Position S)
{
    Position temp1 = P1->next;
    Position temp2 = P2->next;

    while (temp1 != NULL && temp2 != NULL){

        if (temp1->pow == temp2->pow){
            if (!insertSorted(S, temp1->coeff + temp2->coeff, temp1->pow)) {
                return 0;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->pow > temp2->pow){
            if (!insertSorted(S, temp1->coeff, temp1->pow)){
                return 0;
            }

            temp1 = temp1->next;
        }
        else {
            if (!insertSorted(S, temp2->coeff, temp2->pow)){
                return 0;
            }

            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL){
        if (!insertSorted(S, temp1->coeff, temp1->pow)){
            return 0;
        }

        temp1 = temp1->next;
    }

    while (temp2 != NULL){
        if (!insertSorted(S, temp2->coeff, temp2->pow)){
            return 0;
        }

        temp2 = temp2->next;
    }

    return 1;
}


int produkt(Position P1, Position P2, Position P)
{
    Position temp1=P1->next;
    Position temp2;

    while (temp1!=NULL){
        temp2 = P2->next;

        while (temp2!=NULL){
            if (!insertSorted(P,temp1->coeff * temp2->coeff,
                temp1->pow + temp2->pow)) {
                return 0;
            }

            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }

    return 1;
}


int BrisiSve(Position P)
{
    Position temp;

    while (P->next != NULL) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }

    return 1;
}