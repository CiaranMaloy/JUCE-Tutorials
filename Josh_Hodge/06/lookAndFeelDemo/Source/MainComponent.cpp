#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible(dial1);
    addAndMakeVisible(dial2);
    
    dial1.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dial1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    
    dial2.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dial2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    
    getLookAndFeel().setColour(<#int colourId#>, <#Colour colour#>);
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void MainComponent::resized()
{
    const int BORDER=20;
    const int DIAL_WIDTH=getWidth()/2 - BORDER;
    const int DIAL_HEIGHT=getHeight() - BORDER - 100;
    
    dial1.setBounds(BORDER, BORDER, DIAL_WIDTH, DIAL_HEIGHT);
    dial2.setBounds(getWidth()/2, BORDER, DIAL_WIDTH, DIAL_HEIGHT);
    
}
