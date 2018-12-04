/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeEffectsAudioProcessor::VirtualTubeEffectsAudioProcessor()
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
    
    
    parameters.createAndAddParameter("tubeLengthLeft_", "tubeLengthLeft", "tubeLengthLeft", NormalisableRange<float>(1,3), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeLengthRight_", "tubeLengthRight", "tubeLengthRight", NormalisableRange<float>(1,3), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(0.0, 3.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(0.0, 3.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0, 1.0), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndLeft_", "tubeEndLeft", "tubeEndLeft", NormalisableRange<float>(1.0, 2.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndRight_", "tubeEndRight", "tubeEndRight", NormalisableRange<float>(1.0, 2.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(0.0, 9.0), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight", "gainRefRight", NormalisableRange<float>(0.0, 9.0), 1, nullptr, nullptr);
    
    parameters.createAndAddParameter("feedback_", "feedback", "feedback", NormalisableRange<float>(0.0,0.9), 0.0, nullptr, nullptr);
    
    
    
    
    parameters.createAndAddParameter("width_", "width", "width", NormalisableRange<float>(0.0, 0.9), 0, nullptr, nullptr);
    parameters.createAndAddParameter("frequencyRate_", "frequencyRate", "frequencyRate", NormalisableRange<float>(0.0, 14.0), 0.0, nullptr, nullptr);
    
    parameters.createAndAddParameter("enabledVibrato_", "enabledVibrato", "enabledVibrato", NormalisableRange<float>(0,1), false, nullptr, nullptr, true);
    parameters.createAndAddParameter("enabledChorus_", "enabledChorus", "enabledChorus", NormalisableRange<float>(0,1), false, nullptr, nullptr, true);
    parameters.createAndAddParameter("enabledFlanger_", "enabledFlanger", "enabledFlanger", NormalisableRange<float>(0,1), false, nullptr, nullptr, true);
    
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
    feedback_ = parameters.getRawParameterValue ("feedback_");
    width_ = parameters.getRawParameterValue ("width_");
    frequencyRate_ = parameters.getRawParameterValue ("frequencyRate_");
    
    enabledVibrato_ = parameters.getRawParameterValue ("enabledVibrato_");
    enabledChorus_ = parameters.getRawParameterValue ("enabledChorus_");
    enabledFlanger_ = parameters.getRawParameterValue ("enabledFlanger_");

    
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

    ph = 0;
    
    //addParameter (tubeLengthLeft_ = new AudioParameterFloat ("tubeLengthLeft_", "TubeLength Left", 1.0f, 30.0f, 10.0f));
    //addParameter (gainLeft_     = new AudioParameterFloat ("gainLeft_",     "Gain Left",     0.0f, 10.0f, 5.0f));
}

VirtualTubeEffectsAudioProcessor::~VirtualTubeEffectsAudioProcessor()
{
}

//==============================================================================
const String VirtualTubeEffectsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualTubeEffectsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeEffectsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeEffectsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VirtualTubeEffectsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualTubeEffectsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualTubeEffectsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualTubeEffectsAudioProcessor::setCurrentProgram (int index)
{
}

const String VirtualTubeEffectsAudioProcessor::getProgramName (int index)
{
    return {};
}

void VirtualTubeEffectsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VirtualTubeEffectsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
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
    
    mFilter.setSampleRate(getSampleRate());
    mDelayLine.setSampleRate(getSampleRate());
    delayBufferLength_ = (int)((4/0.345) * sampleRate/1000);
    delayBufferLengthRef_ = (int)((9/0.345) * sampleRate/1000);
    mDelayLine.initialize();
    
    rad = floor(*tubeSize_*10 - 12);

    leng_L = mFilter.setLengt(*tubeLengthLeft_);
    delayMilli_L = mFilter.setDelayMilliseconds(leng_L);
    delaySamples_L = mFilter.setDelaySamples(delayMilli_L);
    mDelayLine.setDelayL(delaySamples_L);
    mFilter.setValues(*tubeLengthLeft_, rad);
    mFilter.getCalculatedCoefficients(0);

    leng_R = mFilter.setLengt(*tubeLengthRight_);
    delayMilli_R = mFilter.setDelayMilliseconds(leng_R);
    delaySamples_R = mFilter.setDelaySamples(delayMilli_R);
    mDelayLine.setDelayR(delaySamples_R);
    mFilter.setValues(*tubeLengthRight_, rad);
    mFilter.getCalculatedCoefficients(1);
}

