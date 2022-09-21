/*
  ==============================================================================

    RoofComponent.cpp
    Created: 17 Sep 2022 5:59:17pm
    Author:  ciaran maloy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RoofComponent.h"

//==============================================================================
RoofComponent::RoofComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

RoofComponent::~RoofComponent()
{
}

void RoofComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::red);
    juce::Path roof_outline;
    roof_outline.startNewSubPath(200, 190);
    roof_outline.lineTo(400, 190);
    roof_outline.lineTo(300, 140);
    roof_outline.closeSubPath();
    
    g.fillPath(roof_outline);
    g.strokePath(roof_outline, juce::PathStrokeType(2.0f));
}

void RoofComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
