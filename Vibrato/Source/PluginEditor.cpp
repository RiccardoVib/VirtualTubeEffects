/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeVibratoAudioProcessorEditor::VirtualTubeVibratoAudioProcessorEditor (VirtualTubeVibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
        delayTimeLeftLabel_("", "Left Channel:"), delayTimeRightLabel_("", "Right Channel:"), gainLeftLabel_("", "Left Channel:"), gainRightLabel_("", "Right Channel:"), tubeSizeLabel_("", "Tube Size (cm):"), delayTimeRefLeftLabel_("", "Left Channel:"),delayTimeRefRightLabel_("", "Right Channel:"), gainRefLeftLabel_("", "Left Channel:"),gainRefRightLabel_("", "Right Channel:"), frequencyRateLabel_("", "Frequency Rate:"), widthLabel_("", "Width:")
{
   
    setSize (800, 400);
    
    
    delayTimeLeftAttachment = new SliderAttachment(processor.parameters, "delayTimeLeft_", delayTimeLeftSlider_);
    delayTimeRightAttachment = new SliderAttachment(processor.parameters, "delayTimeRight_", delayTimeRightSlider_);
    gainLeftAttachment = new SliderAttachment(processor.parameters, "gainLeft_", gainLeftSlider_);
    gainRightAttachment = new SliderAttachment(processor.parameters, "gainRight_", gainRightSlider_);
    tubeSizeAttachment = new SliderAttachment(processor.parameters, "tubeSize_", tubeSizeSlider_);
    delayTimeRefLeftAttachment = new SliderAttachment(processor.parameters, "delayTimeRefLeft_", delayTimeRefLeftSlider_);
    delayTimeRefRightAttachment = new SliderAttachment(processor.parameters, "delayTimeRefRight_", delayTimeRefRightSlider_);
    gainRefLeftAttachment = new SliderAttachment(processor.parameters, "gainRefLeft_", gainRefLeftSlider_);
    gainRefRightAttachment = new SliderAttachment(processor.parameters, "gainRefRight_", gainRefRightSlider_);
    frequencyRateAttachment = new SliderAttachment(processor.parameters, "frequencyRate_", frequencyRateSlider_);
    widthAttachment = new SliderAttachment(processor.parameters, "width_", widthSlider_);
    
    delayTimeText_.setReadOnly(true);
    delayTimeText_.setText("Delay Time (ms)");
    addAndMakeVisible(&delayTimeText_);
    
    delayMsL_.setReadOnly(true);
    delayMsL_.setText(createTextForDelays(processor.delayMilli[0]));
    addAndMakeVisible (&delayMsL_);
    
    delayMsR_.setReadOnly(true);
    delayMsR_.setText(createTextForDelays(processor.delayMilli[1]));
    addAndMakeVisible (&delayMsR_);
    
    delayMsRefL_.setReadOnly(true);
    delayMsRefL_.setText(createTextForDelays(processor.delayMilliRef[0]));
    addAndMakeVisible (&delayMsRefL_);
    
    delayMsRefR_.setReadOnly(true);
    delayMsRefR_.setText(createTextForDelays(processor.delayMilliRef[1]));
    addAndMakeVisible (&delayMsRefR_);
    
    delayTimeLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayTimeLeftSlider_.setRange (3.0f, 10.0f, 0.01f);
    delayTimeLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTimeLeftSlider_.setPopupDisplayEnabled(false, false, this);
    delayTimeLeftSlider_.setTextValueSuffix(" ms");
    delayTimeLeftSlider_.setDoubleClickReturnValue(true, 3.0f);
    addAndMakeVisible (&delayTimeLeftSlider_);
    delayTimeLeftSlider_.addListener(this);
    
    delayTimeRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayTimeRightSlider_.setRange (3.0f, 10.0f, 0.01f);
    delayTimeRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTimeRightSlider_.setPopupDisplayEnabled (false, false, this);
    delayTimeRightSlider_.setTextValueSuffix(" ms");
    delayTimeRightSlider_.setDoubleClickReturnValue(true, 3.0f);
    addAndMakeVisible (&delayTimeRightSlider_);
    delayTimeRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainLeftSlider_.setRange (-128.0f, 9.0f, 0.01f);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" dB");
    gainLeftSlider_.setDoubleClickReturnValue(true, 0.0f);
    gainLeftSlider_.setSkewFactorFromMidPoint(0.0f);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRightSlider_.setRange (-128.0f, 9.0f, 0.01f);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" dB");
    gainRightSlider_.setDoubleClickReturnValue(true, 0.0f);
    gainRightSlider_.setSkewFactorFromMidPoint(0.0f);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeSizeSlider_.setRange (1.2f, 2.5f, 0.1f);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    tubeSizeSlider_.setDoubleClickReturnValue(true, 1.2f);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    delayTimeRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayTimeRefLeftSlider_.setRange (3.0f, 10.0f, 0.01f);
    delayTimeRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTimeRefLeftSlider_.setPopupDisplayEnabled(false, false, this);
    delayTimeRefLeftSlider_.setTextValueSuffix(" ms");
    delayTimeRefLeftSlider_.setDoubleClickReturnValue(true, 3.0f);
    addAndMakeVisible (&delayTimeRefLeftSlider_);
    delayTimeRefLeftSlider_.addListener(this);
    
    delayTimeRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayTimeRefRightSlider_.setRange (3.0f, 10.0f, 0.01f);
    delayTimeRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTimeRefRightSlider_.setPopupDisplayEnabled (false, false, this);
    delayTimeRefRightSlider_.setTextValueSuffix(" ms");
    delayTimeRefRightSlider_.setDoubleClickReturnValue(true, 3.0f);
    addAndMakeVisible (&delayTimeRefRightSlider_);
    delayTimeRefRightSlider_.addListener(this);
    
    gainRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefLeftSlider_.setRange (-128.0f, 19.0f, 0.01f);
    gainRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefLeftSlider_.setTextValueSuffix(" dB");
    gainRefLeftSlider_.setDoubleClickReturnValue(true, 0.0f);
    gainRefLeftSlider_.setSkewFactorFromMidPoint(0.0f);
    addAndMakeVisible (&gainRefLeftSlider_);
    gainRefLeftSlider_.addListener(this);
    
    gainRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefRightSlider_.setRange (-128.0f, 19.0f, 0.01f);
    gainRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefRightSlider_.setTextValueSuffix(" dB");
    gainRefRightSlider_.setDoubleClickReturnValue(true, 0.0f);
    gainRefRightSlider_.setSkewFactorFromMidPoint(0.0f);
    addAndMakeVisible (&gainRefRightSlider_);
    gainRefRightSlider_.addListener(this);
    
    widthSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider_.setRange (0.0f, 1.0f, 0.01f);
    widthSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    widthSlider_.setPopupDisplayEnabled (true, false, this);
    widthSlider_.setDoubleClickReturnValue(true, 0.0f);
    addAndMakeVisible (&widthSlider_);
    widthSlider_.addListener(this);
    
    frequencyRateSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    frequencyRateSlider_.setRange (2.0f, 14.0f, 0.01f);
    frequencyRateSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    frequencyRateSlider_.setPopupDisplayEnabled (true, false, this);
    frequencyRateSlider_.setDoubleClickReturnValue(true, 2.0f);
    addAndMakeVisible (&frequencyRateSlider_);
    frequencyRateSlider_.addListener(this);
 
    delayTimeLeftLabel_.attachToComponent(&delayTimeLeftSlider_, false);
    delayTimeLeftLabel_.setFont(Font (14.0f));
    
    delayTimeRightLabel_.attachToComponent(&delayTimeRightSlider_, false);
    delayTimeRefRightLabel_.setFont(Font (14.0f));
    
    gainLeftLabel_.attachToComponent(&gainLeftSlider_, false);
    gainLeftLabel_.setFont(Font (14.0f));
    
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (14.0f));
    
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (14.0f));
    
    delayTimeRefLeftLabel_.attachToComponent(&delayTimeRefLeftSlider_, false);
    delayTimeRefLeftLabel_.setFont(Font (14.0f));
    
    delayTimeRefRightLabel_.attachToComponent(&delayTimeRefRightSlider_, false);
    delayTimeRefRightLabel_.setFont(Font (14.0f));
    
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
    
}

