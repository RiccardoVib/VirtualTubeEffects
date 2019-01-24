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

    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, tubeEndLeftLabel_, tubeEndRightLabel_, gainRefLeftLabel_, gainRefRightLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, tubeEndLeftSlider_, tubeEndRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider widthSlider_, frequencyRateSlider_;
    
    Label widthLabel_, frequencyRateLabel_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_, gainText_, gainRefText_, tubeLengthText_, tubeEndText_;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeLengthLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeLengthRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeSizeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeEndLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeEndRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequencyRateAttachment;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeVibratoAudioProcessorEditor)
};