/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorial20AudioProcessorEditor::GainTutorial20AudioProcessorEditor (GainTutorial20AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Gain slider initialisation values
    double const gain_minimum = -60;
    double const gain_maximum = 0;
    double const gain_increment = 0.01;
    double const gain_initial = -20;
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mGainSlider.setRange(gain_minimum, gain_maximum, gain_increment);
    mGainSlider.setValue(gain_initial);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);
}

GainTutorial20AudioProcessorEditor::~GainTutorial20AudioProcessorEditor()
{
}

//==============================================================================
void GainTutorial20AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // Draw slider
    mGainSlider.setBounds(0, 0, getWidth()-BORDER/2.0f, getHeight()-BORDER/2.0f);
}

void GainTutorial20AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
void GainTutorial20AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mGainSlider)
    {
        audioProcessor.mGain = mGainSlider.getValue();
    }
}
