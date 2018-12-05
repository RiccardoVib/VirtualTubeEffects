/*
  ==============================================================================

    DelayLine.cpp
    Created: 5 Dec 2018 3:29:32pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#include "DelayLine.h"

#include <iostream>
#include <math.h>


void DelayLine::suspend(){
    
    memset(delayBufferLeft_, 0, delayBufferLength_*sizeof(double));
    memset(delayBufferRight_, 0, delayBufferLength_*sizeof(double));
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

