#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t empty = 0;
const uint8_t occupied = 1;
typedef uint32_t T;

struct bucket {
    uint8_t statuts;
    T element;
};
typedef struct bucket bucket;

struct set {
    int p;
    bucket *a;
    uint64_t nb_empty;
};
typedef struct set set;

uint64_t power_of_2(int p) {
    return 1 << p;
}

uint64_t hash(T x, int p) {
    int power = power_of_2(p);
    return x % power;
}

/*

2. Écrire la fonction set *set_new(void) créant une table de hachage pour laquelle p = 1, dont toutes les cases
sont « libres ». Afin de pouvoir tester plus facilement nos prochaines fonctions, on écrira aussi une fonction
set *set_example(void) générant artificiellement une table de hachage pour laquelle p = 2 et contenant les
dates 1492, 1515 et 1939 comme décrit dans l’exemple plus haut.

*/

set *set_new(void) {
    set *ans = malloc(sizeof(set));
    ans->p = 1;
    ans->nb_empty = 1;
    ans->a = NULL;
    return ans;
}

set *set_example(void) {
    set *ans = malloc(sizeof(set));
    ans->p = 2;
    ans->nb_empty = 1;
    ans->a = malloc(sizeof(bucket) * 4);

    ans->a[0].statuts = occupied;
    ans->a[0].element = 1492;

    ans->a[1].statuts = occupied;
    ans->a[1].element = 1939;

    ans->a[2].statuts = empty;

    ans->a[3].statuts = occupied;
    ans->a[3].element = 1515;

    return ans;
}

/*

3. Écrire la fonction void set_delete(set *s) permettant de libérer la mémoire utilisée par s.

*/

void set_delete(set *s) {
    free(s->a);
    free(s);
}

/*

4. Écrire la fonction bool set_is_member(set *s, T x) permettant de déterminer si x est un élément de s. Afin
de proposer une implémentation efficace, on utilisera les opérations bit à bit pour les calculs modulo 2p. On
donnera de plus un argument justifiant la terminaison de cette fonction

*/

bool set_is_member(set *s, T x) {
    uint64_t i = hash(x, s->p);
    int ans = false;

    while (s->a[i].statuts != empty && !(ans)) {
        if (s->a[i].element == x) {
            ans = true;
        }
        i = (i + 1) % s->p;
    }

    return ans;
}

T set_get(set *s, uint64_t i) {

    return s->a[i].element;
}

uint64_t set_begin(set *s) {
    int i = 0;
    int ans = 0;

    if (s->a[0].statuts = occupied) {
        return ans;
    }

    while (ans == 0 && i < s->p) {
        if (s->a[i].statuts == occupied) {
            ans = i;
        }
        i++;
    }

    if (ans == 0) {
        return power_of_2(s->p);
    }
    return ans;
}

uint64_t set_end(set *s) {
    return power_of_2(s->p);
}

uint64_t set_next(set *s, uint64_t i) {
    int ans = 0;

    for (int k = i + 1; k < s->p; k++) {
        if (s->a[i].statuts == occupied) {
            ans = i;
            break;
        }
    }

    if (ans == 0) {
        return power_of_2(s->p);
    }

    return ans;
}

int main(void) {

    set *try = set_example();

    bool ans = set_is_member(try, 1492);

    return 0;
}