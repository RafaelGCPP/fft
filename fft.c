#include <complex.h>
#include <math.h>
#include <stdio.h>
#include "fft.h"


void precompute_twiddle_factors(float *twiddle, int n) {
    float complex* twd=(float complex *) twiddle;
    for (int j = 0; j < n/2; j++) 
        twd[j] = cexp(-2 * M_PI * I * j / n) ;
    
}

void fft(float *data, float *twiddle, int n, bool inverse) {
    float complex* cdata=(float complex *) data;
    float complex* twd=(float complex *) twiddle;

    // Bit-reverse the input data

    for (int i = 1, j=0; i < n - 1; i++) {
        int k = n >> 1;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        j += k;
        if (i < j) {
            float complex tmp=cdata[i];
            cdata[i]=cdata[j];
            cdata[j]=tmp;
        }
    }

    if (inverse)
        for (int i=0; i<n; i++) {
            cdata[i]=conj(cdata[i])/sqrt(n);
        }

    // Perform the butterfly operations
    
    for (int k=0, stride = 1, tw_index=n>>1; stride < n; k++, stride <<= 1, tw_index>>=1) {
        int jmax=n-stride;
        for (int j = 0; j < jmax; j+= (stride<<1)) {
            for (int i=0;i<stride;i++) {   
                complex float a, b, w;                
                int index = j + i ;  
                w=twd[i*tw_index] ;
                a = cdata[index];
                b = cdata[index + stride];
                b = b * w;
                cdata[index] = a + b;
                cdata[index + stride] = a - b;
            }
        }
    }

    if (inverse)
        for (int i=0; i<n; i++) 
            cdata[i]=conj(cdata[i])/sqrt(n);
}

void rfft(float data[], float c_real[], float c_imag[], int n, bool inverse) {



}