#include "projet.h"
#include "pngwrap.h"
#include <stdio.h>
#include <math.h>

void cplx2int(C_image complex_image, bwimage_t *real_image) {
    real_image->width = complex_image.width;
    real_image->height = complex_image.height;

    // Allocation de la mémoire pour l'image réelle
    real_image->data = (unsigned char **)malloc(real_image->height * sizeof(unsigned char *));
    if (real_image->data == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'image réelle\n");
        exit(1);  // Sortie si l'allocation échoue
    }

    for (int i = 0; i < real_image->height; i++) {
        real_image->data[i] = (unsigned char *)malloc(real_image->width * sizeof(unsigned char));
        if (real_image->data[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la ligne %d de l'image réelle\n", i);
            exit(1);  // Sortie si l'allocation échoue
        }
    }

    // Remplir l'image réelle avec les valeurs calculées à partir de l'image complexe
    for (unsigned int y = 0; y < real_image->height; y++) {
        for (unsigned int x = 0; x < real_image->width; x++) {
            // Calcul de l'index dans l'image complexe
            unsigned int idx = y * real_image->width + x;

            // Calcul de la magnitude du nombre complexe (norme)
            float module = sqrt(complex_image.data[idx].Re * complex_image.data[idx].Re + 
                                complex_image.data[idx].Im * complex_image.data[idx].Im);

            // Normalisation de la magnitude (mettre dans l'intervalle [0, 255])
            unsigned char pixel_value = (unsigned char)(fmin(module, 255.0f));

            // Stocker la valeur dans l'image réelle
            real_image->data[y][x] = pixel_value;
        }
    }
}