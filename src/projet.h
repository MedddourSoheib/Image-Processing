#ifndef PROJECT_H
#define PROJECT_H

#include "pngwrap.h"


//*****************************************************************************************************/
/*                            Définition de la structure pour complexe                                */
/*****************************************************************************************************/
typedef struct {
    float Re;   // Partie réelle
    float Im;   // Partie imaginaire
} cplx;

//*****************************************************************************************************/
/*                            Définition de la structure pour l'image complexe                        */
/*****************************************************************************************************/ 
typedef struct {
    int width;   // Largeur de l'image
    int height;  // Hauteur de l'image
    cplx *cdata; // Données de l'image complexe
} C_image;


//*****************************************************************************************************/
/*                           Fonction de conversion de l'image réelle vers l'image complexe          */
/*****************************************************************************************************/
C_image * int2cplx(bwimage_t *int_image);


//*****************************************************************************************************/
/*                            Fonction FFT (Transformation de Fourier) sur l'image complexe          */
/*****************************************************************************************************/ 
void fourn(float data[], unsigned long nn[], int ndim, int isign);


//*****************************************************************************************************/
/*                            Fonction pour appliquer la FFT à une image complex                     */
/*****************************************************************************************************/
void apply_fft(C_image *complex_image,int isign);


//*****************************************************************************************************/
/*                                     Produit de convolution                                        */
/*****************************************************************************************************/
C_image * produit_images(C_image image1, C_image image2);


//*****************************************************************************************************/
/*           Fonction de conversion de l'image complexe vers l'image réelle                           */
/*****************************************************************************************************/
bwimage_t * cplx2int(C_image *complex_image);



#endif // PROJECT_H