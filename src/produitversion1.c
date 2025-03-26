#include <stdlib.h>
#include <stdio.h>
#include "projet.h"

// Produit de convolution dans le domaine de Fourier
C_image * produit_images(C_image image1, C_image image2) {
    // Vérifier que les dimensions des images sont compatibles
    if (image1.width != image2.width || image1.height != image2.height) {
        fprintf(stderr, "Erreur : les images doivent avoir les mêmes dimensions pour la convolution !\n");
        return NULL;
    }

    // Allocation de la nouvelle image resultante
    C_image *result = (C_image *)malloc(sizeof(C_image));
    if (!result) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'image résultat\n");
        return NULL;
    }

    result->width = image1.width;
    result->height = image1.height;
    result->cdata = (cplx *)malloc(image1.width * image1.height * sizeof(cplx));
    if (!result->cdata) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les données complexes\n");
        free(result);
        return NULL;
    }

    // Produit de convolution (multiplication terme à terme dans le domaine de Fourier)
    for (int i = 0; i < image1.width * image1.height; i++) {
        float Re1 = image1.cdata[i].Re;
        float Im1 = image1.cdata[i].Im;
        float Re2 = image2.cdata[i].Re;
        float Im2 = image2.cdata[i].Im;

        // Multiplication complexe : (Re1 + i*Im1) * (Re2 - i*Im2)
        result->cdata[i].Re = (Re1 * Re2) + (Im1 * Im2);
        result->cdata[i].Im = (Im1 * Re2) - (Re1 * Im2) ;
    }

    return result;
}
