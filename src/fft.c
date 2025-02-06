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

void apply_fft_2d(C_image *complex_image, int isign) {
    unsigned int width = complex_image->width;
    unsigned int height = complex_image->height;
    float *data = (float *)malloc(2 * width * sizeof(float));

    // FFT sur chaque ligne
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            data[2 * x] = complex_image->data[y * width + x].Re;
            data[2 * x + 1] = complex_image->data[y * width + x].Im;
        }

        // FFT 1D sur la ligne
        four1(data - 1, width, isign);

        for (unsigned int x = 0; x < width; x++) {
            complex_image->data[y * width + x].Re = data[2 * x];
            complex_image->data[y * width + x].Im = data[2 * x + 1];
        }
    }

    // FFT sur chaque colonne
    float *colData = (float *)malloc(2 * height * sizeof(float));

    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            colData[2 * y] = complex_image->data[y * width + x].Re;
            colData[2 * y + 1] = complex_image->data[y * width + x].Im;
        }

        // FFT 1D sur la colonne
        four1(colData - 1, height, isign);

        for (unsigned int y = 0; y < height; y++) {
            complex_image->data[y * width + x].Re = colData[2 * y];
            complex_image->data[y * width + x].Im = colData[2 * y + 1];
        }
    }

    free(data);
    free(colData);
}