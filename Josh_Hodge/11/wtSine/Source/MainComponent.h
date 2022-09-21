#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    //===============================================================================
    void sliderValueChanged(juce::Slider* slider) override;
    void updateFrequency();
private:
    // Wavetable stuff
    juce::Array<float> waveTable;
    int wtSize;
    double frequency;
    double phase;
    double increment;
    double amplitude;
    double currentSampleRate;
    
    // Consts
    const int LEFT = 0;
    const int RIGHT = 1;
    
    // GUI Consts
    const int LABEL_SPACE = 100;
    const int BORDER = 20;
    
    // Sliders
    juce::Slider frequencySlider, amplitudeSlider;
    juce::Label frequencyLabel, amplitudeLabel;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
