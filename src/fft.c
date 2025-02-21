#include <math.h>
#include <stdio.h>
#include <string.h>
#include "projet.h"

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void fourn(float data[], unsigned long nn[], int ndim, int isign)
{
  //attention: dans le code original les tableaux data et nn commencent avec l'indice 1 (code traduit du fortran)
   // pour traiter les tableaux commençant par l'indice 0 comme d'habitude en c et sans modifier le reste du code,
   // on ajoute une ligne pour décaler les pointeurs:

   data--; nn--;   //modif PW : maintenant les tableaux sont indexés à partir de 0

	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot;
	float tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	for (ntot=1,idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for (idim=ndim;idim>=1;idim--) {
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) {
			if (i2 < i2rev) {
				for (i1=i2;i1<=i2+ip1-2;i1+=2) {
					for (i3=i1;i3<=ip3;i3+=ip2) {
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) {
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2) {
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) {
				for (i1=i3;i1<=i3+ip1-2;i1+=2) {
					for (i2=i1;i2<=ip3;i2+=ifp2) {
						k1=i2;
						k2=k1+ifp1;
						tempr=(float)wr*data[k2]-(float)wi*data[k2+1];
						tempi=(float)wr*data[k2+1]+(float)wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1] += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
}
#undef SWAP

void apply_fft_nn(C_image *complex_image, float *data, int isign) {
    if (!complex_image || !complex_image->cdata || !data) {
        fprintf(stderr, "Invalid input image or data array\n");
        exit(1);
    }
    
    int ndim = 2;
    
    unsigned long nn[2] = {complex_image->width, complex_image->height};
    unsigned int size = complex_image->width * complex_image->height;

    // Remplir le tableau 'data' avec les parties réelle et imaginaire de l'image complexe
    for (unsigned int i = 0; i < size; i++) {
        data[2 * i] = (float)complex_image->cdata[i].Re;  // Partie réelle
        data[2 * i + 1] = (float)complex_image->cdata[i].Im;  // Partie imaginaire
    }

    // Appliquer la FFT avec le signe spécifié
    fourn(data - 1, nn, ndim, isign);
}
