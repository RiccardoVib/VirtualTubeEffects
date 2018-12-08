/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeChorusAudioProcessorEditor::VirtualTubeChorusAudioProcessorEditor (VirtualTubeChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
    tubeLengthLeftLabel_("", "Left Channel:"), tubeLengthRightLabel_("", "Right Channel:"), gainLeftLabel_("", "Left Channel:"), gainRightLabel_("", "Right Channel:"), tubeSizeLabel_("", "Tube Size (cm):"), dryWetMixLabel_("", "Dry/Wet:"), tubeEndLeftLabel_("", "Left Channel:"),tubeEndRightLabel_("", "Right Channel:"), gainRefLeftLabel_("", "Left Channel:"),gainRefRightLabel_("", "Right Channel:"), frequencyRateLabel_("", "Frequency Rate:"), widthLabel_("", "Width:"), feedbackLabel_("", "Feedback:")
{
    setSize (800, 400);
    
    tubeLengthLeftAttachment = new SliderAttachment(processor.parameters, "tubeLengthLeft_", tubeLengthLeftSlider_);
    tubeLengthRightAttachment = new SliderAttachment(processor.parameters, "tubeLengthRight_", tubeLengthRightSlider_);
    gainLeftAttachment = new SliderAttachment(processor.parameters, "gainLeft_", gainLeftSlider_);
    gainRightAttachment = new SliderAttachment(processor.parameters, "gainRight_", gainRightSlider_);
    tubeSizeAttachment = new SliderAttachment(processor.parameters, "tubeSize_", tubeSizeSlider_);
    dryWetMixAttachment = new SliderAttachment(processor.parameters, "dryWetMix_", dryWetMixSlider_);
    tubeEndLeftAttachment = new SliderAttachment(processor.parameters, "tubeEndLeft_", tubeEndLeftSlider_);
    tubeEndRightAttachment = new SliderAttachment(processor.parameters, "tubeEndRight_", tubeEndRightSlider_);
    gainRefLeftAttachment = new SliderAttachment(processor.parameters, "gainRefLeft_", gainRefLeftSlider_);
    gainRefRightAttachment = new SliderAttachment(processor.parameters, "gainRefRight_", gainRefRightSlider_);
    frequencyRateAttachment = new SliderAttachment(processor.parameters, "frequencyRate_", frequencyRateSlider_);
    widthAttachment = new SliderAttachment(processor.parameters, "width_", widthSlider_);
    feedbackAttachment = new SliderAttachment(processor.parameters, "feedback_", feedbackSlider_);
    
    
    
    
    gainText_.setReadOnly(true);
    gainText_.setText("Gain Level");
    addAndMakeVisible (&gainText_);
    
    gainRefText_.setReadOnly(true);
    gainRefText_.setText("Reflection Level");
    addAndMakeVisible (&gainRefText_);
    
    tubeLengthText_.setReadOnly(true);
    tubeLengthText_.setText("Tube Length (m)");
    addAndMakeVisible(&tubeLengthText_);
    
    tubeEndText_.setReadOnly(true);
    tubeEndText_.setText("Tube End Distance (m)");
    addAndMakeVisible(&tubeEndText_);
    
    delayMsL_.setReadOnly(true);
    delayMsL_.setText(createTextForDelays(processor.delayMilli_L));
    addAndMakeVisible (&delayMsL_);
    
    delayMsR_.setReadOnly(true);
    delayMsR_.setText(createTextForDelays(processor.delayMilli_R));
    addAndMakeVisible (&delayMsR_);
    
    delayMsRefL_.setReadOnly(true);
    delayMsRefL_.setText(createTextForDelays(processor.delayMilliRef_L));
    addAndMakeVisible (&delayMsRefL_);
    
    delayMsRefR_.setReadOnly(true);
    delayMsRefR_.setText(createTextForDelays(processor.delayMilliRef_L));
    addAndMakeVisible (&delayMsRefR_);
    
    tubeLengthLeftSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthLeftSlider_.setRange (1.0, 4.0, 0.01);
    tubeLengthLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthLeftSlider_.setTextValueSuffix(" m");
    tubeLengthLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeLengthLeftSlider_);
    tubeLengthLeftSlider_.addListener(this);
    
    tubeLengthRightSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthRightSlider_.setRange (1.0, 4.0, 0.01);
    tubeLengthRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRightSlider_.setTextValueSuffix(" m");
    tubeLengthRightSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeLengthRightSlider_);
    tubeLengthRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //gainLeftSlider_.setRange (-48.0, 9.0, 0.01);
    gainLeftSlider_.setRange (0.0, 3.0, 0.01);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" dB");
    gainLeftSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //gainRightSlider_.setRange (-48.0, 9.0, 0.01);
    gainRightSlider_.setRange (0.0, 3.0, 0.01);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" dB");
    gainRightSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    tubeSizeSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider_.setRange (0.0, 1.0, 0.01);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    tubeEndLeftSlider_.setSliderStyle(Slider::LinearBar);
    tubeEndLeftSlider_.setRange (1.0, 2.0, 0.01);
    tubeEndLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeEndLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeEndLeftSlider_.setTextValueSuffix(" m");
    tubeEndLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeEndLeftSlider_);
    tubeEndLeftSlider_.addListener(this);
    
    tubeEndRightSlider_.setSliderStyle(Slider::LinearBar);
    tubeEndRightSlider_.setRange (1.0, 2.0, 0.01);
    tubeEndRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeEndRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeEndRightSlider_.setTextValueSuffix(" m");
    tubeEndRightSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeEndRightSlider_);
    tubeEndRightSlider_.addListener(this);
    
    gainRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //gainRefLeftSlider_.setRange (-48.0, 18.0, 0.01);
    gainRefLeftSlider_.setRange (0.0, 9.0, 0.01);
    gainRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefLeftSlider_.setTextValueSuffix(" dB");
    gainRefLeftSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRefLeftSlider_);
    gainRefLeftSlider_.addListener(this);
    
    gainRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //gainRefRightSlider_.setRange (-48.0, 18.0, 0.01);
    gainRefRightSlider_.setRange (0.0, 9.0, 0.01);
    gainRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefRightSlider_.setTextValueSuffix(" dB");
    gainRefRightSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRefRightSlider_);
    gainRefRightSlider_.addListener(this);
    
    widthSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider_.setRange (0.0, 0.9, 0.01);
    widthSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    widthSlider_.setPopupDisplayEnabled (true, false, this);
    widthSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&widthSlider_);
    widthSlider_.addListener(this);
    
    frequencyRateSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    frequencyRateSlider_.setRange (0.0, 10.0, 0.01);
    frequencyRateSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    frequencyRateSlider_.setPopupDisplayEnabled (true, false, this);
    frequencyRateSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&frequencyRateSlider_);
    frequencyRateSlider_.addListener(this);
    
    feedbackSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider_.setRange (0.0, 0.9, 0.01);
    feedbackSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedbackSlider_.setPopupDisplayEnabled (true, false, this);
    feedbackSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&feedbackSlider_);
    feedbackSlider_.addListener(this);
    
    
    tubeLengthLeftLabel_.attachToComponent(&tubeLengthLeftSlider_, false);
    tubeLengthLeftLabel_.setFont(Font (14.0f));
    
    tubeLengthRightLabel_.attachToComponent(&tubeLengthRightSlider_, false);
    tubeLengthRightLabel_.setFont(Font (14.0f));
    
    gainLeftLabel_.attachToComponent(&gainLeftSlider_, false);
    gainLeftLabel_.setFont(Font (14.0f));
    
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (14.0f));
    
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (14.0f));
    
    dryWetMixLabel_.attachToComponent(&dryWetMixSlider_, false);
    dryWetMixLabel_.setFont(Font (14.0f));
    
    tubeEndLeftLabel_.attachToComponent(&tubeEndLeftSlider_, false);
    tubeEndLeftLabel_.setFont(Font (14.0f));
    
    tubeEndRightLabel_.attachToComponent(&tubeEndRightSlider_, false);
    tubeEndRightLabel_.setFont(Font (14.0f));
    
    gainRefLeftLabel_.attachToComponent(&gainRefLeftSlider_, false);
    gainRefLeftLabel_.setFont(Font (14.0f));
    
    gainRefRightLabel_.attachToComponent(&gainRefRightSlider_, false);
    gainRefRightLabel_.setFont(Font (14.0f));
    
    gainRefRightLabel_.attachToComponent(&gainRefRightSlider_, false);
    gainRefRightLabel_.setFont(Font (14.0f));
    
    widthLabel_.attachToComponent(&widthSlider_, false);
    widthLabel_.setFont(Font (14.0f));
    
    frequencyRateLabel_.attachToComponent(&frequencyRateSlider_, false);
    frequencyRateLabel_.setFont(Font (14.0f));
    
    feedbackLabel_.attachToComponent(&feedbackSlider_, false);
    feedbackLabel_.setFont(Font (14.0f));
}

