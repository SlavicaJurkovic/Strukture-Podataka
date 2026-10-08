#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char ime[30];
    char prezime[30];
    int br_bodova;
}_student;

int prebroji(){

    FILE *fp;
    int brojac = 0;
    char ime[30], prezime[30];
    int br_bodova;

    fp = fopen("studenti.txt", "r");

    while(fscanf(fp, "%s %s %d", ime, prezime, &br_bodova) == 3){
        brojac++;
    }

    fclose(fp);

    return brojac;
}

void ucitaj(_student *studenti, int brojac){

    FILE *fp;

    fp = fopen("studenti.txt", "r");

    for(int i=0; i<brojac; i++){
        fscanf(fp, "%s %s %d",
               studenti[i].ime,
               studenti[i].prezime,
               &studenti[i].br_bodova);
    }

    fclose(fp);
}

void ispis(_student *studenti, int brojac, int max_br_bodova){
    
    for(int i=0; i<brojac; i++){
        printf("%s\t%s\t%d\t%.2f\n",
               studenti[i].ime,
               studenti[i].prezime,
               studenti[i].br_bodova,
               studenti[i].br_bodova / (float)max_br_bodova * 100);
    }
}

int main(){

    _student *studenti;
    int brojac;
    int max_br_bodova = 100;

    brojac = prebroji();

    studenti = malloc(brojac*sizeof(_student));

    ucitaj(studenti, brojac);

    ispis(studenti, brojac, max_br_bodova);

    free(studenti);

    return 0;
}

