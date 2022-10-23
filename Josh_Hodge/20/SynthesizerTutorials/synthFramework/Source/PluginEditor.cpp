/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // Add the attack slider to the editor
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.f);
    attackSlider.setValue(0.1);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20, 10);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    sliderTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    // there are much better ways of putting UI elements here (drawing bounding boxes and putting them there)
    attackSlider.setBounds(10, 10, 20, 100);
    
}

void SynthFrameworkAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // what to do when a slider's value has changed (update relevant params).
    if (slider == &attackSlider)
    {
        audioProcessor.attack_time = attackSlider.getValue();
    }
}
