#include "projet.h"
#include "pngwrap.h"
#include <string.h>
#include <stdio.h>


// Fonction pour convertir une image réelle en image complexe
C_image int2cplx(bwimage_t real_image) {
    // Créer une image complexe
    C_image complex_image;
    complex_image.width = real_image.width;
    complex_image.height = real_image.height;

    // Allouer de la mémoire pour l'image complexe
    complex_image.data = (cplx *)malloc(real_image.width * real_image.height * sizeof(cplx));
    if (complex_image.data == NULL) {
        fprintf(stderr, "Memory allocation failed for complex image\n");
        exit(1);  // Quitter en cas d'échec d'allocation mémoire
    }

    // Remplir l'image complexe avec les valeurs de l'image réelle
    for (unsigned int y = 0; y < real_image.height; y++) {
        for (unsigned int x = 0; x < real_image.width; x++) {
            unsigned int idx = y * real_image.width + x;

            // Partie réelle : correspond à l'intensité du pixel dans l'image réelle
            complex_image.data[idx].Re = (float)real_image.data[y][x];

            // Partie imaginaire : initialisée à 0
            complex_image.data[idx].Im = 0.0f;
        }
    }

    return complex_image;
}