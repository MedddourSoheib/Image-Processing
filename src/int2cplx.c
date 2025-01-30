#include "projet.h"
#include "pngwrap.h"
#include <string.h>
#include <stdio.h>


complex_t *convert_to_complex(bwimage_t *image) {
    // Allouer un tableau pour stocker les valeurs complexes
    complex_t *image_complex = (complex_t *)malloc(image->width * image->height * sizeof(complex_t));

    if (!image_complex) {
        // Gestion des erreurs si l'allocation échoue
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Remplir l'image complexe avec les valeurs de l'image en niveaux de gris
    for (unsigned int y = 0; y < image->height; y++) {
        for (unsigned int x = 0; x < image->width; x++) {
            unsigned int idx = y * image->width + x;
            image_complex[idx].Re = image->data[y][x]; // Partie réelle : intensité du pixel
            image_complex[idx].Im = 0.0;               // Partie imaginaire : initialisée à zéro
        }
    }

    return image_complex; // Retourner le tableau de données complexes
}

