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
class VirtualTubeChorusAudioProcessorEditor  : public AudioProcessorEditor,
                                               private Slider::Listener
{
public:
    VirtualTubeChorusAudioProcessorEditor (VirtualTubeChorusAudioProcessor&);
    ~VirtualTubeChorusAudioProcessorEditor();

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
  
    VirtualTubeChorusAudioProcessor& processor;

    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, tubeEndLeftLabel_, tubeEndRightLabel_, gainRefLeftLabel_, gainRefRightLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_, tubeEndLeftSlider_, tubeEndRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider widthSlider_, frequencyRateSlider_, feedbackSlider_;
    
    Label widthLabel_, frequencyRateLabel_, feedbackLabel_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_, gainText_, gainRefText_, tubeLengthText_, tubeEndText_;
    
    
    SliderAttachment* tubeLengthLeftAttachment;
    SliderAttachment* tubeLengthRightAttachment;
    SliderAttachment* gainLeftAttachment;
    SliderAttachment* gainRightAttachment;
    SliderAttachment* tubeSizeAttachment;
    SliderAttachment* dryWetMixAttachment;
    SliderAttachment* tubeEndLeftAttachment;
    SliderAttachment* tubeEndRightAttachment;
    SliderAttachment* gainRefLeftAttachment;
    SliderAttachment* gainRefRightAttachment;
    SliderAttachment* widthAttachment;
    SliderAttachment* frequencyRateAttachment;
    SliderAttachment* feedbackAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeChorusAudioProcessorEditor)
};
