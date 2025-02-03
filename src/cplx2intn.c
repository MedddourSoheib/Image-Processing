#include "projet.h"
#include "pngwrap.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

bwimage_t cplx2int(C_image complex_image) {
    bwimage_t real_image;
    real_image.width = complex_image.width;
    real_image.height = complex_image.height;

    // Allocation mémoire pour rawdata (tableau 1D contigu)
    real_image.rawdata = (unsigned char *)malloc(real_image.width * real_image.height * sizeof(unsigned char));
    if (!real_image.rawdata) {
        fprintf(stderr, "Memory allocation failed for rawdata\n");
        exit(1);
    }

    // Allocation mémoire pour data (tableau 2D pointant sur rawdata)
    real_image.data = (unsigned char **)malloc(real_image.height * sizeof(unsigned char *));
    if (!real_image.data) {
        fprintf(stderr, "Memory allocation failed for data pointers\n");
        free(real_image.rawdata);
        exit(1);
    }

    for (unsigned int y = 0; y < real_image.height; y++) {
        real_image.data[y] = real_image.rawdata + y * real_image.width;
    }

    // Étape 1 : Trouver la valeur maximale du module
    float max_magnitude = 0.0f;
    for (unsigned int i = 0; i < real_image.width * real_image.height; i++) {
        float magnitude = sqrt(complex_image.data[i].Re * complex_image.data[i].Re +
                               complex_image.data[i].Im * complex_image.data[i].Im);
        if (magnitude > max_magnitude) {
            max_magnitude = magnitude;
        }
    }

    // Éviter la division par zéro (au cas où l'image est toute noire)
    if (max_magnitude == 0.0f) {
        max_magnitude = 1.0f;
    }

    // Étape 2 : Conversion et normalisation des pixels
    for (unsigned int y = 0; y < real_image.height; y++) {
        for (unsigned int x = 0; x < real_image.width; x++) {
            unsigned int idx = y * real_image.width + x;
            float magnitude = sqrt(complex_image.data[idx].Re * complex_image.data[idx].Re +
                                   complex_image.data[idx].Im * complex_image.data[idx].Im);

            // Normalisation entre 0 et 255
            real_image.data[y][x] = (unsigned char)((magnitude / max_magnitude) * 255.0f);
        }
    }

    return real_image;
}