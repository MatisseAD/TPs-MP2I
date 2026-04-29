#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int item;

struct node {
    item key;
    struct node *left;
    struct node *right;
};

typedef struct node node;

struct bst {
    node *root;
};

typedef struct bst bst;

// Exercice 1

node *new_node(item x) {
    node *newNode = malloc(sizeof(node));
    newNode->key = x;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bst *bst_make_empty(void) {
    bst *newBst = malloc(sizeof(bst));
    newBst->root = NULL;
    return newBst;
}

void node_free(node *n) {

    if (n == NULL) return;

    if (n->left != NULL) {
        node_free(n->left);
    }
    if (n->right != NULL) {
        node_free(n->right);
    }
    free(n);
}

void bst_free(bst *t) {
    node_free(t->root);
    free(t);
}

// Exercice 2

node *node_insert(node *t, item x) {

    if (t == NULL) {
        return new_node(x);
    }

    if (t->key == x) return t;

    if (t->key < x) {
        if (t->right == NULL) {
            node *newNode = new_node(x);
            t->right = newNode;
            return t;
        } else {
            t->right = node_insert(t->right, x);
            return t;
        }
    } else {
        if (t->left == NULL) {
            node *newNode = new_node(x);
            t->left = newNode;
            return t;
        } else {
            t->left = node_insert(t->left, x);
            return t;
        }
    }
}

void bst_insert(bst *t, item x) {
    t->root = node_insert(t->root, x);
}

bst *bst_from_array(item arr[], int len) {

    bst *newBst = bst_make_empty();

    for (int i = 0; i < len; i++) {
        bst_insert(newBst, arr[i]);
    }

    return newBst;
}

// Exercice 3

item node_min(node *n);

item bst_min(bst *t);

bool node_member(node *n, item x);

bool bst_member(bst *t, item x);

void test_member(void) {
    int n = 6;
    item arr[] = {50, 30, 20, 60, 40, 10};
    bst *t = bst_from_array(arr, 6);
    for (int i = 0; i < n; i++) {
        assert(bst_member(t, arr[i]));
        assert(!bst_member(t, 1 + arr[i]));
    }
    printf("test_member : OK !");
}

int node_size(node *n);

int bst_size(bst *t);

int node_height(node *n);

int bst_height(bst *t);

void node_write_to_array(node *n, item arr[], int *offset_ptr);

item *bst_to_array(bst *t, int *nb_elts);

// Exercice 4

node *node_extract_min(node *n, int *min_ptr);

node *node_extract_min(node *n, int *min_ptr);

node *node_delete(node *n, item x);

// Exercice 5

// rand_between(lo, hi) return a random integer
// between lo (inclusive) and hi (exclusive).
//
// Not perfectly uniform, but close enough
// provided hi - lo << RAND_MAX.

int rand_between(int lo, int hi) {
    int x = rand();
    return lo + x % (hi - lo);
}

// Shuffles (applies a random permutation to) the argument array.
// This will be uniform
// provided the function rand_between is (which is not
// quite the case here, but it won't make any difference
// in practice).

void shuffle(item arr[], int len) {
    assert(len < RAND_MAX);
    for (int i = 0; i < len; i++) {
        int j = rand_between(i, len);
        item tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main(void) {

    return 0;
}
