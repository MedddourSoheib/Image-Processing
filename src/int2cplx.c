#include "projet.h"
#include "pngwrap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


C_image * int2cplx(bwimage_t *real_image) {

    C_image *complex_image = (C_image *)malloc(sizeof(C_image));
    complex_image->width = real_image->width;
    complex_image->height = real_image->height;

    // Allocation de mémoire pour l'real_image complexe
    
    complex_image->cdata = (cplx *)malloc(real_image->width * real_image->height * sizeof(cplx));
    
    if (!complex_image->cdata) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    // Remplir l'real_image complexe
    // l ligne et c colonne
    for (unsigned int l = 0; l < real_image->height; l++) {
        for (unsigned int c = 0; c < real_image->width; c++) {
            unsigned int idx = l * real_image->width + c;

            // Partie réelle : pixel de l'real_image réelle
            complex_image->cdata[idx].Re = (double)real_image->rawdata[idx];

            // Partie imaginaire : 0
            complex_image->cdata[idx].Im = 0.0;
        }
    }

    return complex_image;
}

    










    