VirtualTubeChorusAudioProcessorEditor::~VirtualTubeChorusAudioProcessorEditor()
{
}

void VirtualTubeChorusAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &tubeLengthLeftSlider_)
    {
        *processor.tubeLengthLeft_ = tubeLengthLeftSlider_.getValue();
        
        processor.leng_L = processor.mFilter.setLengt(*processor.tubeLengthLeft_);
        processor.delayMilli_L = processor.mFilter.setDelayMilliseconds(processor.leng_L);
        
        std::string delayText = createTextForDelays(processor.delayMilli_L);
        delayMsL_.setText(delayText);
        
        processor.lengRef_L = processor.leng_L + processor.mFilter.setLengt(*processor.tubeEndLeft_);
        processor.delayMilliRef_L = processor.mFilter.setDelayMilliseconds(processor.lengRef_L);
        
        std::string delayTextRef = createTextForDelays(processor.delayMilliRef_L);
        delayMsRefL_.setText(delayTextRef);
       
        
    }
    else if (slider == &tubeLengthRightSlider_)
    {
        *processor.tubeLengthRight_ = tubeLengthRightSlider_.getValue();
        
        processor.leng_R = processor.mFilter.setLengt(*processor.tubeLengthRight_);
        processor.delayMilli_R = processor.mFilter.setDelayMilliseconds(processor.leng_R);
        
        std::string delayText = createTextForDelays(processor.delayMilli_R);
        delayMsR_.setText(delayText);
        
        processor.lengRef_R = processor.leng_R + processor.mFilter.setLengt(*processor.tubeEndRight_);
        processor.delayMilliRef_R = processor.mFilter.setDelayMilliseconds(processor.lengRef_R);
        
        std::string delayTextRef = createTextForDelays(processor.delayMilliRef_R);
        delayMsRefR_.setText(delayTextRef);
        
    }
    else if (slider == &gainLeftSlider_)
    {
        *processor.gainLeft_ = gainLeftSlider_.getValue();
        //*processor.gainLeft_ = pow(10, gainLeftSlider_.getValue() / 20);
    }
    else if (slider == &gainRightSlider_)
    {
        *processor.gainRight_ = gainRightSlider_.getValue();
        //*processor.gainRight_ = pow(10, gainRightSlider_.getValue() / 20);
    }
    else if (slider == &dryWetMixSlider_)
    {
        *processor.dryWetMix_ = dryWetMixSlider_.getValue();
    }
    else if (slider == &tubeSizeSlider_)
    {
        *processor.tubeSize_ = tubeSizeSlider_.getValue();
        
    }
    else if (slider == &tubeEndLeftSlider_)
    {
        *processor.tubeEndLeft_ = tubeEndLeftSlider_.getValue();
        
        processor.lengRef_L = processor.leng_L + processor.mFilter.setLengt(*processor.tubeEndLeft_);
        processor.delayMilliRef_L = processor.mFilter.setDelayMilliseconds(processor.lengRef_L);
        
        std::string delayText = createTextForDelays(processor.delayMilliRef_L);
        delayMsRefL_.setText(delayText);

    }
    else if (slider == &tubeEndRightSlider_)
    {
        *processor.tubeEndRight_ = tubeEndRightSlider_.getValue();
        
        processor.lengRef_R = processor.leng_R + processor.mFilter.setLengt(*processor.tubeEndRight_);
        processor.delayMilliRef_R = processor.mFilter.setDelayMilliseconds(processor.lengRef_R);
        
        std::string delayText = createTextForDelays(processor.delayMilliRef_R);
        delayMsRefR_.setText(delayText);
        
    }
    else if (slider == &gainRefLeftSlider_)
    {
        *processor.gainRefLeft_ = gainRefLeftSlider_.getValue();
        //*processor.gainRefLeft_ = pow(10, gainRefLeftSlider_.getValue() / 20);
    }
    else if (slider == &gainRefRightSlider_)
    {
        *processor.gainRefRight_ = gainRefRightSlider_.getValue();
        //*processor.gainRefRight_ = pow(10, gainRefRightSlider_.getValue() / 20);
    }
    else if (slider == &widthSlider_)
    {
        *processor.width_ = widthSlider_.getValue();
    }
    else if (slider == &frequencyRateSlider_)
    {
        *processor.frequencyRate_ = frequencyRateSlider_.getValue();
    }
    else if(slider == &feedbackSlider_)
    {
        *processor.feedback_ = feedbackSlider_.getValue();
    }
}

