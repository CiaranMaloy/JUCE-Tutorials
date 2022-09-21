#include "MainComponent.h"
//#include <math.h>

// consts


//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    frequencySlider.setRange(50, 500);
    frequencySlider.setTextValueSuffix("Hz");
    frequencySlider.addListener(this);
    addAndMakeVisible(frequencySlider);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);
    
    amplitudeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    amplitudeSlider.setRange(0, 0.9);
    amplitudeSlider.setTextValueSuffix("peak");
    amplitudeSlider.addListener(this);
    addAndMakeVisible(amplitudeSlider);
    amplitudeLabel.setText("Amplitude", juce::dontSendNotification);
    amplitudeLabel.attachToComponent(&amplitudeSlider, true);
    

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    frequency = 440; // Hz
    phase = 0;
    wtSize = 1024; // value long array (is it since it's sored as a double)
    amplitude = 0.25;
    currentSampleRate = sampleRate;
    
    for (int i = 0; i < wtSize; i++)
    {
        waveTable.insert(i, sin(2.0 * juce::MathConstants<double>::pi * i / wtSize));
    }
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    
    float* const LEFT_SPEAKER = bufferToFill.buffer->getWritePointer(LEFT, bufferToFill.startSample);
    float* const RIGHT_SPEAKER = bufferToFill.buffer->getWritePointer(RIGHT, bufferToFill.startSample);
    
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        LEFT_SPEAKER[sample] = waveTable[(int)phase] * amplitude;
        RIGHT_SPEAKER[sample] = waveTable[(int)phase] * amplitude;
        updateFrequency();
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    frequencySlider.setBounds(LABEL_SPACE, 20, getWidth()-LABEL_SPACE, 20);
    amplitudeSlider.setBounds(LABEL_SPACE, 50, getWidth()-LABEL_SPACE, 50);
}
//===============================================================================
void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &frequencySlider)
    {
        frequency = frequencySlider.getValue();
    }
    else if (slider == &amplitudeSlider)
    {
        amplitude = amplitudeSlider.getValue();
    }
    
}

void MainComponent::updateFrequency()
{
    increment = frequency * wtSize / currentSampleRate;
    phase = fmod((phase + increment), wtSize);
}
