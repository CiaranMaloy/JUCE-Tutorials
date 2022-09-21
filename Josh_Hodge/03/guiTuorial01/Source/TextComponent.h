/*
  ==============================================================================

    TextComponent.h
    Created: 17 Sep 2022 6:33:06pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TextComponent  : public juce::Component
{
public:
    TextComponent();
    ~TextComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextComponent)
};
