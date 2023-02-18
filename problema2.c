#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary_entry{
    char *word;
    int priority;
}term;

void adaugare(term *a, char *cuv, int n) {
    a[n].word = malloc(21 * sizeof(char));
    strcpy(a[n].word, cuv);
    a[n].word[strlen(cuv)] = '\0';
    a[n].priority = 1;
    a[n].word = realloc(a[n].word, (strlen(a[n].word) + 1) * sizeof(char));
}
/*functie care adauga un nou cuvant in dictionar*/

int is_in_d(term *a, char *b, int n) {
    int i;
    for(i = 0; i < n; i++) {
        if(strcmp(a[i].word, b) == 0) {
            return i;
        }
    }
    return -1;
}
/*functie care verifica daca un cuvant se afla in dictionar
, caz in care se returneaza pozitia sau -1 in caz contrar*/

void transformare(term **a, char *x, int *n) {
    if(strcmp(x, ",") == 0 || strcmp(x, "?") == 0 || strcmp(x, "!") == 0
    || strcmp(x, ".") == 0 || strcmp(x, ":") == 0) {
        printf("%s", x);
    /*se verifica daca entitatea citita este un semn de punctuatie, caz in
    care se afiseaza si se trece mai departe*/
    } else {
        if(x[strlen(x) - 1] == '*') {
            x[strlen(x) - 1] = '\0';
            /*se verifica daca cuvantul citit are caracterul '*' la final
            , caz in care se elimina ultimul caracter*/
            if(is_in_d(*a, x, *n) != -1) {
                int j = is_in_d(*a, x, *n);
                (*a)[j].priority++;
                printf("%s", (*a)[j].word);
                /*daca cuvantul este gasit in dictionar i se creste
                prioritatea si este afisat*/
            } else {
                *a = realloc(*a, ((*n) + 1) * sizeof(term));
                adaugare(*a, x, *n);
                ++(*n);
                printf("%s", x);
                /*daca cuvantul nu este gasit este adaugat in dictionar
                si afisat*/
            }    
         } else {
            /*se considera cazul in care cuvantul introdus se gaseste sigur
            in dictionar si va fi inlocuit*/
             int maxi = -1, jmaxi = -1;
             int j;
             for(j = 0; j < (*n); j++) {
                 char aux[100];
                 strncpy(aux, (*a)[j].word, strlen(x));
                 /*pentru cuvantul "x" se verifica cu fiecare cuvant din 
                 dictionar daca se gaseste la inceputul acestora*/
                 aux[strlen(x)] = '\0';
                 if(strcmp(aux, x) == 0){
                     if((*a)[j].priority > maxi){
                         maxi = (*a)[j].priority;
                         jmaxi = j;
                         /*in caz afirmativ, se cauta cuvantul din dictionar
                         potrivit cu cuvantul "x" de prioritate maxima*/
                     } else {
                         if((*a)[j].priority == maxi) {
                             if(strcmp((*a)[jmaxi].word, (*a)[j].word) > 0) {
                                 jmaxi = j;
                             }
                         }
                    /*in cazul in care se gasesc doua sau mai multe cuvinte
                    cu aceeasi prioritate, se va inlocui cu cel mai mic din
                    punct de vedere lexicografic*/
                     }
                 }
             }
             if(maxi != -1) {
                 printf("%s", (*a)[jmaxi].word);
                 (*a)[jmaxi].priority++;
                 /*se afiseaza cuvantul gasit*/
             } else {
                 *a = realloc(*a, ((*n) + 1) * sizeof(term));
                 adaugare(*a, x, *n);
                 ++(*n);
                 printf("%s", x);
            /*se considera cazul in care cuvantul nu a fost asociat niciunui
            cuvant din dictionar, fiind adaugat in dictionar si afisat*/
             }
         }
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    getchar();
    term *a = malloc(n * sizeof(term));
    int i;
    for(i = 0; i < n; i++) {
        a[i].word = malloc(21 * sizeof(char));
        a[i].priority = 0;
    }
    for(i = 0; i < n; i++) {
        scanf("%s", a[i].word);
    }
    for(i = 0; i < n; i++) {
        a[i].word = realloc(a[i].word, (strlen(a[i].word) + 1) * sizeof(char));
    }
    /*se citeste fiecare cuvant din dictionar si se realoca cu memoria
    necesara*/
    scanf("%d", &m);
    i = 0;
    char *x;
    x = malloc(21 * sizeof(char));
    while(i < m) {
        scanf("%s", x);
        transformare(&a, x, &n);
        printf(" ");
        i++;
        /*se citeste fiecare cuvant si se tranforma in functie de caz*/
    }

    free(a);
    free(x);

    return 0;

}
