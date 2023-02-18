#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inmat(char **a, char **s, int n) {
    int i, j, k = 0;
    for(i = 1; i < 2 * n; i = i + 2) {
        for(j = 0 ; j < strlen(s[(i - 1) / 2]); j++) {
            a[i][j] = ' ';
        }
    }
    /*se initializeaza matricea cu spatii*/
    for(i = 0; i < n; i++) {
        for(j = 0; j < strlen(s[i]); j++) {
            a[k][j] = s[i][j];
        }
        k = k + 2;
    }
    /*se introduce textul pe liniile pare ale matricei, urmand ca pe cele 
    impare sa se sublinieze cuvintele cheie*/
}

void subliniere(char **a, int n) {
    char dictionar[11][10] = {"for" ,"from", "in", "is", "unit", "or", "while",
    "int", "float", "double", "string"};
    /*se initializeaza dictionarul doar cu acele cuvinte care sunt
    considerate cheie singure*/
    int i;
    char *p;
    char aux[102];
    for(i = 0; i < 2 * n; i = i + 2) {
        strcpy(aux, a[i]);
        p = strtok(aux, " ");
        int j;
        long int k;
        while(p) {
            for(j = 0; j < 11; j++) {
                if(strcmp(p, dictionar[j]) == 0) {
                    break;
                }
            }
            /*se verifica pentru fiecare cuvant daca se gaseste in
            dictionar*/
            char *man = p;
            if(j != 11) {
                p = strtok(NULL, " ");
                /*in cazul in care a fost gasit in dictionar se cauta
                daca urmatorul cuvant formeaza o pereche cheie cu 
                cuvantul initial*/
                if(p) {
                    if(strcmp(p, "each") == 0 && strcmp(man, "for") == 0) {
                        for(k = man - aux; k < strlen(p) + p - aux; k++) {
                            a[i + 1][k] = '_';
                        }
                        p = strtok(NULL, " ");
                        /*daca cele doua cuvinte sunt "for" si "each" se
                        subliniaza si se trece la urmatoruk cuvant*/
                    } else {
                        if(strcmp(p, "a") == 0 && strcmp(man, "is") == 0) {
                            for(k = man - aux; k < strlen(p) + p - aux; k++) {
                                a[i + 1][k] = '_';
                            }
                            p = strtok(NULL, " ");
                            /*daca cele doua cuvinte sunt "is" si "a" se
                        subliniaza si se trece la urmatoruk cuvant*/
                        } else {
                            for(k = man - aux; k < strlen(man) + man - aux;
                            k++) {
                                a[i + 1][k] = '_';
                            }
                            /*in cazul in care urmatorul cuvant nu formeaza
                            o pereche cheie se subliniaza cuvantul initial fara
                            a trece mai departe*/
                        }
                    }
                } else {
                    for(k = man - aux; k < strlen(man) + man - aux; k++) {
                        a[i + 1][k] = '_';
                    }
                }
                /*in cazul in care urmatorul cuvant nu se gaseste
                in dictionar se subliniaza cel initial fara a trece
                mai departe*/
            } else {
                if(strcmp(man, "list") == 0) {
                    p = strtok(NULL, " ");
                    if(p) {
                        if(strcmp(p, "of") == 0) {
                            for(k = man - aux; k < strlen(p) + p - aux; k++) {
                                a[i + 1][k] = '_';
                            }
                            if(p) {
                                p = strtok(NULL ," ");
                            }
                        }
                    }
                    /*se verifica daca este intalnita perechea "list of",
                    deoarece aceasta nu a fost introdusa in dictionar*/
                } else {
                    if(strcmp(man, "first") == 0) {
                        p = strtok(NULL, " ");
                        if(p) {
                            if(strcmp(p, "of") == 0) {
                                for(k = man - aux; k < strlen(p) + p - aux;
                                k++) {
                                    a[i + 1][k] = '_';
                                }
                                if(p) {
                                    p = strtok(NULL, " ");
                                }
                            }
                        }
                        /*se verifica daca este intalnita perechea "first of",
                    deoarece aceasta nu a fost introdusa in dictionar*/
                    } else {
                        p = strtok(NULL, " ");
                    }
                }
            }
        }
    }
}
        

int main() {
    char **a, **s;
    int n, i;
    scanf("%d", &n);
    getchar();
    a = malloc(2 * n * sizeof(char *));
    for(i = 0; i < 2 * n; i++) {
        a[i] = malloc(102 * sizeof(char));
    }
    s = malloc(n * sizeof(char *));
    for(i = 0; i < n; i++) {
        s[i] = malloc(102 * sizeof(char));
    }
    for(i = 0 ; i < n; i++) {
        fgets(s[i], 102, stdin);
        s[i][strlen(s[i]) - 1] = '\0';
    }
    inmat(a, s, n);
    subliniere(a, n);
    for(i = 0; i < 2 * n; i++) {
        printf("%s\n", a[i]);
    }

    free(a);
    free(s);

    return 0;

}