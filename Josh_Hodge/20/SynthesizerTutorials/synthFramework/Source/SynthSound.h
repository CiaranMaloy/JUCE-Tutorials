/*
  ==============================================================================

    SynthSound.h
    Created: 15 Oct 2022 6:40:36pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int /*midi note number*/)
    {
        return true;
    }
    bool appliesToChannel (int /*midi channel*/)
    {
        return true;
    }
};
