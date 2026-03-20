#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t empty = 0;
const uint8_t occupied = 1;
const uint8_t tombstone = 2;
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

T set_get(set *s, uint64_t i) {

    return s->a[i].element;
}

uint64_t set_begin(set *s) {
    int i = 0;
    int ans = 0;

    if (s->a[0].statuts == occupied) {
        return ans;
    }

    while (ans == 0 && i < power_of_2(s->p)) {
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

uint64_t set_search(set *s, T x, bool *found) {
    uint64_t i = hash(x, s->p);
    bool ans = false;
    int size = power_of_2(s->p);

    while (s->a[i].statuts != empty && !(ans)) {
        if (s->a[i].element == x) {
            ans = true;
        }
        i = (i + 1) % (size);
    }

    (*found) = ans;

    return i - 1;
}

bool set_is_member(set *s, T x) {
    bool is_here;
    uint64_t i = set_search(s, x, &is_here);

    return is_here;
}

void set_resize(set *s, int p) {
    set *new_s = malloc(sizeof(set));
    uint64_t new_size = power_of_2(p);
    new_s->p = p;
    new_s->nb_empty = new_size;
    new_s->a = malloc(new_size * sizeof(bucket));
}

void set_resize(set *s, int p) {
    set *new_set = malloc(sizeof(set));

    uint64_t new_size = power_of_2(p);
    new_set->nb_empty = new_size;
    new_set->p = p;
    new_set->a = malloc(new_size * sizeof(bucket));

    for (int i; i < new_size; i++) {
        s->a[i].statuts = empty;
    }

    int i = set_begin(s);

    while (i < set_end(s)) {
        T value = s->a[i].element;
        uint64_t indice_case = hash(value, p);

        while (s->a[i].statuts != empty) {
            indice_case++;
        }

        new_set->a[indice_case].element = value;
        new_set->a[indice_case].statuts = occupied;
        new_set->nb_empty--;

        i = set_next(s, i);
    }

    free(s->a);
    *s = *new_set;
    free(new_set);
}

/**
 * 
 * 3. Écrire la fonction void set_add(set *s, T x) ajoutant l’élément x à la table s. Afin de toujours conserver
une case « libre » dans notre tableau et de ne pas trop le charger, on décidera de doubler la taille du tableau
dès que le nombre de cases « libres » est inférieur au tiers de la taille du tableau
 * 
 */

void set_add(set *s, T x) {
    bool no_useful = false;

    if (s->nb_empty <= s->nb_empty * (1 / 3)) {
        set_resize(s, s->p * 2);
    }

    if (!set_is_member(s, x)) {
        uint64_t i = set_search(s, x, &no_useful);
        s->a[i].element = x;
        s->a[i].statuts = occupied;
        s->nb_empty--;
    }
}

// 4. Suppression d'éléments

/*

1. Expliquer pourquoi il n’est pas possible de supprimer un élément de la table en changeant simplement le statut
de sa case en case « libre ».

Si on met une telle case vide, alors la recherche d'un élément peut être fausse.

*/

/*

2. Proposer des nouvelles implémentations des fonctions set_search, set_begin, set_next et set_add fonction-
nant avec les pierres tombales.

*/

uint64_t set_search(set *s, T x, bool *found) {
    uint64_t i = hash(x, s->p);
    bool ans = false;
    int size = power_of_2(s->p);
    int ftb = NULL;

    while (s->a[i].statuts != empty && !(ans)) {
        if (s->a[i].statuts == tombstone && ftb == NULL) {
            ftb = i;
        }

        if (s->a[i].element == x && s->a[i].statuts != tombstone) {
            ans = true;
        }

        i = (i + 1) % size;
    }

    (*found) = ans;

    if (!ans) {
        if (ftb != NULL) {
            return ftb;
        }
    } else {
    }


    return i - 1;
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


int main(void) {

    set *try = set_example();

    bool ans = set_is_member(try, 1492);

    return 0;
}