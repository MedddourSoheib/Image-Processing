#if !defined(__PROJET__H__)
#define __PROJET__H__

//*****************************************************************************************************/
/*                                               Lecture d'image                                      */
/*****************************************************************************************************/

E3ACreateRGBAImage(); /* Creates the structure on the heap and initialize it to the defaults */
E3ALoadRGBAImage();   /* Loads image from the open tiff file. Data are allocated on the heap. */
E3ADumpRGBAImage();   /* Dumps the image in the new tiff file */
E3AFreeRGBAImage();   /* Deallocates the resources */


//*****************************************************************************************************/
/*                         conversion d'une image en structure complexe                               */
/*****************************************************************************************************/
typedef struct 
{
    double Re;
    double Im;

} cplx;

typedef struct {
    int width;
    int height;
    cplx *data;
} C_image; 



typedef struct
  {
    unsigned int width;
    unsigned int height;
    unsigned char **data; /* Access intensities as image.data[row][col] */
    unsigned char *rawdata;
  } bwimage_t;

C_image int2cplx(bwimage_t *real_image);

//*****************************************************************************************************/
/*                                                Transforme de fourier                               */
/*****************************************************************************************************/

void apply_fft_2d(C_image *complex_image, int isign);



//*****************************************************************************************************/
/*                                                    Produit                                         */
/*****************************************************************************************************/

// C_image produit_images(C_image 1, C_image 2);





//*****************************************************************************************************/
/*                                                      Transformer Inverser                          */
/*****************************************************************************************************/



//*****************************************************************************************************/
/*                                                      Complexe to Real                             */
/*****************************************************************************************************/



//bwimage_t cplx2int(C_image complex_image);
void cplx2int(C_image complex_image, bwimage_t *real_image);









//*****************************************************************************************************/
/*                                                      Recuperer l'image                            */
/*****************************************************************************************************/
//Sauvergarder();  
















                                                                        











#endif 