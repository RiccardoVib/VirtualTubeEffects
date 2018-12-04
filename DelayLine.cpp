//
//  DelayLine.cpp
//  VirtualTubeDelay
//
//  Created by Riccardo Simionato on 03/10/18.
//
//

#include "DelayLine.h"
#include <iostream>
#include <math.h>

void DelayLine::setDelayL(double samples){
    
    rptrLeft = wptrLeft - (long)samples;
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    fracDelaySamplesLeft = samples - (long)samples;
}

void DelayLine::setDelayR(double samples){
    
    rptrRight = wptrRight - (long)samples;
    while (rptrRight < delayBufferRight_) { rptrRight += delayBufferLength_; }
    
    fracDelaySamplesRight = samples - (long)samples;
}


void DelayLine::setDelay_Ref_L(double samples){
    
    rptrLeft_Ref = wptrLeft_Ref - (long)samples;
    while (rptrLeft_Ref < delayBufferLeftRef_) { rptrLeft_Ref += delayBufferLengthRef_; }
    
    fracDelaySamplesLeft_Ref = samples - (long)samples;
}

void DelayLine::setDelay_Ref_R(double samples){
    
    rptrRight_Ref = wptrRight_Ref - (long)samples;
    while (rptrRight_Ref < delayBufferRightRef_) { rptrRight_Ref += delayBufferLengthRef_; }
    
    fracDelaySamplesRight_Ref = samples - (long)samples;
}


void DelayLine::suspend(){
    
     memset(delayBufferLeft_, 0, delayBufferLength_*sizeof(double));
     memset(delayBufferRight_, 0, delayBufferLength_*sizeof(double));
}


double DelayLine::delayLineL(double x)
{
    
    double y;
    
    double *rpi = (rptrLeft+1);
    if (rpi - delayBufferLeft_ >= delayBufferLength_) { rpi -= delayBufferLength_; }
    
    y = (1 - fracDelaySamplesLeft) * *rptrLeft + fracDelaySamplesLeft * *(rpi) - y_1_L * (1 - fracDelaySamplesLeft);
    
    y_1_L = y;
    rptrLeft += 1;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLineR(double x)
{
    
    double y;
    
    double *rpi = (rptrRight+1);
    if (rpi - delayBufferRight_ >= delayBufferLength_) { rpi -= delayBufferLength_; }
    
    y = (1 - fracDelaySamplesRight) * *rptrRight + fracDelaySamplesRight * *(rpi) - y_1_R * (1 - fracDelaySamplesRight);
    y_1_R = y;
    
    rptrRight += 1;
    
    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLine_Ref_L(double x)
{
    
    double y;
    
    *wptrLeft_Ref++ = x;
    
    double *rpi = (rptrLeft_Ref+1);
    if (rpi - delayBufferLeftRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesLeft_Ref) * *rptrLeft_Ref + fracDelaySamplesLeft_Ref * *(rpi) - y_1_L_ref * (1 - fracDelaySamplesLeft_Ref);
    
    y_1_L_ref = y;
    
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;
    
}

double DelayLine::delayLine_Ref_R(double x)
{
    
    double y;
    
    double *rpi = (rptrRight_Ref+1);
    if (rpi - delayBufferRightRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesRight_Ref) * *rptrRight_Ref + fracDelaySamplesRight_Ref * *(rpi) - y_1_R_ref * (1 - fracDelaySamplesRight_Ref);
    
    y_1_R_ref = y;
    
    rptrRight_Ref += 1;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    return y;
}




double DelayLine::delayLine_Vibrato_L(double x, double samples){
    
    double y;
    
    rptrLeft = wptrLeft - (long)samples;// - 3;// + delayBufferLength_ - 3;
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    double fraction = samples - (long)samples;

    y = hermiteInterpolation(rptrLeft, x, delayBufferLeft_, delayBufferLength_, fraction);
    
    *wptrLeft++ = x;
    
    rptrLeft += 1;
    
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    
    
    return y;
    
}


double DelayLine::delayLine_Vibrato_R(double x, double samples){
    
    double y;
    
    rptrRight = wptrRight - (long)samples;// - 3;// + delayBufferLength_ - 3;
    while (rptrRight < delayBufferRight_) { rptrRight += delayBufferLength_; }
    
    double fraction = samples - (long)samples;
    
    y = hermiteInterpolation(rptrRight, x, delayBufferRight_, delayBufferLength_, fraction);
    
    *wptrRight++ = x;
    
    rptrRight += 1;
    
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }

    return y;
    
}


double DelayLine::delayLine_Vibrato_Ref_L(double x, double samples){
    
    double y;
    
    rptrLeft_Ref = wptrLeft_Ref - (long)samples;// - 3;// + delayBufferLength_ - 3;
    while (rptrLeft_Ref < delayBufferLeftRef_) { rptrLeft_Ref += delayBufferLengthRef_; }
    
    double fraction = samples - (long)samples;
    
    y = hermiteInterpolation(rptrLeft_Ref, x, delayBufferLeftRef_, delayBufferLengthRef_, fraction);
    
    *wptrLeft_Ref++ = x;
    
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }

    
    return y;
    
}


double DelayLine::delayLine_Vibrato_Ref_R(double x, double samples){
    
    double y;
    
    rptrRight_Ref = wptrRight_Ref - (long)samples;// - 3;// + delayBufferLength_ - 3;
    while (rptrRight_Ref < delayBufferRightRef_) { rptrRight_Ref += delayBufferLengthRef_; }
    
    double fraction = samples - (long)samples;
    
    y = hermiteInterpolation(rptrRight_Ref, x, delayBufferRightRef_, delayBufferLengthRef_, fraction);
    
    *wptrRight_Ref++ = x;
    
    rptrRight_Ref += 1;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    
    return y;
    
}

