#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    setAudioChannels (0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    juce::String message;
    message << "Preparing to play audio.... \n";
    message << " SamplesPerBlockEpected = " << samplesPerBlockExpected << "\n";
    message << " Samplerate = " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog(message);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // 1. Iterate over each channel
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        // this buffer value is a pointer to the buffer within the bufferToFill object, which points to the getWrite pointer of the start sample of each channel.
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        
        // populate the buffer with samples between -0.25 an 0.25
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            buffer[sample] = ((random.nextFloat()* 2.0f ) - 1.0f) * 0.25;
        }
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
}
