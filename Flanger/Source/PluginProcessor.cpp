/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeFlangerAudioProcessor::VirtualTubeFlangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters (*this, nullptr)
#endif
{
    
    parameters.createAndAddParameter("tubeLengthLeft_", "tubeLengthLeft", "tubeLengthLeft", NormalisableRange<float>(1,4), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeLengthRight_", "tubeLengthRight", "tubeLengthRight", NormalisableRange<float>(1,4), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(0.0, 3.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(0.0, 3.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0, 1.0), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndLeft_", "tubeEndLeft", "tubeEndLeft", NormalisableRange<float>(1.0, 2.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndRight_", "tubeEndRight", "tubeEndRight", NormalisableRange<float>(1.0, 2.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(0.0, 9.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight", "gainRefRight", NormalisableRange<float>(0.0, 9.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("width_", "width", "width", NormalisableRange<float>(0.0, 0.9), 0, nullptr, nullptr);
    parameters.createAndAddParameter("frequencyRate_", "frequencyRate", "frequencyRate", NormalisableRange<float>(0.0, 10.0), 0.0, nullptr, nullptr);
    parameters.createAndAddParameter("feedback_", "feedback", "feedback", NormalisableRange<float>(0.0, 0.9), 0.0, nullptr, nullptr);

    
    parameters.state = ValueTree("SavedParams");
    
    tubeLengthLeft_ = parameters.getRawParameterValue ("tubeLengthLeft_");
    tubeLengthRight_ = parameters.getRawParameterValue ("tubeLengthRight_");
    gainLeft_ = parameters.getRawParameterValue ("gainLeft_");
    gainRight_ = parameters.getRawParameterValue ("gainRight_");
    dryWetMix_ = parameters.getRawParameterValue ("dryWetMix_");
    tubeSize_ = parameters.getRawParameterValue ("tubeSize_");
    tubeEndLeft_ = parameters.getRawParameterValue ("tubeEndLeft_");
    tubeEndRight_ = parameters.getRawParameterValue ("tubeEndRight_");
    gainRefLeft_ = parameters.getRawParameterValue ("gainRefLeft_");
    gainRefRight_ = parameters.getRawParameterValue ("gainRefRight_");
    width_ = parameters.getRawParameterValue ("width_");
    frequencyRate_ = parameters.getRawParameterValue ("frequencyRate_");
    feedback_ = parameters.getRawParameterValue ("feedback_");
    
    //Set default values
    leng_L = 1.0;
    leng_R = 1.0;
    delayMilli_L = 2.8985507246376812;
    delayMilli_R = 2.8985507246376812;
    delaySamples_L = 127.82608695652175;
    delaySamples_R = 127.82608695652175;
    lengRef_L = 3.0;
    lengRef_R = 3.0;
    delayMilliRef_L = 8.695652173913043;
    delayMilliRef_R = 8.695652173913043;
    delaySamplesRef_L = 383.478260869565217;
    delaySamplesRef_R = 383.478260869565217;
    
}

VirtualTubeFlangerAudioProcessor::~VirtualTubeFlangerAudioProcessor()
{
}

//==============================================================================
const String VirtualTubeFlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualTubeFlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeFlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeFlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VirtualTubeFlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualTubeFlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualTubeFlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualTubeFlangerAudioProcessor::setCurrentProgram (int index)
{
}

const String VirtualTubeFlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void VirtualTubeFlangerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VirtualTubeFlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ptr = 0;
    ptr2 = 0;
    
    i_0 = 0;
    i_1 = 0;
    i_2 = 0;
    i_3 = 0;
    i_4 = 0;
    i_5 = 0;
    i_6 = 0;
    
    j_0 = 0;
    j_1 = 0;
    j_2 = 0;
    j_3 = 0;
    
    previousGain_L = 2;
    previousGain_R = 2;
    previousGainRef_L = 1;
    previousGainRef_R = 1;
    
    previousMaxDelaySamples_L = delaySamples_L;
    previousMaxDelaySamples_R = delaySamples_R;
    previousMaxDelaySamplesRef_L = delaySamplesRef_L;
    previousMaxDelaySamplesRef_L = delaySamplesRef_L;
    
    mFilter.setSampleRate(getSampleRate());
    mDelayLine.setSampleRate(getSampleRate());
    delayBufferLength_ = (int)((4/0.345) * sampleRate/1000);
    delayBufferLengthRef_ = (int)((9/0.345) * sampleRate/1000);
    mDelayLine.initialize();
    
}

void VirtualTubeFlangerAudioProcessor::releaseResources()
{
    mDelayLine.suspend();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualTubeFlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VirtualTubeFlangerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    int numSamples = buffer.getNumSamples();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    
    float width = *width_; //Width = %Delay
    float feedback = *feedback_;
    float frequency = *frequencyRate_;// Vibrato: base 2 - 14 Hz  Flanger: 0.1 Hz to 10 Hz//Chorus: 0.1 to 3 Hz.
    float inverseSampleRate = 1./getSampleRate();
    
    float wetValue_ = *dryWetMix_;
    
    rad = floor(*tubeSize_*10 - 12);
    
    // Vibrato: basic delay 1-10 ms, Flanger: basic delay 1-10 ms, Chorus: 20 to 30 ms
    currentGain_L = *gainLeft_;
    currentGain_R = *gainRight_;
    currentGainRef_L = *gainRefLeft_;
    currentGainRef_R = *gainRefRight_;
    
    tubeLengthLeft = *tubeLengthLeft_;
    tubeLengthRight = *tubeLengthRight_;
    tubeEndLeft = *tubeEndLeft_ *2;
    tubeEndRight = *tubeEndRight_ *2;
    
    //computing delay samples
    delaySamples_L = mFilter.setDelaySamples(delayMilli_L);
    delaySamples_R = mFilter.setDelaySamples(delayMilli_R);
    
    //computing delay samples (reflection)
    delaySamplesRef_L = mFilter.setDelaySamples(delayMilliRef_L);
    delaySamplesRef_R = mFilter.setDelaySamples(delayMilliRef_R);
    
    maxDelaySamples_L = round(tubeLengthLeft*getSampleRate()/1000); // basic delay in # samples
    maxDelaySamplesRef_L = round(tubeEndLeft*getSampleRate()/1000);
    maxDelaySamples_R = round(tubeLengthRight*getSampleRate()/1000);
    maxDelaySamplesRef_R = round(tubeEndRight*getSampleRate()/1000);
    
    applyFilterDelay_L(numSamples);
    applyFilterDelay_R(numSamples);
    
    applyGain(numSamples);
    
    for (int i = 0; i < numSamples; ++i)
    {
        
        const float inL = channelDataL[i];
        const float inR = channelDataR[i];
        float outL = 0.0;
        float outR = 0.0;
        
        process();
        
        //computing filter coefficients
        mFilter.setValues(interpolatedTubeLength_L, rad);
        mFilter.getCalculatedCoefficients(0);
        
        mFilter.setValues(interpolatedTubeLength_R, rad);
        mFilter.getCalculatedCoefficients(1);
        
        //computing filter coefficients (reflection)
        mFilter.setValues(interpolatedTubeEnd_L, rad);
        mFilter.getCalculatedCoefficients_Ref(0);
        
        mFilter.setValues(interpolatedTubeEnd_R, rad);
        mFilter.getCalculatedCoefficients_Ref(1);
        
        double currentDelayL = maxDelaySamples_L/2 * ((1 + sin(2.0 * M_PI * ph) * width));
        double currentDelayR = maxDelaySamples_R/2 * ((1 + sin(2.0 * M_PI * ph) * width));
        
        double currentDelayRefL = maxDelaySamplesRef_L/2 * ((1 + sin(2.0 * M_PI * ph) * width));
        double currentDelayRefR = maxDelaySamplesRef_R/2 * ((1 + sin(2.0 * M_PI * ph) * width));
        
        double xL = computeOutFilter_L(inL);
        double xR = computeOutFilter_R(inR);
        
        double x_fin_L = computeOutReflectionFilter_L(outL);
        double x_fin_R = computeOutReflectionFilter_R(outR);
        
        outL =  inL + (wetValue_) * (currentGain_L * mDelayLine.delayLine_Flanger_L(xL * feedback, currentDelayL) + currentGainRef_L * mDelayLine.delayLine_Flanger_Ref_L(x_fin_L * feedback, currentDelayRefL));
        
        outR =  inR + (wetValue_) * (currentGain_R * mDelayLine.delayLine_Flanger_R(xR * feedback, currentDelayR) + currentGainRef_R * mDelayLine.delayLine_Flanger_Ref_R(x_fin_R * feedback, currentDelayRefR));
        
        channelDataR[i] = outL;
        channelDataL[i] = outR;
        
        interpolatedGain_L += incrementGain_L;
        interpolatedGain_R += incrementGain_R;
        
        interpolatedGainRef_L += incrementGainRef_L;
        interpolatedGainRef_R += incrementGainRef_R;
        
        interpolatedTubeLength_L += incrementTubeLength_L;
        interpolatedTubeLength_R += incrementTubeLength_R;
        
        interpolatedTubeEnd_L += incrementTubeEnd_L;
        interpolatedTubeEnd_R += incrementTubeEnd_R;
        
        interpolatedMaxDelaySamples_L += incrementMaxDelaySamples_L;
        interpolatedMaxDelaySamples_R += incrementMaxDelaySamples_R;
        
        interpolatedMaxDelaySamplesRef_L += incrementMaxDelaySamplesRef_L;
        interpolatedMaxDelaySamplesRef_R += incrementMaxDelaySamplesRef_R;
        
        ph += frequency*inverseSampleRate;
        if(ph >= 1.0){
            ph -= 1.0;
        }
    }
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

void VirtualTubeFlangerAudioProcessor::applyFilterDelay_L(int numSamples){
    
    //interpolating lengths (filter coefficients)
    incrementTubeLength_L = (tubeLengthLeft - previousTubeLength_L) / (float) numSamples;
    interpolatedTubeLength_L = previousTubeLength_L;
    
    previousTubeLength_L = tubeLengthLeft;
    
    incrementTubeEnd_L = (tubeEndLeft - previousTubeEnd_L) / (float) numSamples;
    interpolatedTubeEnd_L = previousTubeEnd_L;
    
    previousTubeEnd_L = tubeEndLeft;
    
    //interpolating delays
    incrementMaxDelaySamples_L = (maxDelaySamples_L - previousMaxDelaySamples_L) / (float) numSamples;
    interpolatedMaxDelaySamples_L = previousMaxDelaySamples_L;
    
    previousMaxDelaySamples_L = maxDelaySamples_L;
    
    incrementMaxDelaySamplesRef_L = (maxDelaySamplesRef_L - previousMaxDelaySamplesRef_L) / (float) numSamples;
    interpolatedMaxDelaySamplesRef_L = previousMaxDelaySamplesRef_L;
    
    previousMaxDelaySamplesRef_L = maxDelaySamplesRef_L;
    
}

void VirtualTubeFlangerAudioProcessor::applyFilterDelay_R(int numSamples){
    
    //interpolating lengths (filter coefficients)
    incrementTubeLength_R = (tubeLengthRight - previousTubeLength_R) / (float) numSamples;
    interpolatedTubeLength_R = previousTubeLength_R;
    
    previousTubeLength_R = tubeLengthRight;
    
    incrementTubeEnd_R = (tubeEndRight - previousTubeEnd_R) / (float) numSamples;
    interpolatedTubeEnd_R = previousTubeEnd_R;
    
    previousTubeEnd_R = tubeEndRight;
    
    //interpolating delays
    incrementMaxDelaySamples_R = (maxDelaySamples_R - previousMaxDelaySamples_R) / (float) numSamples;
    interpolatedMaxDelaySamples_R = previousMaxDelaySamples_R;
    
    previousMaxDelaySamples_R = maxDelaySamples_R;
    
    incrementMaxDelaySamplesRef_R = (maxDelaySamplesRef_R - previousMaxDelaySamplesRef_R) / (float) numSamples;
    interpolatedMaxDelaySamplesRef_R = previousMaxDelaySamplesRef_R;
    
    previousMaxDelaySamplesRef_R = maxDelaySamplesRef_R;
}

void VirtualTubeFlangerAudioProcessor::applyGain(int numSamples){
    
    //left channel
    incrementGain_L = (currentGain_L - previousGain_L) / (double) numSamples;
    interpolatedGain_L = previousGain_L;
    
    previousGain_L = currentGain_L;
    
    incrementGainRef_L = (currentGainRef_L - previousGainRef_L) / (double) numSamples;
    interpolatedGainRef_L = previousGainRef_L;
    
    previousGainRef_L = currentGainRef_L;
    
    //right channel
    incrementGain_R = (currentGain_R - previousGain_R) / (double) numSamples;
    interpolatedGain_R = previousGain_R;
    
    previousGain_R = currentGain_R;
    
    incrementGainRef_R = (currentGainRef_R - previousGainRef_R) / (double) numSamples;
    interpolatedGainRef_R = previousGainRef_R;
    
    previousGainRef_R = currentGainRef_R;
}


void VirtualTubeFlangerAudioProcessor::process() {
    
    i_0 = ptr%7;       //->6
    i_1 = (ptr + 1)%7; //->0
    i_2 = (ptr + 2)%7; //->1
    i_3 = (ptr + 3)%7; //->2
    i_4 = (ptr + 4)%7; //->3
    i_5 = (ptr + 5)%7; //->4
    i_6 = (ptr + 6)%7; //->5
    
    if (--ptr < 0) { ptr += 7; }
    
    j_0 = ptr2%4;       //->3
    j_1 = (ptr2 + 1)%4; //->0
    j_2 = (ptr2 + 2)%4; //->1
    j_3 = (ptr2 + 3)%4; //->2
    
    if (--ptr2 < 0) { ptr2 += 4; }
}


double VirtualTubeFlangerAudioProcessor::computeOutFilter_L(double input){
    
    double inL = input;
    double out;
    
    bufIn_L[i_0] = inL;
    
    bufOut_L[i_0] = bufIn_L[i_0] * mFilter.b0f_L + bufIn_L[i_1] * mFilter.b1f_L + bufIn_L[i_2] * mFilter.b2f_L + bufIn_L[i_3] * mFilter.b3f_L + bufIn_L[i_4] * mFilter.b4f_L + bufIn_L[i_5] * mFilter.b5f_L + bufIn_L[i_6] * mFilter.b6f_L - bufOut_L[i_1] * mFilter.a1f_L - bufOut_L[i_2] * mFilter.a2f_L - bufOut_L[i_3] * mFilter.a3f_L - bufOut_L[i_4] * mFilter.a4f_L - bufOut_L[i_5] * mFilter.a5f_L - bufOut_L[i_6] * mFilter.a6f_L;
    
    out = bufOut_L[i_0];
    
    return out;
    
}

double VirtualTubeFlangerAudioProcessor::computeOutFilter_R(double input){
    
    double inR = input;
    double out;
    
    bufIn_R[i_0] = inR;
    
    bufOut_R[i_0] = bufIn_R[i_0] * mFilter.b0f_R + bufIn_R[i_1] * mFilter.b1f_R + bufIn_R[i_2] * mFilter.b2f_R + bufIn_R[i_3] * mFilter.b3f_R + bufIn_R[i_4] * mFilter.b4f_R + bufIn_R[i_5] * mFilter.b5f_R + bufIn_R[i_6] * mFilter.b6f_R - bufOut_R[i_1] * mFilter.a1f_R - bufOut_R[i_2] * mFilter.a2f_R - bufOut_R[i_3] * mFilter.a3f_R - bufOut_R[i_4] * mFilter.a4f_R - bufOut_R[i_5] * mFilter.a5f_R - bufOut_R[i_6] * mFilter.a6f_R;
    
    out = bufOut_R[i_0];
    
    return out;
    
}

double VirtualTubeFlangerAudioProcessor::computeOutReflectionFilter_L(double input){
    
    double inL = input;
    double out;
    
    bufIn_Ref_L[i_0] = inL;
    
    bufOut_Ref_L[i_0] = bufIn_Ref_L[i_0] * mFilter.b0f_Ref_L + bufIn_Ref_L[i_1] * mFilter.b1f_Ref_L + bufIn_Ref_L[i_2] * mFilter.b2f_Ref_L + bufIn_Ref_L[i_3] * mFilter.b3f_Ref_L + bufIn_Ref_L[i_4] * mFilter.b4f_Ref_L + bufIn_Ref_L[i_5] * mFilter.b5f_Ref_L + bufIn_Ref_L[i_6] * mFilter.b6f_Ref_L - bufOut_Ref_L[i_1] * mFilter.a1f_Ref_L - bufOut_Ref_L[i_2] * mFilter.a2f_Ref_L - bufOut_Ref_L[i_3] * mFilter.a3f_Ref_L - bufOut_Ref_L[i_4] * mFilter.a4f_Ref_L - bufOut_Ref_L[i_5] * mFilter.a5f_Ref_L - bufOut_Ref_L[i_6] * mFilter.a6f_Ref_L;
    
    bufIn_Fin_L[j_0] = bufOut_Ref_L[i_0];
    
    bufOut_Fin_L[j_0] = bufIn_Fin_L[j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_L[j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_L[j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_L[j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_L[j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_L[j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_L[j_3] * mFilter.a_Ref[rad][2];
    
    out = bufOut_Fin_L[j_0];
    
    return out;
    
}

double VirtualTubeFlangerAudioProcessor::computeOutReflectionFilter_R(double input){
    
    double inR = input;
    double out;
    
    bufIn_Ref_R[i_0] = inR;
    
    bufOut_Ref_R[i_0] = bufIn_Ref_R[i_0] * mFilter.b0f_Ref_R + bufIn_Ref_R[i_1] * mFilter.b1f_Ref_R + bufIn_Ref_R[i_2] * mFilter.b2f_Ref_R + bufIn_Ref_R[i_3] * mFilter.b3f_Ref_R + bufIn_Ref_R[i_4] * mFilter.b4f_Ref_R + bufIn_Ref_R[i_5] * mFilter.b5f_Ref_R + bufIn_Ref_R[i_6] * mFilter.b6f_Ref_R - bufOut_Ref_R[i_1] * mFilter.a1f_Ref_R - bufOut_Ref_R[i_2] * mFilter.a2f_Ref_R - bufOut_Ref_R[i_3] * mFilter.a3f_Ref_R - bufOut_Ref_R[i_4] * mFilter.a4f_Ref_R - bufOut_Ref_R[i_5] * mFilter.a5f_Ref_R - bufOut_Ref_R[i_6] * mFilter.a6f_Ref_R;
    
    bufIn_Fin_R[j_0] = bufOut_Ref_R[i_0];
    
    bufOut_Fin_R[j_0] = bufIn_Fin_R[j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_R[j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_R[j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_R[j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_R[j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_R[j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_R[j_3] * mFilter.a_Ref[rad][2];
    
    out = bufOut_Fin_R[j_0];
    
    return out;
    
}

//==============================================================================
bool VirtualTubeFlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VirtualTubeFlangerAudioProcessor::createEditor()
{
    return new VirtualTubeFlangerAudioProcessorEditor (*this);
}

//==============================================================================
void VirtualTubeFlangerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualTubeFlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new VirtualTubeFlangerAudioProcessor();
}
