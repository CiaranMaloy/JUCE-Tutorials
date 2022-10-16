/*
  ==============================================================================

    SynthSound.h
    Created: 15 Oct 2022 6:40:36pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int /*midi note number*/)
    {
        return true;
    }
    bool appliesToCHannel (int /*midi channel*/)
    {
        return true;
    }
};
