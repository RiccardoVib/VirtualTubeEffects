/*
  ==============================================================================

    Filter.h
    Created: 5 Dec 2018 3:57:23pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#pragma once
#include <math.h>
#include <tgmath.h>

const double mPI = 2*acos(0.0);

//propagation filter parameters values

const double f12 = -42.8571428571429; const double f12LP = 100;
const double g12 = 0.00285714285714286; const double f212 = 785.714285714286;
const double g23 = 0.00500000000000000; const double f23LP = 133.333333333333;
const double fc1_0 = 1200; const double fcLP_0 = 9500; const double fc2_0 = 1500;
const double fc1_1 = 900; const double fcLP_1 = 10200; const double fc2_1 = 7000;


//decrement steps for LP filters
const int fLPValues[36] = {0, 0, 850, 1700, 2700, 3500, 4000, 4500, 4900, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6700, 7000, 7300, 7500, 7700, 7800, 7950, 8050, 8150, 8250, 8350, 8400, 8500, 8550, 8600, 8650, 8690, 8750, 8770, 8900};

const double incValues[36] = {8.5, 8.5, 8.5, 10, 8, 5, 5, 4, 3, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 1, 1.5, 0.5, 1, 1, 1, 0.5, 1, 1.5, 0.5, 0.5, 0.4, 0.6, 1.3, 0};

class Filter {
public:
    
    Filter() :
    
    Q1(0.65000000000000002),
    fcLP(4100.0),
    G1(-8.6499999999999985),
    V1(0.36940264435828352),
    fc1(1470.0),
    G2(-9.9000000000000003),
    V2(0.31988951096913981),
    fc2(1950.0),
    Q2(0.5),
    inc(0.19687440434072259),
    
    K1(0.10201843500792108),
    a1(-1.8124480755856778),
    a2(0.82643833647869547),
    b0(0.39229522156127944),
    b1(-0.66511200112149416),
    b2(0.28680704045323241),
    K2(0.19739200480919947),
    a11(-1.5982791189070777),
    a22(0.63862403548359614),
    b00(0.37114398154063555),
    b11(-0.49755322526799012),
    b22(0.16675416030387299),
    KLP(0.30845914892734089),
    a2LP(0.27932856083050811),
    a1LP(-1.0570308620480446),
    b0LP(0.05557442469561584),
    b1LP(0.11114884939123168),
    b2LP(0.05557442469561584),
    
    a1f(-4.4677580565408004),
    a2f(8.246432752710092),
    a3f(-8.0416864964928578),
    a4f(4.3658701352651246),
    a5f(-1.250157835645624),
    a6f(0.14742497350765946),
    b0f(0.0016473782482660101),
    b1f(-0.0017067348851367849),
    b2f(-0.0026667292888066523),
    b3f(0.0035067498850163384),
    b4f(0.00049099029470241347),
    b5f(-0.0017872423055908145),
    b6f(0.00054113344012696836){};

    
    ~Filter(){};
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    void setValues(double inputLength, double inputSize);
    
    void getCalculatedCoefficients();
    
    inline double setLengt(double lengthInput) {
        return (double)((long)floor(lengthInput*100))/100; };
    
    double a1f;
    double a2f;
    double a3f;
    double a4f;
    double a5f;
    double a6f;
    double b0f;
    double b1f;
    double b2f;
    double b3f;
    double b4f;
    double b5f;
    double b6f;
    
private:
    
    double Q1;
    double fcLP;
    double G1;
    double V1;
    double fc1;
    double G2;
    double V2;
    double fc2;
    double Q2;
    
    double inc;
    
    double K1;
    double a1;
    double a2;
    double b0;
    double b1;
    double b2;
    double K2;
    double a11;
    double a22;
    double b00;
    double b11;
    double b22;
    
    double KLP;
    double a2LP;
    double a1LP;
    double b0LP;
    double b1LP;
    double b2LP;
    
    double mSampleRate;
};