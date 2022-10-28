/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CircularBufferAudioProcessor::CircularBufferAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

CircularBufferAudioProcessor::~CircularBufferAudioProcessor()
{
}

//==============================================================================
const juce::String CircularBufferAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CircularBufferAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CircularBufferAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CircularBufferAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CircularBufferAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CircularBufferAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CircularBufferAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CircularBufferAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CircularBufferAudioProcessor::getProgramName (int index)
{
    return {};
}

void CircularBufferAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CircularBufferAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // In prepareToPlay we just define
    const int numSeconds = 5;
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = numSeconds * (sampleRate + samplesPerBlock);
    
    mSampleRate = sampleRate;
    
    mDelayBuffer.setSize(numInputChannels, delayBufferSize); // uses the prepare to play function to set the initial size of the buffer
    
}

void CircularBufferAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CircularBufferAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CircularBufferAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    mStartGain  = JUCE_LIVE_CONSTANT(0.8);
    mEndGain = JUCE_LIVE_CONSTANT(0.8);
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    
    // this is the for loop that loops over the chanels
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // we need to read from the main buffer and then place that info into the delay buffer
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);
        float* dryBuffer = buffer.getWritePointer(channel);
        
        // what does this to??
        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        feedbackDelay(channel, bufferLength, delayBufferLength, dryBuffer);
    }
    
    // 2. once we have copied these values, we say:
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength; // this forces the value to wrap back around when we get to the end of the delay buffer
}

void CircularBufferAudioProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    // What do we do once the delay buffers hae reached the end of their length (it should wrap back around to the front)
    // 1. copy the data from the main buffer to the delay buffer
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, mStartGain, mEndGain);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, mStartGain, mEndGain);
        
        // now we've come to the end, we need to put the rest of the data back at the start of the buffer
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength-bufferRemaining, mStartGain, mEndGain);
    }
}

void CircularBufferAudioProcessor::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    int delayTime = JUCE_LIVE_CONSTANT(100); // ms (delay time, this should be a variable at some point)
    int n_ms_in_s = 1000; //
    const int readPosition = static_cast<int>(delayBufferLength + mWritePosition - (mSampleRate*delayTime/n_ms_in_s)) % delayBufferLength; // it is important that everything within this statis cast remains an int
    
    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
}

void CircularBufferAudioProcessor::feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer)
{
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, mStartGain, mEndGain);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, mStartGain, mEndGain);
        mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, mStartGain, mEndGain);
    }
}

//==============================================================================
bool CircularBufferAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CircularBufferAudioProcessor::createEditor()
{
    return new CircularBufferAudioProcessorEditor (*this);
}

//==============================================================================
void CircularBufferAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CircularBufferAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CircularBufferAudioProcessor();
}
