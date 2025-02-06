#include "projet.h"
#include "pngwrap.h"
#include <string.h>
#include <stdio.h>


C_image int2cplx(bwimage_t *real_image) {
    // Vérifier si l'image d'entrée est valide
    if (!real_image || !real_image->data) {
        fprintf(stderr, "Invalid input image\n");
        exit(1);
    }

    // Créer une image complexe
    C_image complex_image;
    complex_image.width = real_image->width;
    complex_image.height = real_image->height;

    // Allouer de la mémoire pour l'image complexe
    complex_image.data = (cplx *)malloc(real_image->width * real_image->height * sizeof(cplx));
    if (!complex_image.data) {
        fprintf(stderr, "Memory allocation failed for complex image\n");
        exit(1);
    }

    // Remplir l'image complexe avec les valeurs de l'image réelle
    for (unsigned int y = 0; y < real_image->height; y++) {
        for (unsigned int x = 0; x < real_image->width; x++) {
            unsigned int idx = y * real_image->width + x;

            // Partie réelle : pixel de l'image originale
            complex_image.data[idx].Re = (double)real_image->data[y][x];

            // Partie imaginaire : initialisée à 0
            complex_image.data[idx].Im = 0.0;
        }
    }

    return complex_image;
}