VirtualTubeVibratoAudioProcessorEditor::~VirtualTubeVibratoAudioProcessorEditor()
{
}


void VirtualTubeVibratoAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &delayTimeLeftSlider_)
    {
        *processor.delayTimeLeft_ = delayTimeLeftSlider_.getValue();

        std::string delayText = createTextForDelays(delayTimeLeftSlider_.getValue());
        delayMsL_.setText(delayText);
        
    }
    else if (slider == &delayTimeRightSlider_)
    {
        *processor.delayTimeRight_ = delayTimeRightSlider_.getValue();
        
        std::string delayText = createTextForDelays(delayTimeRightSlider_.getValue());
        delayMsR_.setText(delayText);
    }
    else if (slider == &gainLeftSlider_)
    {
        *processor.gainLeft_ = gainLeftSlider_.getValue();
    }
    else if (slider == &gainRightSlider_)
    {
        *processor.gainRight_ = gainRightSlider_.getValue();
    }
    else if (slider == &tubeSizeSlider_)
    {
        *processor.tubeSize_ = tubeSizeSlider_.getValue();
    }
    else if (slider == &delayTimeRefLeftSlider_)
    {
        *processor.delayTimeRefLeft_ = delayTimeRefLeftSlider_.getValue();
        
        std::string delayText = createTextForDelays(delayTimeRefLeftSlider_.getValue());
        delayMsRefL_.setText(delayText);
        
    }
    else if (slider == &delayTimeRefRightSlider_)
    {
        *processor.delayTimeRefRight_ = delayTimeRefRightSlider_.getValue();
        
        std::string delayText = createTextForDelays(delayTimeRefRightSlider_.getValue());
        delayMsRefR_.setText(delayText);
    }
    else if (slider == &gainRefLeftSlider_)
    {
        *processor.gainRefLeft_ = gainRefLeftSlider_.getValue();
    }
    else if (slider == &gainRefRightSlider_)
    {
        *processor.gainRefRight_ = gainRefRightSlider_.getValue();
    }
    else if (slider == &widthSlider_)
    {
        *processor.width_ = widthSlider_.getValue();
    }
    else if (slider == &frequencyRateSlider_)
    {
        *processor.frequencyRate_ = frequencyRateSlider_.getValue();
    }
}

