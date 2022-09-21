/*
  ==============================================================================

    GrassComponent.h
    Created: 17 Sep 2022 5:45:08pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GrassComponent  : public juce::Component
{
public:
    GrassComponent();
    ~GrassComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrassComponent)
};
