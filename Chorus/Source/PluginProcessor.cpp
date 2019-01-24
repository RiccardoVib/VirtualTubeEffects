/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeChorusAudioProcessor::VirtualTubeChorusAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true)
                    .withOutput ("Output", AudioChannelSet::stereo(), true)), parameters (*this, nullptr)

{
    parameters.createAndAddParameter("delayTimeLeft_", "delayTimeLeft", "delayTimeLeft", NormalisableRange<float>(20.0f,30.0f), 20.0f, nullptr, nullptr);
    parameters.createAndAddParameter("delayTimeRight_", "delayTimeRight", "delayTimeRight", NormalisableRange<float>(20.0f,30.0f), 20.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(-128.0f, 9.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(-128.0f, 9.0f), 0.0, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2f,2.5f), 1.2f, nullptr, nullptr);
    parameters.createAndAddParameter("delayTimeRefLeft_", "delayTimeRefLeft", "delayTimeRefLeft", NormalisableRange<float>(20.0f,30.0f), 20.0f, nullptr, nullptr);
    parameters.createAndAddParameter("delayTimeRefRight_", "delayTimeRefRight", "delayTimeRefRight", NormalisableRange<float>(20.0f,30.0f), 20.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(-128.0f, 19.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight", "gainRefRight", NormalisableRange<float>(-128.0f, 19.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("width_", "width", "width", NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("frequencyRate_", "frequencyRate", "frequencyRate", NormalisableRange<float>(0.1f, 3.0f), 0.1f, nullptr, nullptr);
    parameters.createAndAddParameter("feedback_", "feedback", "feedback", NormalisableRange<float>(0.0f, 0.9f), 0.0f, nullptr, nullptr);
    
    
    parameters.state = ValueTree("SavedParams");
    
    delayTimeLeft_ = parameters.getRawParameterValue ("delayTimeLeft_");
    delayTimeRight_ = parameters.getRawParameterValue ("delayTimeRight_");
    gainLeft_ = parameters.getRawParameterValue ("gainLeft_");
    gainRight_ = parameters.getRawParameterValue ("gainRight_");
    dryWetMix_ = parameters.getRawParameterValue ("dryWetMix_");
    tubeSize_ = parameters.getRawParameterValue ("tubeSize_");
    delayTimeRefLeft_ = parameters.getRawParameterValue ("delayTimeRefLeft_");
    delayTimeRefRight_ = parameters.getRawParameterValue ("delayTimeRefRight_");
    gainRefLeft_ = parameters.getRawParameterValue ("gainRefLeft_");
    gainRefRight_ = parameters.getRawParameterValue ("gainRefRight_");
    width_ = parameters.getRawParameterValue ("width_");
    frequencyRate_ = parameters.getRawParameterValue ("frequencyRate_");
    feedback_ = parameters.getRawParameterValue ("feedback_");
    
}

VirtualTubeChorusAudioProcessor::~VirtualTubeChorusAudioProcessor()
{
}

//==============================================================================
const String VirtualTubeChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualTubeChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VirtualTubeChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualTubeChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualTubeChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualTubeChorusAudioProcessor::setCurrentProgram (int index)
{
}

const String VirtualTubeChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void VirtualTubeChorusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VirtualTubeChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
        mDelayLine_ref[channel].suspend();
    }
    
    // Set default values:
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        previousMaxDelaySamples[channel] = maxDelaySamples[channel] = 441.0f;
        previousMaxDelaySamplesRef[channel] = maxDelaySamplesRef[channel] = 441.0f;
        previousGain[channel] = 0.0f;
        previousGainRef[channel] = 0.0f;
   
        previousWidth[channel] = currentWidth[channel] = 0.0f;
        
        mDelayLine[channel].setSampleRate(getSampleRate());
        mFilter[channel].setSampleRate(getSampleRate());
        
        mDelayLine_ref[channel].setSampleRate(getSampleRate());
        mFilter_ref[channel].setSampleRate(getSampleRate());
        
        mDelayLine[channel].initialize();
        mDelayLine_ref[channel].initialize();
    }
}

