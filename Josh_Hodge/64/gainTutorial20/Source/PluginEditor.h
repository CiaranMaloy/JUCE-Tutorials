/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainTutorial20AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    GainTutorial20AudioProcessorEditor (GainTutorial20AudioProcessor&);
    ~GainTutorial20AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void sliderValueChanged(juce::Slider*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Slider mGainSlider;
    
    GainTutorial20AudioProcessor& audioProcessor;

    // consts
    const double BORDER = 100;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTutorial20AudioProcessorEditor)
};
