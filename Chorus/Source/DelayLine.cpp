/*
  ==============================================================================

    DelayLine.cpp
    Created: 5 Dec 2018 4:28:27pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#include "DelayLine.h"
#include <math.h>


double DelayLine::hermiteInterpolation(double* pointer, double* buffer, int bufferLength, double frac){
    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    double y;
    double *y_1 = (pointer - 1);
    double *y_2 = (pointer - 2);
    double *y_3 = (pointer - 3);
    
    if (y_1 < buffer) { y_1 += bufferLength; }
    if (y_2 < buffer) { y_2 += bufferLength; }
    if (y_3 < buffer) { y_3 += bufferLength; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *pointer);
    c2 = (*pointer - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3 - *pointer) + (3.0/2.0)*(*y_1 - *y_2);
    
    return y = ((c3*frac+c2)*frac+c1)*frac+c0;
    
}


double DelayLine::delayLine(double x, double samples, int channel){
    
    rptr[channel] = wptr[channel] - (long)samples;
    while (rptr[channel] < delayBuffer[channel]) { rptr[channel] += delayBufferLength_; }
    
    fracDelaySamples[channel] = samples - (long)samples;
    
    double y = hermiteInterpolation(rptr[channel], delayBuffer[channel], delayBufferLength_, fracDelaySamples[channel]);
    
    rptr[channel] += 1;
    
    *wptr[channel]++ = x;
    
    if (rptr[channel] - delayBuffer[channel] >= delayBufferLength_) { rptr[channel] -= delayBufferLength_; }
    if (wptr[channel] - delayBuffer[channel] >= delayBufferLength_) { wptr[channel] -= delayBufferLength_; }
    
    return y;
    
}
