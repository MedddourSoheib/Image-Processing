#include <stdio.h>
#include "projet.h"


bwimage_t cplx2int(C_image *complex_image) {
    if (!complex_image || !complex_image->cdata) {
        fprintf(stderr, "Image complexe invalide\n");
        exit(1);
    }

    // Créer une image en niveaux de gris
    bwimage_t image;
    image.width = complex_image->width;
    image.height = complex_image->height;

    // Allouer la mémoire pour rawdata
    image.rawdata = (unsigned char *)malloc(image.width * image.height * sizeof(unsigned char));
    if (!image.rawdata) {
        fprintf(stderr, "Erreur d'allocation mémoire pour rawdata\n");
        exit(1);
    }

    // 1️⃣ Trouver les valeurs min et max
    float Umin = complex_image->cdata[0].Re;
    float Umax = complex_image->cdata[0].Re;

    for (unsigned int i = 0; i < image.width * image.height; i++) {
        if (complex_image->cdata[i].Re < Umin) Umin = complex_image->cdata[i].Re;
        if (complex_image->cdata[i].Re > Umax) Umax = complex_image->cdata[i].Re;
    }

    // 2️⃣ Appliquer la normalisation avec ta formule
    float Vmax = 255.0; // Valeur maximale de l'image en niveaux de gris

    for (unsigned int i = 0; i < image.width * image.height; i++) {
        // Application de la formule de normalisation
        float Xu = complex_image->cdata[i].Re;
        float Xv = (Xu - Umin) * Vmax / (Umax - Umin); // Normalisation
        
        // Clamping des valeurs entre 0 et 255
        if (Xv < 0) Xv = 0;
        if (Xv > 255) Xv = 255;

        image.rawdata[i] = (unsigned char)Xv; // Affecter à rawdata
    }

    return image;
}
