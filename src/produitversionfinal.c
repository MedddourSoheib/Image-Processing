#include <stdlib.h>
#include <stdio.h>
#include "projet.h"

// Produit de convolution dans le domaine de Fourier
C_image * produit_images(C_image image1, C_image image2) {
    // Déterminer la taille de l'image résultante
    int max_width = (image1.width > image2.width) ? image1.width : image2.width;
    int max_height = (image1.height > image2.height) ? image1.height : image2.height;

    // Allocation de la nouvelle image résultante
    C_image *result = (C_image *)malloc(sizeof(C_image));
    if (!result) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'image résultat\n");
        return NULL;
    }

    result->width = max_width;
    result->height = max_height;
    result->cdata = (cplx *)calloc(max_width * max_height, sizeof(cplx));
    if (!result->cdata) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les données complexes\n");
        free(result);
        return NULL;
    }

    // Produit de convolution (multiplication terme à terme dans le domaine de Fourier)
    for (int y = 0; y < max_height; y++) {
        for (int x = 0; x < max_width; x++) {
            int index = y * max_width + x;
            float Re1 = 0.0, Im1 = 0.0, Re2 = 0.0, Im2 = 0.0;

            // Récupérer les valeurs si elles existent dans chaque image
            if (x < image1.width && y < image1.height) {
                int idx1 = y * image1.width + x;
                Re1 = image1.cdata[idx1].Re;
                Im1 = image1.cdata[idx1].Im;
            }
            if (x < image2.width && y < image2.height) {
                int idx2 = y * image2.width + x;
                Re2 = image2.cdata[idx2].Re;
                Im2 = image2.cdata[idx2].Im;
            }

            // Multiplication complexe : (Re1 + i*Im1) * (Re2 - i*Im2)
            float Fx = (x < max_width / 2) ? x : x - max_width;
            float Fy = (y < max_height / 2) ? y : y - max_height;
            float coeff = (Fx * Fx) + (Fy * Fy);
            result->cdata[index].Re = coeff * (Re1 * Re2 + Im1 * Im2);
            result->cdata[index].Im = coeff * (-Re1 * Im2 + Im1 * Re2);
        }
    }

    return result;
}
