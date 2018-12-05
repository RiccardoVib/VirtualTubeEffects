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
#include <vector>

class DelayLine {
public:
    
    DelayLine():
    y_1_L(0.0),
    y_1_R(0.0),
    y_1_L_ref(0.0),
    y_1_R_ref(0.0),
    fracDelaySamplesLeft(0.0),
    fracDelaySamplesRight(0.0),
    fracDelaySamplesLeft_Ref(0.0),
    fracDelaySamplesRight_Ref(0.0){};
    ~DelayLine(){};
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    inline double hermiteInterpolation(double* pointer, double x, double* buffer, int bufferLenght, double frac){
        
        // Hermite polynomial interpolation
        // 4-point, 3rd-order Hermite (x-form)
        static double c0, c1, c2, c3;
        double y;
        double *y_1 = (pointer - 1);
        double *y_2 = (pointer - 2);
        double *y_3 = (pointer - 3);
        
        if (y_1 < buffer) { y_1 += bufferLenght; }
        if (y_2 < buffer) { y_2 += bufferLenght; }
        if (y_3 < buffer) { y_3 += bufferLenght; }
        
        c0 = *y_1;
        c1 = (1.0/2.0)*(*y_2 - *pointer);
        c2 = (*pointer - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
        c3 = (1.0/2.0)*(*y_3- *pointer) + (3.0/2.0)*(*y_1 - *y_2);
        
        return y = ((c3*x+c2)*x+c1)*frac+c0;
        
    }
    
    void suspend(); // flush buffers
    
    void initialize(){
        
        delayBufferLength_ = 6*mSampleRate;//3835;//(int)(30/0.345)*44.1 + 1;
        delayBufferLengthRef_ = 6*mSampleRate;//5114;//(int)(40/0.345)*44.1 + 1;
        
        delayBufferLeft_ = new double[delayBufferLength_];
        delayBufferRight_ = new double[delayBufferLength_];
        
        delayBufferLeftRef_ = new double[delayBufferLengthRef_];
        delayBufferRightRef_ = new double[delayBufferLengthRef_];
        
        rptrLeft = delayBufferLeft_; // read ptr
        wptrLeft = delayBufferLeft_; // write ptr
        
        rptrRight = delayBufferRight_; // read ptr
        wptrRight = delayBufferRight_; // write ptr
        
        rptrLeft_Ref = delayBufferLeftRef_;
        rptrRight_Ref = delayBufferRightRef_;
        
        wptrLeft_Ref = delayBufferLeftRef_;
        wptrRight_Ref = delayBufferRightRef_;
    }
    
    double delayLine_Flanger_L(double input, double samples);
    double delayLine_Flanger_R(double input, double samples);
    
    double delayLine_Flanger_Ref_L(double x, double samples);
    double delayLine_Flanger_Ref_R(double x, double samples);
    
private:
    
    double mSampleRate;
    double y_1_L;
    double y_1_R;
    double y_1_L_ref;
    double y_1_R_ref;
    double fracDelaySamplesLeft;
    double fracDelaySamplesRight;
    
    double fracDelaySamplesLeft_Ref;
    double fracDelaySamplesRight_Ref;
        
    int delayBufferLength_;
    int delayBufferLengthRef_;
    
    double *delayBufferLeft_;
    double *delayBufferRight_;
    
    double *delayBufferLeftRef_;
    double *delayBufferRightRef_;
    
    double *rptrLeft; // read ptr
    double *wptrLeft; // write ptr
    
    double *rptrRight; // read ptr
    double *wptrRight; // write ptr
    
    double *rptrLeft_Ref;
    double *rptrRight_Ref;
    
    double *wptrLeft_Ref;
    double *wptrRight_Ref;
};
