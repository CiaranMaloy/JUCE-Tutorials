/*
  ==============================================================================

    ball.cpp
    Created: 28 Oct 2022 7:45:21am
    Author:  ciaran maloy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Ball.h"

//==============================================================================
Ball::Ball()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Ball::~Ball()
{
}

void Ball::paint (juce::Graphics& g)
{
    // declare rectangle object
    // what we need to do is change where the x and y coordinate 
    juce::Rectangle<float> area {posX, posY, size, size}; // {initX, initY, width, height}
    
    // First thing, paint the background black
    g.fillAll(juce::Colours::black);
    
    g.setColour(juce::Colours::goldenrod);
    g.drawEllipse(area, 2.0); // (bounding_box_rectangle, line_thickness)
    
    // Ball movement -----
    // X location
    // move the item when repaint is called
    posX += speedX;
    // the ball dissapears because it's always going positive in the X direction
    if (posX >= getWidth()-size || posX <= 0)
    {
        speedX = -speedX;
    }
    // Y location
    posY += speedY;
    if (posY >= getHeight()-size || posY <= 0)
    {
        speedY = -speedY;
    }
    // -----
    
    
}

void Ball::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
