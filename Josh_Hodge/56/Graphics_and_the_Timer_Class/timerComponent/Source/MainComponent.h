#pragma once

#include <JuceHeader.h>
#include "Ball.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
public juce::Timer // timer is a pure virtual method which means that the way that it interacts with everything is already defined.
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void timerCallback() override; // this is the juce::Timer main virtual function 

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    Ball ball;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
