#include <stdio.h>
#include <stdlib.h>
#include "projet.h"
#include <string.h>
#include "pngtest/pngwrap.h"

int main(void){
    
    bwimage_t *input_image = E3ACreateImage();  // Créer une image pour l'entrée
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
    C_image complex_image = int2cplx(input_image);
    printf("Image convertie en complexe\n");

    // Appliquer la FFT à l'image complexe
    apply_fft_on_image(&complex_image, 1);  // Applique la FFT (isign = 1 pour la transformation directe)
    printf("FFT appliquée sur l'image complexe\n");

    // Conversion de l'image complexe transformée en image réelle
    bwimage_t result_image = cplx2int(complex_image);
    printf("Image complexe convertie en image réelle\n");

    err = E3ADumpImage("output_lena.bmp", &result_image);  // Remplacez par le chemin de sortie désiré
    if (err != E3A_OK) {
        printf("Erreur lors de la sauvegarde de l'image\n");
        return -1;
    }
    printf("Image sauvegardée avec succès\n");

    // Libération des ressources allouées
    free(input_image);
    free(result_image.data);
    free(complex_image.data);
    return 0;
}
















    
