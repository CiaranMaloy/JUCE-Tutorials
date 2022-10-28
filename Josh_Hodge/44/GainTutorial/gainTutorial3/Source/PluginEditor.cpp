/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorial3AudioProcessorEditor::GainTutorial3AudioProcessorEditor (GainTutorial3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    sliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, GAIN_ID, gainSlider);
    
    setSize (200, 200);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0f, 0.0f);
    gainSlider.setValue(-15.0f);
    addAndMakeVisible(&gainSlider);
    
}

GainTutorial3AudioProcessorEditor::~GainTutorial3AudioProcessorEditor()
{
}

//==============================================================================
void GainTutorial3AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void GainTutorial3AudioProcessorEditor::resized()
{
    // Lets do this using bounding boxes --- ::
    auto bounds = getLocalBounds();
    auto gainSliderArea = bounds;
    gainSliderArea.setWidth(100);
    
    
    gainSlider.setBounds(gainSliderArea);
}
