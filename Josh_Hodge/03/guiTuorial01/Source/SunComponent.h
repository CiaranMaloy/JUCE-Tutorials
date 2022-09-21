/*
  ==============================================================================

    SunComponent.h
    Created: 17 Sep 2022 6:21:28pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SunComponent  : public juce::Component
{
public:
    SunComponent();
    ~SunComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunComponent)
};
