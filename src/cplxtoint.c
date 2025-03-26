#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"  
#include "projet.h"




bwimage_t * cplx2int(C_image *complex_image) {
    // Allouer et initialiser la structure image
    bwimage_t * image = (bwimage_t *)malloc(sizeof(bwimage_t));
    if (!image) {
        fprintf(stderr, "Erreur d'allocation mémoire pour image\n");
        free(image);
        exit(1);
    }
    image->width = complex_image->width;
    image->height = complex_image->height;

    // Allouer la mémoire pour rawdata
    image->rawdata = (unsigned char *)malloc(image->width * image->height * sizeof(unsigned char));
    if (!image->rawdata) {
        fprintf(stderr, "Erreur d'allocation mémoire pour rawdata\n");
        free(image);
        exit(1);
    }

    // Allouer la mémoire pour data (tableau de pointeurs)
    image->data = (unsigned char **)malloc(image->height * sizeof(unsigned char *));
    if (!image->data) {
        free(image->rawdata);
        free(image);
        fprintf(stderr, "Erreur d'allocation mémoire pour data\n");
        exit(1);
    }

    // Assigner les pointeurs pour accéder aux pixels sous forme de tableau 2D
    for (unsigned int y = 0; y < image->height; y++) {
        image->data[y] = image->rawdata + y * image->width;
    }

    // 1️⃣ Trouver les valeurs min et max dans les parties réelles
    float Umin = complex_image->cdata[0].Re;
    float Umax = complex_image->cdata[0].Re;
    unsigned int total_pixels = image->width * image->height;

    for (unsigned int i = 0; i < total_pixels; i++) {
        if (complex_image->cdata[i].Re < Umin)
            Umin = complex_image->cdata[i].Re;
        if (complex_image->cdata[i].Re > Umax)
            Umax = complex_image->cdata[i].Re;
    }

    // 2️⃣ Appliquer la normalisation pour mapper les valeurs sur [0, 255]
    float Vmax = 255.0f; // Valeur maximale en niveaux de gris
    for (unsigned int i = 0; i < total_pixels; i++) {
        float Xu = complex_image->cdata[i].Re;
        float Xv = (Xu - Umin) * Vmax / (Umax - Umin);
        
        // Clamp la valeur pour être sûre qu'elle reste dans [0, 255]
        if (Xv < 0)
            Xv = 0;
        if (Xv > 255)
            Xv = 255;
        
        image->rawdata[i] = (unsigned char)Xv;
    }

    return image;
}
