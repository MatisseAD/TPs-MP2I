/**********************************/
/* Chapitre 11 - Listes & Tableaux*/
/*   TP 2 - Tableaux dynamiques   */
/**********************************/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct int_array {
    int *data;
    int len;
};

typedef struct int_array int_array;

//1

int array_get(int_array *t, int i) {
    assert(i >= 0 && i < t->len);
    return t->data[i];
}

//2

void array_set(int_array *t, int i, int x) {
    assert(i >= 0 && i < t->len);
    t->data[i] = x;
}

//3

void array_delete(int_array *t) {
    free(t->data);
    free(t);
}

/**********Réalisation naïve**********/

struct int_dynarray {
    int len;
    int capacity;
    int *data;
};

typedef struct int_dynarray int_dynarray;

//1

int length(int_dynarray *t) {
    return t->len;
}

//2

int_dynarray *make_empty(void) {
    int_dynarray *t = malloc(sizeof(int_dynarray));
    t->data = NULL;
    t->capacity = 0;
    t->len = 0;
    return t;
}

//3

int get(int_dynarray *t, int i) {
    assert(i >= 0 && i < t->len);
    return t->data[i];
}

int set(int_dynarray *t, int i, int x) {
    assert(i >= 0 && i < t->len);
    t->data[i] = x;
}

//4

int pop(int_dynarray *t) {
    assert(t->len > 0);
    t->len = t->len - 1;
    return t->data[t->len];
}

//5

void resize(int_dynarray *t, int new_capacity) {
    int *newdata = malloc(new_capacity * sizeof(int));
    for (int i = 0; i < t->len; i++) {
        newdata[i] = t->data[i];
    }
    t->capacity = new_capacity;
    free(t->data);
    t->data = newdata;
}

//6

void push(int_dynarray *t, int x) {
    if (t->len < t->capacity) {
        t->data[t->len] = x;
        t->len++;
    } else if (t->len == t->capacity) {
        resize(t, t->capacity + 1);
        t->data[t->len] = x;
        t->len++;
    }
}

//7

void delete (int_dynarray *t) {
    free(t->data);
    free(t);
}

/**********Réalisation efficace**********/

//1

void resize(int_dynarray *t, int new_capacity) {
    int *newdata = malloc(new_capacity * sizeof(int));
    for (int i = 0; i < t->len; i++) {
        newdata[i] = t->data[i];
    }
    t->capacity = new_capacity;
    free(t->data);
    t->data = newdata;
}

void push(int_dynarray *t, int x) {
    if (t->len < t->capacity) {
        t->data[t->len] = x;
        t->len++;
    } else if (t->len == t->capacity) {
        int new_capacity = (t->capacity > 0 ? t->capacity * 2 : 1);
        resize(t, new_capacity);
        t->data[t->len] = x;
        t->len++;
    }
}

void insert_at(int_dynarray *t, int i, int x) {

    int n = length(t);

    assert(0 <= i && i <= n);
    push(t,x);

    for (int j = n;  j>i; j--) {
        set(t, j, get(t, j-1));
    }

    set(t,i,x);

}

/*

Complexité de "insert_at" :



*/

int extract_at(int_dynarray *t, int i) {
    int n = length(t);

    assert(0 <= i && i < n);

    int f = get(t,i);

    for (int j=i; j<n-1; j++) {
        set(t, j, get(t, j+1));
    }
    
    pop(t);
    
    return f;
} 

/**
 * Complexité de la fonction extract_at ou C est le nombre de set et m la taille du tableau et i le rang de la valeur à détruire
 * 
 * Si i = n-1, alors nous sommes dans le meilleur des cas -> C(i) = m - i
 * 
 */

int postion(int_dynarray *t, int x) {

    int i = 0;
    int n = length(t);

    while (i != n && get(t, i) <= x) {
        i++;
    }

    return i;

}

int_dynarray *insertion_sort(int_dynarray *t) {
    int length_t = length(t);
    int_dynarray *out = make_empty();

    for (int i=0; i < length_t; i++) {
        positon(out, get(t,i));
        insert_at(out, positon, get(t,i));
    }

    return out;
}

/*

Dans le pire des cas, le tableau est trié dans l'ordre "inverse"

Alors, il faut à chaque fois décaler tout les éléments du tableau vers la droite.

Alors, on effectue une boucle qui fait n appels à postion.
Or dans le pire des cas, il faut à chaque fois parcour les éléments de 0 à k, où k est le k-ième élément à trié. Donc pour postion on aura une complexité quadratique C(n) = thêta(n²). (Boucle while)

Cependant, la fonction insert_sort n'aura pas à décaler les éléments vers la droite car le k-ième élément à trié est le plus grand.

Ainsi, la complexité de insert_at dans le pire des cas est C(n) = thêta(n²) (Boucle for)

Dans le meilleur des cas, le tableau est déjà trié.
Alors, il faut à chaque fois insérer l'élément à la fin du tableau.
Donc, on effectue une boucle qui fait n appels à postion.
Or dans le meilleur des cas, il faut à chaque fois faire un seul test dans postion.
Donc la complexité de postion dans le meilleur des cas est C(n) = thêta(n) (Boucle for)


*/


void main(void) {



} 