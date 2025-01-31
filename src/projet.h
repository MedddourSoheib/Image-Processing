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
typedef struct {
    int width;
    int height;
    complex_t *data;
} C_image; 

typedef struct 
{
    double Re;
    double Im;

} complex_t;

typedef struct
  {
    unsigned int width;
    unsigned int height;
    unsigned char **data; /* Access intensities as image.data[row][col] */
    unsigned char *rawdata;
  } bwimage_t;


complex_t convert_to_complex(bwimage_t *image);  

//*****************************************************************************************************/
/*                                                Transforme de fourier                               */
/*****************************************************************************************************/

void apply_fft_on_image(complex_t *image_complex, unsigned int width, unsigned int height, int isign) ;








//*****************************************************************************************************/
/*                                                    Produit                                         */
/*****************************************************************************************************/

//produit_image(); 





//*****************************************************************************************************/
/*                                                      Transformer Inverser                          */
/*****************************************************************************************************/


//complexe2float();









//*****************************************************************************************************/
/*                                                      Recuperer l'image                            */
/*****************************************************************************************************/
//Sauvergarder();  
















                                                                        











#endif 