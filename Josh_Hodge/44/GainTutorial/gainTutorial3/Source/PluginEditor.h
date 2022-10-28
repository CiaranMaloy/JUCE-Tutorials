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
class GainTutorial3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GainTutorial3AudioProcessorEditor (GainTutorial3AudioProcessor&);
    ~GainTutorial3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainTutorial3AudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    
public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTutorial3AudioProcessorEditor)
};