void VirtualTubeChorusAudioProcessor::releaseResources()
{
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
        mDelayLine_ref[channel].suspend();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualTubeChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VirtualTubeChorusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    int numSamples = buffer.getNumSamples();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    float width = *width_; //Width = %Delay
    float feedback = *feedback_;
    float frequency = *frequencyRate_;// Vibrato: base 2 - 14 Hz  Flanger: 0.1 Hz to 10 Hz//Chorus: 0.1 to 3 Hz.
    float sampleRate = static_cast<float>(getSampleRate());
    float inverseSampleRate = 1./sampleRate;
    float wetValue_ = *dryWetMix_;

    rad = floor(*tubeSize_*10.0f - 12.0f);
    
    // Vibrato: basic delay 1-10 ms, Flanger: basic delay 1-10 ms, Chorus: 20 to 30 ms
    currentGain[0] = powf(10.0f, *gainLeft_ / 20.0f);
    currentGain[1] = powf(10.0f, *gainRight_ / 20.0f);
    currentGainRef[0] = powf(10.0f, *gainRefLeft_ / 20.0f);
    currentGainRef[1] = powf(10.0f, *gainRefRight_ / 20.0f);
    
    currentWidth[0] = currentWidth[1] = width;
    
    applyGainAndWidth(numSamples);
    
    delayMilli[0] = *delayTimeLeft_;
    delayMilli[1] = *delayTimeRight_;
    delayMilliRef[0] = *delayTimeRefLeft_;
    delayMilliRef[1] = *delayTimeRefRight_;
    
    for (int channel = 0; channel < 2; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        
        maxDelaySamples[channel] = (delayMilli[channel])*(sampleRate/1000.0f); // basic delay in # samples
        maxDelaySamplesRef[channel] = (delayMilliRef[channel])*(sampleRate/1000.0f);
        
        applyFilterDelay(numSamples, channel);
        
        for (int i = 0; i < numSamples; ++i)
        {
            process(channel);
            
            const double in = channelData[i];
       
            currentDelay[channel] = interpolatedMaxDelaySamples[channel]/2 * ((1 + sin(2.0f * M_PI * ph[channel]) * interpolatedWidth[channel]));
            currentDelayRef[channel] = interpolatedMaxDelaySamplesRef[channel]/2 * ((1 + sin(2.0f * M_PI * ph[channel]) * interpolatedWidth[channel]));
        
            currentLength[channel] = (currentDelay[channel]*345.0f)/sampleRate;
            currentLengthRef[channel] = (currentDelayRef[channel]*345.0f)/sampleRate;
        
            //computing filter coefficients
            mFilter[channel].setValues(currentLength[channel], rad);
            mFilter[channel].getCalculatedCoefficients();
            
            //computing filter coefficients (reflection)
            mFilter_ref[channel].setValues(currentLengthRef[channel], rad);
            mFilter_ref[channel].getCalculatedCoefficients();
            
            double x = computeOutFilter(in, channel);
        
            double x_fin = computeOutReflectionFilter(in, rad, channel);
        
            double out1 = currentGain[channel] * mDelayLine[channel].delayLine(x * feedback, static_cast<double>(currentDelay[channel]), channel);
            
            double out2 = currentGainRef[channel] * mDelayLine_ref[channel].delayLine(x_fin * feedback, static_cast<double>(currentDelayRef[channel]), channel);
            
            double out = in + (wetValue_) * (out1 + out2);
            
            channelData[i] = out;
      
            interpolatedGain[channel] += incrementGain[channel];
            interpolatedGainRef[channel] += incrementGainRef[channel];
            
            interpolatedWidth[channel] += incrementWidth[channel];
        
            interpolatedMaxDelaySamples[channel] += incrementMaxDelaySamples[channel];
            interpolatedMaxDelaySamplesRef[channel] += incrementMaxDelaySamplesRef[channel];
        
            ph[channel] += frequency*inverseSampleRate;
            if(ph[channel] >= 1.0){
                ph[channel] -= 1.0;
            }
        }
    }
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

void VirtualTubeChorusAudioProcessor::process(int channel) {
    
    i_0 = ptr[channel]%7;       //->6
    i_1 = (ptr[channel] + 1)%7; //->0
    i_2 = (ptr[channel] + 2)%7; //->1
    i_3 = (ptr[channel] + 3)%7; //->2
    i_4 = (ptr[channel] + 4)%7; //->3
    i_5 = (ptr[channel] + 5)%7; //->4
    i_6 = (ptr[channel] + 6)%7; //->5
    
    if (--ptr[channel] < 0) { ptr[channel] += 7; }
    
    j_0 = ptr2[channel]%4;       //->3
    j_1 = (ptr2[channel] + 1)%4; //->0
    j_2 = (ptr2[channel] + 2)%4; //->1
    j_3 = (ptr2[channel] + 3)%4; //->2
    
    if (--ptr2[channel] < 0) { ptr2[channel] += 4; }
}

double VirtualTubeChorusAudioProcessor::computeOutFilter(double input, int channel){
    
    double in = input;
    double out;
    
    bufIn[channel][i_0] = in;
    
    bufOut[channel][i_0] = bufIn[channel][i_0] * mFilter[channel].b0f + bufIn[channel][i_1] * mFilter[channel].b1f + bufIn[channel][i_2] * mFilter[channel].b2f + bufIn[channel][i_3] * mFilter[channel].b3f + bufIn[channel][i_4] * mFilter[channel].b4f + bufIn[channel][i_5] * mFilter[channel].b5f + bufIn[channel][i_6] * mFilter[channel].b6f - bufOut[channel][i_1] * mFilter[channel].a1f - bufOut[channel][i_2] * mFilter[channel].a2f - bufOut[channel][i_3] * mFilter[channel].a3f - bufOut[channel][i_4] * mFilter[channel].a4f - bufOut[channel][i_5] * mFilter[channel].a5f - bufOut[channel][i_6] * mFilter[channel].a6f;
    
    out = bufOut[channel][i_0];
    
    return out;
    
}

double VirtualTubeChorusAudioProcessor::computeOutReflectionFilter(double input, int rad, int channel){
    
    double in = input;
    double out;
    
    bufIn_Ref[channel][i_0] = in;
    
    bufOut_Ref[channel][i_0] = bufIn_Ref[channel][i_0] * mFilter_ref[channel].b0f + bufIn_Ref[channel][i_1] * mFilter_ref[channel].b1f + bufIn_Ref[channel][i_2] * mFilter_ref[channel].b2f + bufIn_Ref[channel][i_3] * mFilter_ref[channel].b3f + bufIn_Ref[channel][i_4] * mFilter_ref[channel].b4f + bufIn_Ref[channel][i_5] * mFilter_ref[channel].b5f + bufIn_Ref[channel][i_6] * mFilter_ref[channel].b6f - bufOut_Ref[channel][i_1] * mFilter_ref[channel].a1f - bufOut_Ref[channel][i_2] * mFilter_ref[channel].a2f - bufOut_Ref[channel][i_3] * mFilter_ref[channel].a3f - bufOut_Ref[channel][i_4] * mFilter_ref[channel].a4f - bufOut_Ref[channel][i_5] * mFilter_ref[channel].a5f - bufOut_Ref[channel][i_6] * mFilter_ref[channel].a6f;
    
    bufIn_Fin[channel][j_0] = bufOut_Ref[channel][i_0];
    
    bufOut_Fin[channel][j_0] = bufIn_Fin[channel][j_0] * b_Ref[rad][0] + bufIn_Fin[channel][j_1] * b_Ref[rad][1] + bufIn_Fin[channel][j_2] * b_Ref[rad][2] + bufIn_Fin[channel][j_3] * b_Ref[rad][3] - bufOut_Fin[channel][j_1] * a_Ref[rad][0] - bufOut_Fin[channel][j_2] * a_Ref[rad][1] - bufOut_Fin[channel][j_3] * a_Ref[rad][2];
    
    out = bufOut_Fin[channel][j_0];
    
    return out;
    
}

void VirtualTubeChorusAudioProcessor::applyFilterDelay(int numSamples, int channel){

    //interpolating delays
    incrementMaxDelaySamples[channel] = (maxDelaySamples[channel] - previousMaxDelaySamples[channel]) / (double) numSamples;
    interpolatedMaxDelaySamples[channel] = previousMaxDelaySamples[channel];
    
    previousMaxDelaySamples[channel] = maxDelaySamples[channel];
    
    incrementMaxDelaySamplesRef[channel] = (maxDelaySamplesRef[channel] - previousMaxDelaySamplesRef[channel]) / (double) numSamples;
    interpolatedMaxDelaySamplesRef[channel] = previousMaxDelaySamplesRef[channel];
    
    previousMaxDelaySamplesRef[channel] = maxDelaySamplesRef[channel];
    
}


void VirtualTubeChorusAudioProcessor::applyGainAndWidth(int numSamples){
    
    for(int i = 0; i < 2; ++i)
    {
        incrementGain[i] = (currentGain[i] - previousGain[i]) / (double) numSamples;
        interpolatedGain[i] = previousGain[i];
        
        previousGain[i] = currentGain[i];
        
        incrementGainRef[i] = (currentGainRef[i] - previousGainRef[i]) / (double) numSamples;
        interpolatedGainRef[i] = previousGainRef[i];
        
        previousGainRef[i] = currentGainRef[i];
        
        //
        incrementWidth[i] = (currentWidth[i] - previousWidth[i]) / (double) numSamples;
        interpolatedWidth[i] = previousWidth[i];
        
        previousWidth[i] = currentWidth[i];
        
        
    }
}


//==============================================================================
bool VirtualTubeChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VirtualTubeChorusAudioProcessor::createEditor()
{
    return new VirtualTubeChorusAudioProcessorEditor (*this);
}

//==============================================================================
void VirtualTubeChorusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualTubeChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr){
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.state = ValueTree::fromXml(*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualTubeChorusAudioProcessor();
}
