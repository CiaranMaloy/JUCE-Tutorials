/*
  ==============================================================================

    SunComponent.cpp
    Created: 17 Sep 2022 6:21:28pm
    Author:  ciaran maloy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SunComponent.h"

//==============================================================================
SunComponent::SunComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SunComponent::~SunComponent()
{
}

void SunComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::yellow);
    g.drawEllipse(75, 75, 50, 50, 10.0f);
}

void SunComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
