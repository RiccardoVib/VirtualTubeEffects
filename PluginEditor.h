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
class VirtualTubeEffectsAudioProcessorEditor  : public AudioProcessorEditor,
                                                private Slider::Listener,
                                                private Button::Listener
{
public:
    VirtualTubeEffectsAudioProcessorEditor (VirtualTubeEffectsAudioProcessor&);
    ~VirtualTubeEffectsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button* button) override;
    
    inline std::string createTextForDelays(double value){
        
        std::string valueText = std::to_string(value);
        valueText.erase(5);
        valueText.append(" ms");
        return valueText;
    }
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
private:
    
    VirtualTubeEffectsAudioProcessor& processor;
    
    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, tubeEndLeftLabel_, tubeEndRightLabel_, gainRefLeftLabel_, gainRefRightLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_, tubeEndLeftSlider_, tubeEndRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider widthSlider_, frequencyRateSlider_, feedbackSlider_;
    
    Label enabledVibratoLabel_, widthLabel_, frequencyRateLabel_, feedbackLabel_, enabledChorusLabel_, enabledFlangerLabel_;
    
    ToggleButton enabledVibratoToggleButton_, enabledFlangerToggleButton_, enabledChorusToggleButton_;
    
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
    SliderAttachment* feedbackAttachment;
    SliderAttachment* widthAttachment;
    SliderAttachment* frequencyRateAttachment;
    
    ButtonAttachment* enabledVibratoAttachment;
    ButtonAttachment* enabledChorusAttachment;
    ButtonAttachment* enabledFlangerAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeEffectsAudioProcessorEditor)
};
