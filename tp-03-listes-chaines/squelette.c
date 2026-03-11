#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*************/
/*  Partie 1 */
/*************/

typedef int T;

struct Node {
    T data;
    struct Node *next;
};

typedef struct Node node;

// 1.1 Création de listes

node *new_node(T data) {

    

}

node *cons(node *list, T data);

node *from_array(T array[], int len);

// 1.2 Parcours de listes

void free_list(node *n);

void free_list_rec(node *n);

int length(node *list);

// void test_length(void) {
//     assert(length(NULL) == 0);
//     node *u = cons(cons(NULL, 3), 4);
//     assert(length(u) == 2);
//     int t[3] = {2, 4, 6};
//     free_list(u);
//     u = from_array(t, 3);
//     assert(length(u) == 3);
//     assert(u->data == 2);
//     free_list(u);
// }

void print_list(node *n, bool newline);

T *to_array(node *u, int *n);

// void test_to_array(void) {
//     int t[5] = {1, 2, 3, 4, 5};
//     int n = 5;
//     node *u = from_array(t, n);
//     int *t2 = to_array(u, &n);
//     for (int i = 0; i < n; i++) {
//         assert(t[i] == t2[i]);
//     }
//     free(t2);
//     free_list(u);
// }

bool is_equal(node *u, node *v);

// void test_is_equal(void) {
//     int a[4] = {1, 2, 3, 4};
//     int b[4] = {1, 2, 4, 3};

//     node *u = from_array(a, 3);
//     node *v = from_array(a, 4);
//     assert(!is_equal(u, v));
//     free_list(u);
//     free_list(v);

//     u = from_array(a, 4);
//     v = from_array(b, 4);
//     assert(!is_equal(u, v));
//     free_list(u);
//     free_list(v);

//     u = from_array(a, 2);
//     v = from_array(b, 2);
//     assert(is_equal(u, v));

//     free_list(u);
//     free_list(v);
// }

// 1.3 Ordre et tri

bool is_sorted(node *u);

// void test_is_sorted(void) {
//     int t[5] = {1, 2, 4, 3, 5};

//     node *u = from_array(t, 0);
//     assert(is_sorted(u));
//     free_list(u);

//     u = from_array(t, 1);
//     assert(is_sorted(u));
//     free_list(u);

//     u = from_array(t, 3);
//     assert(is_sorted(u));
//     free_list(u);

//     u = from_array(t, 4);
//     assert(!is_sorted(u));
//     free_list(u);

//     u = from_array(t, 5);
//     assert(!is_sorted(u));
//     free_list(u);
// }

node *insert_rec(node *u, T x);

// void test_insert_rec(void) {
//     node *u = NULL;
//     u = insert_rec(u, 4);
//     u = insert_rec(u, 2);
//     u = insert_rec(u, 3);
//     u = insert_rec(u, 5);

//     int t[4] = {2, 3, 4, 5};
//     node *v = from_array(t, 4);
//     assert(is_equal(u, v));

//     free_list(u);
//     free_list(v);
// }

node *insertion_sort_rec(node *u);

// void test_insertion_sort_rec(void) {
//     int t[5] = {0, 4, 2, 1, 3};
//     int t_sorted[5] = {0, 1, 2, 3, 4};

//     node *u = from_array(t, 5);
//     node *v = insertion_sort_rec(u);
//     node *w = from_array(t_sorted, 5);

//     assert(is_equal(v, w));

//     free_list(u);
//     free_list(v);
//     free_list(w);
// }

// 1.4 Reverse

node *reverse_copy(node *u);

// void test_reverse_copy(void) {
//     int t[4] = {1, 2, 3, 4};
//     int t_rev[4] = {4, 3, 2, 1};
//     node *u = from_array(t, 4);
//     node *v = from_array(t_rev, 4);

//     node *u_rev = reverse_copy(u);
//     assert(is_equal(v, u_rev));

//     free_list(u);
//     free_list(v);
//     free_list(u_rev);
// }

node *copy_rec(node *u);

// void test_copy_rec(void) {
//     int t1[4] = {1, 2, 3, 4};
//     node *u = from_array(t1, 4);
//     node *v = copy_rec(u);

//     assert(is_equal(u, v));
//     free_list(u);
//     free_list(v);
// }

node *copy(node *u);

// void test_copy(void) {
//     int t1[4] = {1, 2, 3, 4};
//     node *u = from_array(t1, 4);
//     node *v = copy(u);

//     assert(is_equal(u, v));
//     free_list(u);
//     free_list(v);

//     u = NULL;
//     v = copy(u);
//     assert(is_equal(u, v));
// }

node *reverse(node *u);

// void test_reverse(void) {
//     int t[4] = {1, 2, 3, 4};
//     node *u = from_array(t, 4);
//     node *u_rev = reverse_copy(u);

//     u = reverse(u);
//     assert(is_equal(u, u_rev));

//     free_list(u);
//     free_list(u_rev);

//     u = NULL;
//     u = reverse(u);
//     assert(is_equal(u, NULL));
// }

// 1.5 Tri insertion

// 1.6 Tri fusion

node *split(node *u, int n);

void test_split(void);

node *merge(node *u, node *v);

node *merge_sort(node *u);

// void test_merge_sort(void) {
//     int t[10] = {1, 4, 0, 2, 3, 8, 5, 6, 6, 7};
//     node *u = from_array(t, 10);

//     u = merge_sort(u);
//     node *u_sorted = insertion_sort_it(u);
//     assert(is_equal(u, u_sorted));

//     free_list(u);
//     free_list(u_sorted);
// }

int main(void) { return 0; }
