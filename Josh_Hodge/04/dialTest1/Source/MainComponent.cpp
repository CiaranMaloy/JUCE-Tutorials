#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    slider1.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(slider1);
    
    slider2.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(slider2);
    
    slider3.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider3.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(slider3);
    
    setSize(600, 400); // Need to set size for the window to exist
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::limegreen);
}

void MainComponent::resized()
{
    const int border = 10;
    
    juce::Rectangle<int> area = getLocalBounds();
    juce::Rectangle<int> dial_area = area.removeFromTop(area.getHeight()/2);
    
    slider1.setBounds(dial_area.removeFromLeft(area.getWidth()/2).reduced(border, border));
    slider2.setBounds(dial_area.removeFromRight(area.getWidth()/2).reduced(border, border));
    slider3.setBounds(area.removeFromBottom(area.getHeight()/2));
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
