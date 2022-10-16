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

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        /* DOCS:
         Must return true if this voice object is capable of playing the given sound.

         If there are different classes of sound, and different classes of voice, a voice can choose which ones it wants to take on.

         A typical implementation of this method may just return true if there's only one type of voice and sound, or it might check the type of the sound object passed-in and see if it's one that it understands.
         */
        
        
    }
    
    //======================================================
    bool startNote(int midiNoteNumber, float velocity, SynthesisrSound* sound, int currentPitchWheelPosition)
    {
        /* DOCS:
         Called to start a new note.

         This will be called during the rendering callback, so must be fast and thread-safe.
         */
    }
    
    
    //======================================================
    bool stopNote (float velocity, bool allowTailOff)
    {
        /* DOCS:
         Called to stop a note.

         This will be called during the rendering callback, so must be fast and thread-safe.

         The velocity indicates how quickly the note was released - 0 is slowly, 1 is quickly.

         If allowTailOff is false or the voice doesn't want to tail-off, then it must stop all sound immediately, and must call clearCurrentNote() to reset the state of this voice and allow the synth to reassign it another sound.

         If allowTailOff is true and the voice decides to do a tail-off, then it's allowed to begin fading out its sound, and it can stop playing until it's finished. As soon as it finishes playing (during the rendering callback), it must make sure that it calls clearCurrentNote().
         */
    }
    
    //======================================================
    
    
    //======================================================
    int pitchWheelMoved (int newPitchWheel)
    {
        
    }
    
    //======================================================
    void controllerMoved ( int controllerNumber, int newControllerValue)
    {
        
    }
    
    //======================================================
    void renderNextBlock ( AudioBuffer<float>& ouputBuffer, int startSample, int endSample)
    {
        
    }
    
    //======================================================
    
private:
    
    
};

