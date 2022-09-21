#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Set the window size on initialisation
    setSize (600, 400);
    
    // Set parameters for the frequency slider
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000);
    frequencySlider.setTextValueSuffix("Hz");
    frequencySlider.addListener(this);
    frequencySlider.setValue(500);
    frequencySlider.setSkewFactorFromMidPoint(500);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 120, frequencySlider.getTextBoxHeight());
    
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);
    
    // Set parameters for the duration slider
    addAndMakeVisible(durationSlider);
    durationSlider.setRange(1.0/frequencySlider.getMaximum(), 1.0/frequencySlider.getMinimum());
    durationSlider.setTextValueSuffix("s");
    durationSlider.addListener(this);
    durationSlider.setSkewFactorFromMidPoint(1.0/500);
    durationSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 120, durationSlider.getTextBoxHeight());
    
    addAndMakeVisible(durationLabel);
    durationLabel.setText("Duration", juce::dontSendNotification);
    durationLabel.attachToComponent(&durationSlider, true);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    const int border = 120;
    
    frequencySlider.setBounds(border, 20, getWidth()-border, 20);
    durationSlider.setBounds(border, 50, getWidth()-border, 50);
}

void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &frequencySlider) durationSlider.setValue(1.0/frequencySlider.getValue());
    else if (slider == &durationSlider) frequencySlider.setValue(1.0/durationSlider.getValue());
}
