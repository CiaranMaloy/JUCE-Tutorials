#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // add a ball component to the main component as a child component
    addAndMakeVisible(ball);
    
    // in the main component, start the timer object and state its frequency
    int timerFreq = 60;
    juce::Timer::startTimerHz(timerFreq);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    juce::Timer::stopTimer();
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
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
    g.fillAll (juce::Colours::white);
    
}

void MainComponent::timerCallback()
{
    // this is the timer callback true virtual function, (effectively the callback in the timer thread)
    // we want to create something inside
    
    // This code is called all the time whether the window is open or not:
    // because it's in the timerCallbakc function
    // Ball movement -----
    // X location
    // move the item when repaint is called
    ball.posX += ball.speedX;
    // the ball dissapears because it's always going positive in the X direction
    if (ball.posX >= ball.getWidth()-ball.size || ball.posX <= 0)
    {
        ball.speedX = -ball.speedX;
    }
    // Y location
    ball.posY += ball.speedY;
    if (ball.posY >= ball.getHeight()-ball.size || ball.posY <= 0)
    {
        ball.speedY = -ball.speedY;
    }
    // -----
    
    ball.repaint();
    
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    ball.setBounds(getWidth()/2-100, getHeight()/2-100, 200, 200);
    //ball.setBounds(getLocalBounds());
}
