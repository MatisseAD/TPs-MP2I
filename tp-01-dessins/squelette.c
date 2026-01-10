
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 600
#define WIDTH 400

typedef int rgb[3];

rgb red = {255, 0, 0};
rgb green = {0, 255, 0};
rgb blue = {0, 0, 255};
rgb black = {0, 0, 0};
rgb white = {255, 255, 255};
rgb lightgray = {150, 150, 150};

rgb canvas[HEIGHT][WIDTH];

void put_pixel(int x, int y, rgb c) {
    int i = HEIGHT - 1 - y;
    int j = x;
    if (i < 0 || i >= HEIGHT || j < 0 || j >= WIDTH)
        return;
    for (int k = 0; k < 3; k++) {
        canvas[i][j][k] = c[k];
    }
}

/***********************/
/* Création du fichier */
/***********************/

void print_canvas(void) {
    printf("P3\n");
    printf("%d %d\n", WIDTH, HEIGHT);
    printf("255\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < 3; k++) {
                printf("%d ", canvas[i][j][k]);
            }
            printf("\n");
        }
    }
}

/***********************/
/*  Primitives simples */
/***********************/


void draw_h_line(int y, int x0, int x1, rgb c) {

    if (x0 < x1) {
        for (int i = x0; i <= x1; i++) {
            put_pixel(i, y, c);
        }
    } else if (x0 > x1) {
        for (int i = x1; i <= x0; i++) {
            put_pixel(i, y, c);
        }
    }
}

void draw_v_line(int x, int y0, int y1, rgb c) {

    if (y0 < y1) {
        for (int i = y0; i <= y1; i++) {
            put_pixel(x, i, c);
        }
    } else if (y0 > y1) {
        for (int i = y1; i <= y0; i++) {
            put_pixel(x, i, c);
        }
    }
}

void draw_rectangle(int x0, int y0, int x1, int y1, rgb c) {

    draw_h_line(y0, x0, x1, c);
    draw_h_line(y1, x0, x1, c);
    draw_v_line(x0, y0, y1, c);
    draw_v_line(x1, y0, y1, c);
}


void fill_rectangle(int x0, int y0, int x1, int y1, rgb c) {

    for (int i = x0; i <= x1; i++) {
        draw_rectangle(i, y0, x1, y1, c);
    }
}

// A REFAIRE

void draw_disk(int xc, int yc, int radius, rgb c) {

    draw_v_line(xc, yc, yc + radius, c);
    draw_v_line(xc, yc - radius, yc, c);

    draw_h_line(yc, xc, xc + radius, c);
    draw_h_line(yc, xc - radius, xc, c);
}

// A REFAIRE

void fill_disk(int xc, int yc, int radius, rgb c) {

    for (int i = radius; i >= 0; i--) {

        draw_disk(xc, yc + i, i, c);
    }
}

/***********************/
/* Mélange de couleurs */
/***********************/

int clamp(double x) {

    if (x < 0) {
        return 0;
    } else if (x > 255) {
        return 255;
    }

    return x;
}


void mix(rgb c0, rgb c1, double alpha, double beta, rgb result) {

    result[0] = clamp(alpha * c0[0] + beta * c1[0]);
    result[1] = clamp(alpha * c0[1] + beta * c1[1]);
    result[2] = clamp(alpha * c0[2] + beta * c1[2]);
}

void intepolate(rgb c0, rgb c1, double t, rgb result) {

    double alpha = 1.0 - t;
    double beta = t;

    mix(c0, c1, alpha, beta, result);
}


void draw_h_gradient(int y, int x0, int x1, rgb c0, rgb c1) {

    rgb color;

    if (x0 < x1) {
        for (int i = x0; i <= x1; i++) {
            intepolate(c0, c1, (double) (i - x0) / (x1 - x0), color);
            put_pixel(i, y, color);
        }
    } else if (x0 > x1) {
        for (int i = x1; i <= x0; i++) {
            intepolate(c0, c1, (double) (i - x1) / (x0 - x1), color);
            put_pixel(i, y, color);
        }
    }
}


void fill_disk_gradient(int xc, int yc, int radius, rgb c_center, rgb c_edge) {

    
}

void get_pixel(int x, int y, rgb result);
void mix_pixel(int x, int y, double alpha, double beta, rgb c);
void add_disk(int xc, int yc, int radius, rgb c);

/*******************/
/* Tracé de lignes */
/*******************/

void draw_line(int x0, int y0, int x1, int y1, rgb c);
void draw_spokes(int xc, int yc, int radius, int nb_spokes, rgb c);

/* Exercice 11 */

void bresenham_low(int x0, int y0, int x1, int y1, rgb c);
void bresenham_high(int x0, int y0, int x1, int y1, rgb c);
void bresenham(int x0, int y0, int x1, int y1, rgb c);

/* Exercice 12 */

void draw_circle(int xc, int yc, int radius, rgb c);

/*****************/
/* Fonction main */
/*****************/

int main(void) {
    // Full rouge

    draw_h_gradient(100, 100, 400, red, blue);

    print_canvas();

    return 0;
}