//==============================================================================
void VirtualTubeVibratoAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    
    g.setColour (Colours::white);
    g.setFont(15.0f);
}

void VirtualTubeVibratoAudioProcessorEditor::resized()
{
    
    //Texts
    
    delayMsL_.setBounds (35, 130, 70, 20);
    
    delayMsR_.setBounds (135, 130, 70, 20);
    
    delayMsRefL_.setBounds (35, 260, 70, 20);
    
    delayMsRefR_.setBounds (135, 260, 70, 20);
    
    delayTimeText_.setBounds (100, 5, 110, 20);
    
    //Sliders
    
    delayTimeLeftSlider_.setBounds (30, 50, 80, 100);
    
    delayTimeRightSlider_.setBounds (130, 50, 80, 100);
    
    delayTimeRefLeftSlider_.setBounds (30, 180, 80, 100);
    
    delayTimeRefRightSlider_.setBounds (130, 180, 80, 100);
    
    gainLeftSlider_.setBounds (600, 50, 80, 100);
    
    gainRightSlider_.setBounds (700, 50, 80, 100);
        
    tubeSizeSlider_.setBounds (230, 290, 80, 100);
    
    gainRefLeftSlider_.setBounds (600, 180, 80, 100);
    
    gainRefRightSlider_.setBounds (700, 180, 80, 100);
    
    widthSlider_.setBounds (330, 290, 80, 100);
    
    frequencyRateSlider_.setBounds (430, 290, 80, 100);
    

    
}
