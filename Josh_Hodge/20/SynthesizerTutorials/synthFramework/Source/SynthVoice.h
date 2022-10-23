/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Oct 2022 6:41:02pm
    Author:  ciaran maloy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "src/maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound)
    {
        /* DOCS:
         Must return true if this voice object is capable of playing the given sound.

         If there are different classes of sound, and different classes of voice, a voice can choose which ones it wants to take on.

         A typical implementation of this method may just return true if there's only one type of voice and sound, or it might check the type of the sound object passed-in and see if it's one that it understands.
         */
        
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void getParam (float* attack)
    {
        env1.setAttack(double(*attack));
    }
    
    //======================================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        /* DOCS:
         Called to start a new note.

         This will be called during the rendering callback, so must be fast and thread-safe.
         */
        
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        //std::cout << midiNoteNumber << std::endl;
        
    }
    
    
    //======================================================
    void stopNote (float velocity, bool allowTailOff)
    {
        /* DOCS:
         Called to stop a note.

         This will be called during the rendering callback, so must be fast and thread-safe.

         The velocity indicates how quickly the note was released - 0 is slowly, 1 is quickly.

         If allowTailOff is false or the voice doesn't want to tail-off, then it must stop all sound immediately, and must call clearCurrentNote() to reset the state of this voice and allow the synth to reassign it another sound.

         If allowTailOff is true and the voice decides to do a tail-off, then it's allowed to begin fading out its sound, and it can stop playing until it's finished. As soon as it finishes playing (during the rendering callback), it must make sure that it calls clearCurrentNote().
         */
        env1.trigger = 0;
        
        allowTailOff = true;
        
        if (velocity == 0) clearCurrentNote();
        
    }
    
    //======================================================
    
    
    //======================================================
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //======================================================
    void controllerMoved ( int controllerNumber, int newControllerValue)
    {
        
    }
    
    //======================================================
    void renderNextBlock ( juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        // something in here
        env1.setAttack(2000);
        env1.setDecay (500);
        env1.setSustain(0.8);
        env1.setRelease(2000);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, 100, 0.1);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            
            ++startSample;
        }
    }
    
    //======================================================
    
private:
    double level;
    double frequency;
    
    //
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
    
};

