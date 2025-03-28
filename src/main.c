#include <stdio.h>
#include <stdlib.h>
#include "projet.h"
#include <string.h>
#include "pngwrap.h"

int main() {
    // Créer une image pour l'entrée
    bwimage_t * image1 = E3ACreateImage();
    bwimage_t * image2 = E3ACreateImage();
    bwimage_t * image_corr = E3ACreateImage();
    bwimage_t * test_image ;
    C_image * imagec1 =NULL ;
    C_image * imagec2 =NULL ;
    C_image *image_corr_c = NULL;

    error_e err;


    // Charger l'image à partir d'un fichier
    printf("Chargement de l'image...\n");
    err = E3ALoadImage("../image2.png", image1);
    if (err != E3A_OK) {
        fprintf(stderr, "Erreur de chargement de l'image : %d\n", err);
        return EXIT_FAILURE;
    }

    // Charger l'image à partir d'un fichier
    printf("Chargement de l'image...\n");
    err = E3ALoadImage("../image3.png", image2);
    if (err != E3A_OK) {
        fprintf(stderr, "Erreur de chargement de l'image : %d\n", err);
        return EXIT_FAILURE;
    }


   imagec1 = int2cplx(image1);
   imagec2 = int2cplx(image2);


   apply_fft(imagec1,1);
   apply_fft(imagec2,1);

// Produit de convolution
    image_corr_c = produit_images(*imagec1,*imagec2,0.9);
    if (image_corr_c == NULL) {
        fprintf(stderr, "Erreur lors du produit de convolution\n");
        free(imagec1);
        free(imagec2);
        return EXIT_FAILURE;
    }

    apply_fft(image_corr_c, -1);

    test_image = cplx2int(image_corr_c);

if (test_image == NULL) {
    fprintf(stderr, "Erreur lors de la conversion de l'image complexe en image réelle\n");
    free(image_corr_c);
   
    return EXIT_FAILURE;
}


    // Sauvegarde de l'image résultante
    if (E3ADumpImage("../test2-3v3-0.9.png", test_image) != E3A_OK) {
        fprintf(stderr, "Erreur lors de la sauvegarde de l'image\n");
    }

    
    free(imagec1);
    free(imagec2);
    free(image_corr_c);
    free(test_image);

   return 0;
}

   

   

  
  