//==============================================================================
void VirtualTubeChorusAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    
    g.setColour (Colours::white);
    g.setFont(15.0f);
}

void VirtualTubeChorusAudioProcessorEditor::resized()
{
    //Texts
    
    delayMsL_.setBounds (30, 70, 70, 20);
    
    delayMsR_.setBounds (300, 70, 70, 20);
    
    delayMsRefL_.setBounds (30, 200, 70, 20);
    
    delayMsRefR_.setBounds (300, 200, 70, 20);
    
    gainText_.setBounds (860, 5, 70, 20);
    
    tubeLengthText_.setBounds (240, 5, 110, 20);
    
    tubeEndText_.setBounds (220, 130, 140, 20);
    
    gainRefText_.setBounds (70, 240, 100, 20);
    
    //Sliders
    
    tubeLengthLeftSlider_.setBounds (30, 50, 250, 20);
    
    tubeLengthRightSlider_.setBounds (300, 50, 250, 20);
    
    gainLeftSlider_.setBounds (600, 50, 80, 100);
    
    gainRightSlider_.setBounds (700, 50, 80, 100);
    
    dryWetMixSlider_.setBounds (700, 290, 80, 100);
    
    tubeSizeSlider_.setBounds (700, 160, 80, 100);
    
    tubeEndLeftSlider_.setBounds (30, 180, 150, 20);
    
    tubeEndRightSlider_.setBounds (300, 180, 150, 20);
    
    gainRefLeftSlider_.setBounds (30, 290, 80, 100);
    
    gainRefRightSlider_.setBounds (130, 290, 80, 100);
    
    widthSlider_.setBounds (400, 290, 80, 100);
    
    frequencyRateSlider_.setBounds (500, 290, 80, 100);
    
    feedbackSlider_.setBounds (600, 290, 80, 100);

}
