/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#include "DelayLine.h"

//==============================================================================
/**
*/

static double bufOut_L[7];
static double bufIn_L[7];

static double bufOut_R[7];
static double bufIn_R[7];

static double bufOut_Ref_L[7];
static double bufIn_Ref_L[7];

static double bufOut_Ref_R[7];
static double bufIn_Ref_R[7];

static double bufOut_Fin_L[4];
static double bufIn_Fin_L[4];

static double bufOut_Fin_R[4];
static double bufIn_Fin_R[4];


class VirtualTubeVibratoAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VirtualTubeVibratoAudioProcessor();
    ~VirtualTubeVibratoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Adjustable parameters:
    float* tubeLengthLeft_ = nullptr; // Tube length in m
    float* tubeLengthRight_ = nullptr;
    float* gainLeft_ = nullptr; // Gain
    float* gainRight_ = nullptr;
    float* tubeSize_ = nullptr; // Size of the tube (1.2-2.5 cm)
    
    float* tubeEndLeft_ = nullptr; // Tube length in m
    float* tubeEndRight_ = nullptr;
    float* gainRefLeft_ = nullptr; // Gain
    float* gainRefRight_ = nullptr;
    
    float* frequencyRate_ = nullptr;
    float* width_ = nullptr;
    
    int rad;
    float leng_L;
    float delayMilli_L;
    float delaySamples_L;
    
    float leng_R;
    float delayMilli_R;
    float delaySamples_R;
    
    float lengRef_L;
    float delayMilliRef_L;
    float delaySamplesRef_L;
    
    float lengRef_R;
    float delayMilliRef_R;
    float delaySamplesRef_R;
    
    Filter mFilter;
    DelayLine mDelayLine;
    
    AudioProcessorValueTreeState parameters;
    
    void process();
    double computeOutFilter_L(double input);
    double computeOutFilter_R(double input);
    double computeOutReflectionFilter_L(double input);
    double computeOutReflectionFilter_R(double input);
    void applyGain(int numSamples);
    void applyFilterDelay_L(int numSamples);
    void applyFilterDelay_R(int numSamples);

private:
    
    float maxDelaySamples_L;
    float maxDelaySamples_R;
    float maxDelaySamplesRef_L;
    float maxDelaySamplesRef_R;
    
    float currentGain_L;
    float currentGain_R;
    float currentGainRef_L;
    float currentGainRef_R;
    
    float previousGain_L;
    float interpolatedGain_L;
    float incrementGain_L;
    
    float previousGain_R;
    float interpolatedGain_R;
    float incrementGain_R;
    
    float previousGainRef_L;
    float interpolatedGainRef_L;
    float incrementGainRef_L;
    
    float previousGainRef_R;
    float interpolatedGainRef_R;
    float incrementGainRef_R;
    
    float previousMaxDelaySamples_L;
    float interpolatedMaxDelaySamples_L;
    float incrementMaxDelaySamples_L;
    
    float previousMaxDelaySamples_R;
    float interpolatedMaxDelaySamples_R;
    float incrementMaxDelaySamples_R;
    
    float previousMaxDelaySamplesRef_L;
    float interpolatedMaxDelaySamplesRef_L;
    float incrementMaxDelaySamplesRef_L;
    
    float previousMaxDelaySamplesRef_R;
    float interpolatedMaxDelaySamplesRef_R;
    float incrementMaxDelaySamplesRef_R;
    
    float tubeLengthLeft;
    float tubeLengthRight;
    float tubeEndLeft;
    float tubeEndRight;
    
    float previousTubeLength_L;
    float interpolatedTubeLength_L;
    float incrementTubeLength_L;
    
    float previousTubeLength_R;
    float interpolatedTubeLength_R;
    float incrementTubeLength_R;
    
    float previousTubeEnd_L;
    float interpolatedTubeEnd_L;
    float incrementTubeEnd_L;
    
    float previousTubeEnd_R;
    float interpolatedTubeEnd_R;
    float incrementTubeEnd_R;
    
    int ptr;
    int ptr2;
    
    int i_0;
    int i_1;
    int i_2;
    int i_3;
    int i_4;
    int i_5;
    int i_6;
    
    int j_0;
    int j_1;
    int j_2;
    int j_3;
    
    int delayBufferLength_;
    int delayBufferLengthRef_;
    float ph;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeVibratoAudioProcessor)
};
