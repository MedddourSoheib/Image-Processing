#include <stdlib.h>
#include <stdio.h>
#include "projet.h"
#include <math.h>

// Produit de convolution dans le domaine de Fourier
C_image * produit_images(C_image image1, C_image image2) {
    // Vérifier que les dimensions des images sont compatibles
    if (image1.width != image2.width || image1.height != image2.height) {
        // Ajuster les dimensions pour correspondre à la plus grande taille
        int new_width = (image1.width > image2.width) ? image1.width : image2.width;
        int new_height = (image1.height > image2.height) ? image1.height : image2.height;

        fprintf(stderr, "Avertissement : redimensionnement des images à %d x %d pour la convolution.\n", new_width, new_height);
        
        // Allouer une nouvelle image avec les dimensions ajustées
        C_image *resized_image1 = (C_image *)malloc(sizeof(C_image));
        C_image *resized_image2 = (C_image *)malloc(sizeof(C_image));
        
        if (!resized_image1 || !resized_image2) {
            fprintf(stderr, "Erreur d'allocation mémoire pour le redimensionnement\n");
            return NULL;
        }
        
        resized_image1->width = new_width;
        resized_image1->height = new_height;
        resized_image2->width = new_width;
        resized_image2->height = new_height;
        
        resized_image1->cdata = (cplx *)calloc(new_width * new_height, sizeof(cplx));
        resized_image2->cdata = (cplx *)calloc(new_width * new_height, sizeof(cplx));
        
        if (!resized_image1->cdata || !resized_image2->cdata) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les données redimensionnées\n");
            free(resized_image1);
            free(resized_image2);
            return NULL;
        }
        
        // Copier les données des images d'origine dans les nouvelles images redimensionnées
        for (int y = 0; y < image1.height; y++) {
            for (int x = 0; x < image1.width; x++) {
                resized_image1->cdata[y * new_width + x] = image1.cdata[y * image1.width + x];
            }
        }
        for (int y = 0; y < image2.height; y++) {
            for (int x = 0; x < image2.width; x++) {
                resized_image2->cdata[y * new_width + x] = image2.cdata[y * image2.width + x];
            }
        }
        
        image1 = *resized_image1;
        image2 = *resized_image2;
    }

    // Allocation de la nouvelle image résultante
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
        result->cdata[i].Im = (Im1 * Re2) - (Re1 * Im2);
    }

    return result;
}