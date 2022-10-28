/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorial3AudioProcessor::GainTutorial3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER",
           {
    std::make_unique<juce::AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 0.0f, -15.0f)
})
#endif
{
}

GainTutorial3AudioProcessor::~GainTutorial3AudioProcessor()
{
}

//==============================================================================
const juce::String GainTutorial3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTutorial3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorial3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorial3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTutorial3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTutorial3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTutorial3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTutorial3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainTutorial3AudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTutorial3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainTutorial3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    auto sliderGainValue = treeState.getRawParameterValue(GAIN_ID);
    previousGain = juce::Decibels::decibelsToGain(sliderGainValue->load());
}

void GainTutorial3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTutorial3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainTutorial3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    auto sliderGainValue = treeState.getRawParameterValue(GAIN_ID);
    float sliderGainFloat = juce::Decibels::decibelsToGain(sliderGainValue->load());

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (sliderGainFloat == previousGain)
    {
        buffer.applyGain(sliderGainFloat);
    }
    else
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, sliderGainFloat);
        previousGain = sliderGainFloat;
    }
}

//==============================================================================
bool GainTutorial3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainTutorial3AudioProcessor::createEditor()
{
    return new GainTutorial3AudioProcessorEditor (*this);
}

//==============================================================================
void GainTutorial3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainTutorial3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTutorial3AudioProcessor();
}
