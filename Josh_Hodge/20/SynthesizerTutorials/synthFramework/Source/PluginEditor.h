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
class SynthFrameworkAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener /* if the slider value s changed, then relay over to processor */
{
public:
    SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor&);
    ~SynthFrameworkAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& audioProcessor;
    
    juce::AudioProcessorValueTreeState::SliderAttachment sliderTree;

    juce::Slider attackSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameworkAudioProcessorEditor)
};