void VirtualTubeEffectsAudioProcessor::releaseResources()
{
   mDelayLine.suspend();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualTubeEffectsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VirtualTubeEffectsAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
    
    int maxDelayL = *tubeLengthLeft_;// Vibrato: basic delay 1-10 ms, Flanger: basic delay 1-10 ms, Chorus: 20 to 30 ms
    int maxDelaySamplesL = round(maxDelayL*getSampleRate()/1000); // basic delay in # samples
    
    int maxDelayRefL = *tubeEndLeft_;
    int maxDelaySamplesRefL = round(maxDelayRefL*getSampleRate()/1000);
    
    int maxDelayR = *tubeLengthRight_;
    int maxDelaySamplesR = round(maxDelayR*getSampleRate()/1000); // basic delay in # samples
    
    int maxDelayRefR = *tubeEndRight_;
    int maxDelaySamplesRefR = round(maxDelayRefR*getSampleRate()/1000);
    
    float currentGain_L = *gainLeft_;
    float currentGain_R = *gainRight_;
    float currentGainRef_L = *gainRefLeft_;
    float currentGainRef_R = *gainRefRight_;
    
    double wetValue_ = *dryWetMix_;
    
    bool enabledVibrato = *enabledVibrato_;
    bool enabledChorus = *enabledChorus_;
    bool enabledFlanger = *enabledFlanger_;
    
    if(enabledVibrato) {
    
        for (int i = 0; i < numSamples; ++i)
        {
            const float inL = channelDataL[i];
            const float inR = channelDataR[i];
            float outL = 0.0;
            float outR = 0.0;
                
            process();
                
            //double currentDelayL = ((sin(2.0 * M_PI * ph) + 1) * 0.5) * Width * maxDelaySamplesL + 3;
            //double currentDelayRefL = ((sin(2.0 * M_PI * ph) + 1) * 0.5) * Width * maxDelaySamplesRefL + 3;
                
            //double currentDelayR = ((sin(2.0 * M_PI * ph) + 1) * 0.5) * Width * maxDelaySamplesR + 3;
            //double currentDelayRefR = ((sin(2.0 * M_PI * ph) + 1) * 0.5) * Width * maxDelaySamplesRefR + 3;
                
            double currentDelayL = maxDelaySamplesL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayR = maxDelaySamplesR/2 * ((1 + sin(2.0 * M_PI * ph) * width));
                
            double currentDelayRefL = maxDelaySamplesRefL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayRefR = maxDelaySamplesRefR/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            
            outL = computeOutFilter_L(inL);
            double xL = outL;
                
            outR = computeOutFilter_R(inR);
            double xR = outR;
                
            double outFinL = computeOutReflectionFilter_L(outL);
            double x_fin_L = outFinL;
                
            double outFinR = computeOutReflectionFilter_R(outR);
            double x_fin_R = outFinR;
     
                
            outL =  currentGain_L * mDelayLine.delayLine_Vibrato_L(xL, currentDelayL) + currentGainRef_L * mDelayLine.delayLine_Vibrato_Ref_L(x_fin_L, currentDelayRefL);
                
            outR =  currentGain_R * mDelayLine.delayLine_Vibrato_R(xR, currentDelayR) + currentGainRef_R * mDelayLine.delayLine_Vibrato_Ref_R(x_fin_R, currentDelayRefR);
             
            channelDataR[i] = outL;
            channelDataL[i] = outR;
            
            
            ph += frequency*inverseSampleRate;
            if(ph >= 1.0){
                ph -= 1.0;
            }
        }
        
    }else if(enabledFlanger){
            
        for (int i = 0; i < numSamples; ++i)
        {
                
            const float inL = channelDataL[i];
            const float inR = channelDataR[i];
            float outL = 0.0;
            float outR = 0.0;
                
            process();
            
            double currentDelayL = maxDelaySamplesL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayR = maxDelaySamplesR/2 * ((1 + sin(2.0 * M_PI * ph) * width));
                
            double currentDelayRefL = maxDelaySamplesRefL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayRefR = maxDelaySamplesRefR/2 * ((1 + sin(2.0 * M_PI * ph) * width));

            outL = computeOutFilter_L(inL);
            double xL = outL;
            
            outR = computeOutFilter_R(inR);
            double xR = outR;
            
            double outFinL = computeOutReflectionFilter_L(outL);
            double x_fin_L = outFinL;
            
            double outFinR = computeOutReflectionFilter_R(outR);
            double x_fin_R = outFinR;
            
            outL =  inL + (wetValue_) * (currentGain_L * mDelayLine.delayLine_Vibrato_L(xL * feedback, currentDelayL) + currentGainRef_L * mDelayLine.delayLine_Vibrato_Ref_L(x_fin_L * feedback, currentDelayRefL));
            
            outR =  inR + (wetValue_) * (currentGain_R * mDelayLine.delayLine_Vibrato_R(xR * feedback, currentDelayR) + currentGainRef_R * mDelayLine.delayLine_Vibrato_Ref_R(x_fin_R * feedback, currentDelayRefR));
    
            channelDataR[i] = outL;
            channelDataL[i] = outR;
                
                
            ph += frequency*inverseSampleRate;
            if(ph >= 1.0){
                ph -= 1.0;
            }
        }
            
    }else if(enabledChorus){
        
        for (int i = 0; i < numSamples; ++i)
        {
                    
            const float inL = channelDataL[i];
            const float inR = channelDataR[i];
            float outL = 0.0;
            float outR = 0.0;
                    
            process();
                
            double currentDelayL = maxDelaySamplesL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayR = maxDelaySamplesR/2 * ((1 + sin(2.0 * M_PI * ph) * width));
                
            double currentDelayRefL = maxDelaySamplesRefL/2 * ((1 + sin(2.0 * M_PI * ph) * width));
            double currentDelayRefR = maxDelaySamplesRefR/2 * ((1 + sin(2.0 * M_PI * ph) * width));

            outL = computeOutFilter_L(inL);
            double xL = outL;
            
            outR = computeOutFilter_R(inR);
            double xR = outR;
            
            double outFinL = computeOutReflectionFilter_L(outL);
            double x_fin_L = outFinL;
            
            double outFinR = computeOutReflectionFilter_R(outR);
            double x_fin_R = outFinR;

            
            outL =  inL + (wetValue_) * (currentGain_L * mDelayLine.delayLine_Vibrato_L(xL * feedback, currentDelayL) + currentGainRef_L * mDelayLine.delayLine_Vibrato_Ref_L(x_fin_L * feedback, currentDelayRefL));
            
            outR =  inR + (wetValue_) * (currentGain_R * mDelayLine.delayLine_Vibrato_R(xR * feedback, currentDelayR) + currentGainRef_R * mDelayLine.delayLine_Vibrato_Ref_R(x_fin_R * feedback, currentDelayRefR));
    
            channelDataR[i] = outL;
            channelDataL[i] = outR;
                    
                    
            ph += frequency*inverseSampleRate;
            if(ph >= 1.0){
                ph -= 1.0;
            }
        }
        
    }
    
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}



