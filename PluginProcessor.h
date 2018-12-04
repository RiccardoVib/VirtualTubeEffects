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

class VirtualTubeEffectsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VirtualTubeEffectsAudioProcessor();
    ~VirtualTubeEffectsAudioProcessor();

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
    float* dryWetMix_ = nullptr; // Mix level of original and delayed signal (0-1)
    float* tubeSize_ = nullptr; // Size of the tube (1.2-2.5 cm)
    
    float* tubeEndLeft_ = nullptr; // Tube length in m
    float* tubeEndRight_ = nullptr;
    float* gainRefLeft_ = nullptr; // Gain
    float* gainRefRight_ = nullptr;
    
    
    float* enabledReflection_ = nullptr;
    float* enabledVibrato_ = nullptr;
    float* enabledFlanger_ = nullptr;
    float* enabledChorus_ = nullptr;
    
    int rad;
    float leng_L;
    float delayMilli_L;
    float delaySamples_L;
    
    float leng_R;
    float delayMilli_R;
    float delaySamples_R;
    
    double lengRef_L;
    double delayMilliRef_L;
    double delaySamplesRef_L;
    
    double lengRef_R;
    double delayMilliRef_R;
    double delaySamplesRef_R;
    
    Filter mFilter;
    DelayLine mDelayLine;
    
    //Vibrato
    
    float* frequencyRate_;
    float* width_;
    float* feedback_;
    
    AudioProcessorValueTreeState parameters;
    
    void process();
    double computeOutFilter_L(double input);
    double computeOutFilter_R(double input);
    double computeOutReflectionFilter_L(double input);
    double computeOutReflectionFilter_R(double input);

private:

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
     // Circular buffer variables for implementing delay
    AudioBuffer<float> delayBufferLeft_2, delayBufferRight_2, delayBufferLeftRef_2, delayBufferRightRef_2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeEffectsAudioProcessor)
};
