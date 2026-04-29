#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int nbPersonne = 30800;

bool checkPalyndrome(char *c) {
    int i = 0;
    int j = strlen(c) - 1;

    while (i != j) {
        if (c[i] != c[j]) {
            break;
        }
        i++;
        j--;
    }

    return i == j;
}

int fx(int i) {
    return i * i;
}

int charCounter(char *c) {
    int cpt = 0;
    while (c[cpt] != '\0') {
        cpt++;
    }

    return cpt;
}

bool hasTheLetter(char l, char *c) {
    int i = strlen(c) - 1;
    bool ans = false;

    for (i; i >= 0; i--) {
        if (l == c[i]) {
            ans = true;
        }
    }

    return ans;
}

bool anagrammes(char *c1, char *c2) {
    if (strlen(c1) != strlen(c2)) return false;

    int count[256] = {0};

    for (int i = 0; c1[i] != '\0'; i++) count[(unsigned char) c1[i]]++;
    for (int i = 0; c2[i] != '\0'; i++) count[(unsigned char) c2[i]]--;

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}

bool samePrenom(char *c1, char *c2) {
    int i = 0;

    if (strlen(c1) != strlen(c2)) {
        return false;
    }

    while (c1[i] == c2[i] && c1[i] != '\0' && c2[i] != '\0') {
        i++;
    }

    return i == strlen(c1);
}

int main(void) {
    // Q1, Q2
    FILE *f = fopen("fichiervide.txt", "w");
    fprintf(f, "Première ligne \n");
    fprintf(f, "Deuxième ligne \n");
    fclose(f);

    f = fopen("fichiervide.txt", "r");

    char *c = malloc(64 * sizeof(char));
    while (true) {
        if (fscanf(f, "%c", c) != 1) break;
        printf("%c", *c);
    }

    fclose(f);

    f = fopen("fichiervide.txt", "a");
    fprintf(f, "Troisième ligne");
    fclose(f);

    // Q5

    f = fopen("plot.txt", "w");

    for (int i = 0; i <= 10000; i++) {
        fprintf(f, "%d | %d \n", fx(i), i);
    }

    fclose(f);

    // Q6

    /**FILE *fTarget = fopen(argv[2], "w");
    f = fopen(argv[1], "r");

    while (true) {
        if (fscanf(f, "%c", &c) != 1) break;
        fprintf(fTarget, "%c", c);
    }

    fclose(f);
    fclose(fTarget);*/

    // Prénoms français

    // Q1

    f = fopen("prenoms.txt", "r");

    int cpt = 0;

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;
        cpt++;
    }

    printf("\n Nombre de prenoms : %d \n", cpt);
    cpt = 0;
    rewind(f);

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (c[0] == 'e') {
            cpt++;
        }
    }

    printf("\n Nombre de personnes commençant par la lettre e : %d \n", cpt);

    cpt = 0;
    rewind(f);

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (cpt < charCounter(c)) {
            cpt = charCounter(c);
            cpt++;
        }
    }

    printf("\n Le prénom le plus long a pour nombre : %d \n", cpt);
    rewind(f);

    cpt = 0;
    bool sameBlaze = false;

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (samePrenom(c, "abdel")) {
            sameBlaze = true;
        }
    }

    if (sameBlaze) {
        printf("\n Oui, il y a ce prénom \n");
    } else {
        printf("Non, il n'y a pas ce prénom \n");
    }

    rewind(f);
    cpt = 0;

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (hasTheLetter('e', c)) {
            cpt++;
        }
    }

    double average = ((double) cpt / 30800) * 100;
    cpt = (int) average;

    printf("La proportion de personne comportant la lettre 'e' est de : %d\n", cpt);

    rewind(f);
    cpt = 0;

    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (checkPalyndrome(c)) {
            printf(c);
            printf(" | ");
        }
    }

    rewind(f);
    cpt = 0;
    printf("\n");

    // ANAGRAMMES

    printf("\n Début des anagrammes");


    while (true) {
        if (fscanf(f, "%s", c) != 1) break;

        if (anagrammes(c, "ethan")) {
            printf(c);
            printf(" | ");
        }
    }


    fclose(f);

    free(c);


    return 0;
}