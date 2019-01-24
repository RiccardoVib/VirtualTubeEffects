/*
  ==============================================================================

    DelayLine.h
    Created: 5 Dec 2018 3:57:36pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#pragma once

#include <math.h>
#include <tgmath.h>

class DelayLine {
public:
    
    DelayLine():
    fracDelaySamples{0.0, 0.0}
    {initialize();};
    
    
    ~DelayLine(){
        
        for(int i = 0; i < 2; ++i)
        {
            delete[] delayBuffer[i];
            
        }
    };
    
    void initialize(){
        
        delayBufferLength_ = static_cast<int>(ceilf(11.0f * mSampleRate/1000.0f));
        
        for(int i = 0; i < 2; ++i)
        {
            delayBuffer[i] = new double[delayBufferLength_];
            
            rptr[i] = delayBuffer[i]; // read ptr
            wptr[i] = delayBuffer[i]; // write ptr
            
        }
        
    }
    
    inline void suspend(){
        for(int i = 0; i < 2; ++i)
        {
            memset(delayBuffer[i], 0, delayBufferLength_*sizeof(double));
        }
    }
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    double delayLine(double x, double samples, int channel);
    double hermiteInterpolation(double* pointer, double* buffer, int bufferLength, double frac);
    
private:
    
    double mSampleRate;
    double fracDelaySamples[2];
    int delayBufferLength_;
    double *delayBuffer[2];
    double *rptr[2]; // read ptr
    double *wptr[2]; // write ptr
};
