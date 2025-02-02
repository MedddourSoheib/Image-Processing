#include "projet.h"
#include "pngwrap.h"
#include <stdio.h>
#include <math.h>

bwimage_t cplx2int (C_image complex_image){
    bwimage_t real_image;
    real_image.width = complex_image.width;
    real_image.height = complex_image.height;

    // Allocation de la mémoire pour l'image réelle 

    real_image.data = (unsigned char **)malloc(real_image.height * sizeof(unsigned char *));
    for(int i=0; i< real_image.height;i++){
        real_image.data[i] = (unsigned char *)malloc(real_image.width * sizeof(unsigned char ));
    }

    // Remplir l'image complexe avec les valeurs de l'image réelle
    for (unsigned int y = 0; y < real_image.height; y++) {
        for (unsigned int x = 0; x < real_image.width; x++) {
            unsigned int idx = y * real_image.width + x;

        float magnitude =sqrt(complex_image.data[idx].Re * complex_image.data[idx].Re + complex_image.data[idx].Im * complex_image.data[idx].Im );

    // Normalisation de la magnitude (mettre dans l'ntervalle [0, 255]
    unsigned char pixel_value =(unsigned char)(fmin(magnitude, 255.0f));

    // Stocker la valeur dans l'image réelle

    real_image.data[y][x]= pixel_value;            
        }
    }

    return real_image;
}
