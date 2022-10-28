/*
  ==============================================================================

    ball.h
    Created: 28 Oct 2022 7:45:21am
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Ball  : public juce::Component
{
public:
    Ball();
    ~Ball() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    float posX{10};
    float posY{70};
    float speedX{1};
    float speedY{1.5};
    float size{20};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ball)
};
