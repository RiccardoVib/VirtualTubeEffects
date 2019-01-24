/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VirtualTubeVibratoAudioProcessorEditor  : public AudioProcessorEditor,
                                                private Slider::Listener
                                                
{
public:
    VirtualTubeVibratoAudioProcessorEditor (VirtualTubeVibratoAudioProcessor&);
    ~VirtualTubeVibratoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider*) override;

    inline std::string createTextForDelays(double value){
        
        std::string valueText = std::to_string(value);
        valueText.erase(5);
        valueText.append(" ms");
        return valueText;
    }
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
private:

    VirtualTubeVibratoAudioProcessor& processor;

    Label delayTimeLeftLabel_, delayTimeRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, delayTimeRefLeftLabel_, delayTimeRefRightLabel_, gainRefLeftLabel_, gainRefRightLabel_;
    
    Slider delayTimeLeftSlider_, delayTimeRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, delayTimeRefLeftSlider_, delayTimeRefRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider widthSlider_, frequencyRateSlider_;
    
    Label widthLabel_, frequencyRateLabel_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_, delayTimeText_;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeSizeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeRefLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeRefRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequencyRateAttachment;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeVibratoAudioProcessorEditor)
};
