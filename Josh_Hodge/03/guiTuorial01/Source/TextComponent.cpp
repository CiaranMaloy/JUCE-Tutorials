/*
  ==============================================================================

    TextComponent.cpp
    Created: 17 Sep 2022 6:33:06pm
    Author:  ciaran maloy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TextComponent.h"

//==============================================================================
TextComponent::TextComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TextComponent::~TextComponent()
{
}

void TextComponent::paint (juce::Graphics& g)
{
    juce::Font theFont("Copperplate", "Regular", 20.0f);
    g.setFont(theFont);
    g.drawText("The Audio Programmer", 10, 10, 400, 60, juce::Justification::topLeft);
}

void TextComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
