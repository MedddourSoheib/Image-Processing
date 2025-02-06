#include <stdio.h>
#include <stdlib.h>
#include "projet.h"
#include <string.h>
#include "pngtest/pngwrap.h"

int main(void) {
    // Créer une image pour l'entrée
    bwimage_t *input_image = E3ACreateImage();
    error_e err;


    // Charger l'image à partir d'un fichier
    printf("Chargement de l'image...\n");
    err = E3ALoadImage("../lena.png", input_image);
    if (err != E3A_OK) {
        fprintf(stderr, "Erreur de chargement de l'image : %d\n", err);
        return EXIT_FAILURE;
    }


    // Affichage des dimensions de l'image
    printf("Image chargée : %u x %u\n", input_image->width, input_image->height);


    // Conversion de l'image réelle en image complexe
    C_image complex_image = int2cplx(input_image);  // Corrigé pour passer l'objet directement
    printf("Image convertie en complexe\n");


    // Première application de la FFT
    apply_fft_2d(&complex_image, 1);  // 1 pour effectuer une transformation de Fourier


    // Deuxième application de la FFT
    apply_fft_2d(&complex_image, 1); 


   bwimage_t *result_image = (bwimage_t *)malloc(sizeof(bwimage_t));

    // Conversion de l'image complexe transformée en image réelle
    cplx2int(complex_image, result_image);  // Modification directe du pointeur
    printf("Image complexe convertie en image réelle\n");


    // Sauvegarder l'image résultante
    err = E3ADumpImage("output_lena.bmp", &result_image);  // Remplacez par le chemin de sortie désiré
    if (err != E3A_OK) {
        printf("Erreur lors de la sauvegarde de l'image\n");
        return -1;
    }
    printf("Image sauvegardée avec succès\n");


    // Libération des ressources allouées
    free(input_image->data);  // Libération de la mémoire de l'image d'entrée
    free(result_image->data);  // Libération de la mémoire de l'image résultante
    free(complex_image.data); // Libération de la mémoire de l'image complexe
    

    return 0;
}










    
