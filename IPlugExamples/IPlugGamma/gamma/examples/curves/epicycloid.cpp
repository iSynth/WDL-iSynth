/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Example:		Curve / Epicycloid
	Description:	An epicycloid is the trace of a fixed point on a small 
					circle that rolls around a larger circle. This is a primitive 
					form of 2D additive synthesis using complex oscillators.
*/

#include "../examples.h"

int main(int argc, char* argv[]){

	const int NP=256;				// Number of points in curve
	const int N1=31, N2=N1*N1;		// Size of graph
	float pixels[N2];				// Accumulation buffer
	
	// Use two complex oscillators as harmonics of curve
	Quadra<> qua1(1./NP), qua2;

	// Plot several harmonics summed with fundamental
	for(int j=1; j<8; ++j){

		printf("\ne^iw + e^%diw\n\n", j);
		mem::zero(pixels, N2);
		
		qua2.freq(j/(float)NP);			// Harmonic rotating in tandem with fundamental
		qua2.amp(1./j);					// Amplitude is 1/f to give equal energy
		float r = 0.99/(1. + 1./j);		// Factor to normalize sum of partials

		for(int i=0; i<NP; ++i){
			Complex<> c = qua1() + qua2();
			int ix = posToInd( c.r * r, N1);	// map real component to x
			int iy = posToInd(-c.i * r, N1);	// map imag component to y
			pixels[iy*N1 + ix] += 0.1;
		}

		print2D(pixels, N1, N1);
		printf("\n");
	}

	return 0;
}
