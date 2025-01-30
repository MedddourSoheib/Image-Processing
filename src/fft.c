#include <math.h>
#include "projet.h"

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void four1(float data[], unsigned long nn, int isign)
{
	unsigned long n,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta;
	float tempr,tempi;

	n=nn << 1;
	j=1;
	for (i=1;i<n;i+=2) {
		if (j > i) {
			SWAP(data[j],data[i]);
			SWAP(data[j+1],data[i+1]);
		}
		m=n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax=2;
	while (n > mmax) {
		istep=mmax << 1;
		theta=isign*(6.28318530717959/mmax);
		wtemp=sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi=sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=n;i+=istep) {
				j=i+mmax;
				tempr=wr*data[j]-wi*data[j+1];
				tempi=wr*data[j+1]+wi*data[j];
				data[j]=data[i]-tempr;
				data[j+1]=data[i+1]-tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;
	}
}
#undef SWAP

void apply_fft_on_image(complex_t *image_complex, unsigned int width, unsigned int height, int isign) {
    unsigned long n = width * height; // Nombre total de pixels (en complexes)
    float *data = (float *)malloc(2 * n * sizeof(float)); // Tableau pour stocker les données réelles et imaginaires

    // Remplir le tableau `data[]` avec les données de `image_complex`
    for (unsigned int i = 0; i < n; i++) {
        data[2 * i] = image_complex[i].Re;   // Partie réelle
        data[2 * i + 1] = image_complex[i].Im; // Partie imaginaire
    }

    // Appliquer la FFT sur le tableau `data`
    four1(data, n, isign);

    // Remettre les résultats dans `image_complex`
    for (unsigned int i = 0; i < n; i++) {
        image_complex[i].Re = data[2 * i];     // Partie réelle après FFT
        image_complex[i].Im = data[2 * i + 1]; // Partie imaginaire après FFT
    }

    // Libérer la mémoire allouée pour `data`
    free(data);
}