void VirtualTubeEffectsAudioProcessor::process() {
    
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


double VirtualTubeEffectsAudioProcessor::computeOutFilter_L(double input){
    
    double inL = input;
    double out;
    
    bufIn_L[i_0] = inL;
    
    bufOut_L[i_0] = bufIn_L[i_0] * mFilter.b0f_L + bufIn_L[i_1] * mFilter.b1f_L + bufIn_L[i_2] * mFilter.b2f_L + bufIn_L[i_3] * mFilter.b3f_L + bufIn_L[i_4] * mFilter.b4f_L + bufIn_L[i_5] * mFilter.b5f_L + bufIn_L[i_6] * mFilter.b6f_L - bufOut_L[i_1] * mFilter.a1f_L - bufOut_L[i_2] * mFilter.a2f_L - bufOut_L[i_3] * mFilter.a3f_L - bufOut_L[i_4] * mFilter.a4f_L - bufOut_L[i_5] * mFilter.a5f_L - bufOut_L[i_6] * mFilter.a6f_L;
    
    out = bufOut_L[i_0];
    
    return out;
    
}

double VirtualTubeEffectsAudioProcessor::computeOutFilter_R(double input){
    
    double inR = input;
    double out;
    
    bufIn_R[i_0] = inR;
    
    bufOut_R[i_0] = bufIn_R[i_0] * mFilter.b0f_R + bufIn_R[i_1] * mFilter.b1f_R + bufIn_R[i_2] * mFilter.b2f_R + bufIn_R[i_3] * mFilter.b3f_R + bufIn_R[i_4] * mFilter.b4f_R + bufIn_R[i_5] * mFilter.b5f_R + bufIn_R[i_6] * mFilter.b6f_R - bufOut_R[i_1] * mFilter.a1f_R - bufOut_R[i_2] * mFilter.a2f_R - bufOut_R[i_3] * mFilter.a3f_R - bufOut_R[i_4] * mFilter.a4f_R - bufOut_R[i_5] * mFilter.a5f_R - bufOut_R[i_6] * mFilter.a6f_R;
    
    out = bufOut_R[i_0];
    
    return out;
    
}

double VirtualTubeEffectsAudioProcessor::computeOutReflectionFilter_L(double input){
    
    double inL = input;
    double out;
    
    bufIn_Ref_L[i_0] = inL;
    
    bufOut_Ref_L[i_0] = bufIn_Ref_L[i_0] * mFilter.b0f_Ref_L + bufIn_Ref_L[i_1] * mFilter.b1f_Ref_L + bufIn_Ref_L[i_2] * mFilter.b2f_Ref_L + bufIn_Ref_L[i_3] * mFilter.b3f_Ref_L + bufIn_Ref_L[i_4] * mFilter.b4f_Ref_L + bufIn_Ref_L[i_5] * mFilter.b5f_Ref_L + bufIn_Ref_L[i_6] * mFilter.b6f_Ref_L - bufOut_Ref_L[i_1] * mFilter.a1f_Ref_L - bufOut_Ref_L[i_2] * mFilter.a2f_Ref_L - bufOut_Ref_L[i_3] * mFilter.a3f_Ref_L - bufOut_Ref_L[i_4] * mFilter.a4f_Ref_L - bufOut_Ref_L[i_5] * mFilter.a5f_Ref_L - bufOut_Ref_L[i_6] * mFilter.a6f_Ref_L;
    
    bufIn_Fin_L[j_0] = bufOut_Ref_L[i_0];
    
    bufOut_Fin_L[j_0] = bufIn_Fin_L[j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_L[j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_L[j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_L[j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_L[j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_L[j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_L[j_3] * mFilter.a_Ref[rad][2];
    
    out = bufOut_Fin_L[j_0];
    
    return out;
    
}

double VirtualTubeEffectsAudioProcessor::computeOutReflectionFilter_R(double input){
    
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
bool VirtualTubeEffectsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VirtualTubeEffectsAudioProcessor::createEditor()
{
    return new VirtualTubeEffectsAudioProcessorEditor (*this);
}

//==============================================================================
void VirtualTubeEffectsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualTubeEffectsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new VirtualTubeEffectsAudioProcessor();
}
