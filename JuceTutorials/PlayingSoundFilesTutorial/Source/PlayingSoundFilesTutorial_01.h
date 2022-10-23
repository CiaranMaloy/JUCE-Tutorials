/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             PlayingSoundFilesTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Plays audio files.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public juce::AudioAppComponent,
                               public juce::ChangeListener,
public juce::Timer
{
public:
    // Step 2. Within the main component we configure three buttons
    MainContentComponent()
        : state (Stopped)
    {
        addAndMakeVisible (&openButton);
        openButton.setButtonText ("Open...");
        openButton.onClick = [this] { openButtonClicked(); };

        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.onClick = [this] { playButtonClicked(); };
        playButton.setColour (juce::TextButton::buttonColourId, juce::Colours::green);
        playButton.setEnabled (false);

        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.onClick = [this] { stopButtonClicked(); };
        stopButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
        stopButton.setEnabled (false);
        
        // TIME UPDATE : make a label and set the text
        addAndMakeVisible (&timeLabel);
        timeLabel.setText ("0", dontSendNotification);

        setSize (300, 200);

        // 4. Initialise the audio format manager
        formatManager.registerBasicFormats();       // [1]
        // 5. Add a change listener to the audio transport source to report changes e.g when it stops
        transportSource.addChangeListener (this);   // [2]

        setAudioChannels (0, 2);
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }

    // 9. prepareToPlay calls transportSource.prepareToPlay wich overrides the true virtual fuction
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    }

    // 8. All audio management is basically done by the audio transport source, which you getNextAudioBlock from and pass it the bufferToFill and it fills the buffer. This happens if readerSource.get() is not == a nullptr then itll fill the audiobuffer with the relevant buffer
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        if (readerSource.get() == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

        transportSource.getNextAudioBlock (bufferToFill);
    }
    
    // TIMER CALLBACK FOR PLAYHEAD
    void timerCallback() override
    {
        // this should get the current playtime
        auto currentTime = transportSource.getCurrentPosition();
        
        // time string
        auto ctime = std::to_string(currentTime);
        // set the text for the label to whatever the time is
        timeLabel.setText(ctime, dontSendNotification);
        
    }

    // 10. this true virtual function is also overridden, using transportSource
    void releaseResources() override
    {
        transportSource.releaseResources();
    }

    void resized() override
    {
        openButton.setBounds (10, 10, getWidth() - 20, 20);
        playButton.setBounds (10, 40, getWidth() - 20, 20);
        stopButton.setBounds (10, 70, getWidth() - 20, 20);
        timeLabel.setBounds (10, 100, getWidth() - 20, 20);
    }

    // 6. when a change to the audio transport function is made, this function will be called asyncronously on the message thread
    // PAUSE: 16. Logic is changed to handle pause and stop requests and what to change the state to in these cases
    void changeListenerCallback (juce::ChangeBroadcaster* source) override
    {
        if (source == &transportSource)
        {
            if (transportSource.isPlaying())
                changeState (Playing);
            else if ((state == Stopping) || (state == Playing))
                changeState (Stopped);
            else if (state == Pausing)
                changeState (Paused);
        }
    }

private:
    // Step 1. make an enum in the main component class
    // PAUSE: Step 14. add two states to the enum, pausing and paused
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };

    // 7. Changing the transport state is localised to this function
    // when Stopped is returned, it disables the stop button and sets the lay position to 0.0
    // when Starting is returned it disables the play button and starts the audio
    // when Playing is returned it enables the stop button
    // when Stopping is returned (i.e when the stop button has been pressed) it stopps the audio.
    // PAUSE 15. changeState needs to handle the two new states,
    // Pausing and Paused
    void changeState (TransportState newState)
    {
        if (state != newState)
        {
            state = newState;

            switch (state)
            {
                case Stopped:                           // [3]
                    stopButton.setButtonText("Play");
                    playButton.setButtonText("Stop");
                    stopButton.setEnabled(false);
                    transportSource.setPosition (0.0);
                    break;

                case Starting:                          // [4]
                    transportSource.start();
                    startTimer(10);
                    break;

                case Playing:                           // [5]
                    playButton.setButtonText("Pause");
                    stopButton.setButtonText("Stop");
                    stopButton.setEnabled (true);
                    break;
                    
                case Pausing:
                    transportSource.stop();
                    //stopTimer();
                    
                case Paused:
                    playButton.setButtonText("Resume");
                    stopButton.setButtonText("Return to Zero");
                    break;

                case Stopping:                          // [6]
                    transportSource.stop();
                    stopTimer();
                    timeLabel.setText("0", dontSendNotification);
                    break;
            }
        }
    }

    // 11. What to do when the open button is clicked: this opens a unique pointer to the file cooser object, which allows the user to open .wav files
    // the flags are what the object can do, i.e it opens and it can select files
    // inside this launchAsync is a lambda where:
    // the file is the result of the file getter.
    // if a file is selected then make a pointer to a format reader for the file
    // if the reader is valid (not nullptr) then a new reader object is initialised in a temporaty unique pointer incase there is already one in a pointer being used (? i dont understand this)
    // transportSource.setsource sets the newSource as the audio source as an audio source and checks that the samplerates allign, if they don't then re-sampling is handled internally.
    // Once a file is loaded then the play button is enabled.
    //
    void openButtonClicked()
    {
        chooser = std::make_unique<juce::FileChooser> ("Select a Wave file to play...",
                                                       juce::File{},
                                                       "*.wav");                     // [7]
        auto chooserFlags = juce::FileBrowserComponent::openMode
                          | juce::FileBrowserComponent::canSelectFiles;

        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc)           // [8]
        {
            auto file = fc.getResult();

            if (file != File{})                                                      // [9]
            {
                auto* reader = formatManager.createReaderFor (file);                 // [10]

                if (reader != nullptr)
                {
                    auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);   // [11]
                    transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);      // [12]
                    playButton.setEnabled (true);                                                      // [13]
                    readerSource.reset (newSource.release());                                          // [14]
                }
            }
        });
    }

    // 12. and 13. when the buttons are clicked, since everything has already been set up, you just need to change the state to play or stop
    // PAUSE: 17. if the play button is clicked and the current state is stopped or starting, then start, if it's clicked when the state is playing, then pause the audio
    // Same with the stop button, if the state is currently paused and the stop button is pressed, then the audio has already stopped playing, so the state only needs to be changed to stopped as opposed to 'stopping'.
    void playButtonClicked()
    {
        if ((state == Stopped) || (state == Paused))
            changeState (Starting);
        else if (state == Playing)
            changeState (Pausing);
    }

    void stopButtonClicked()
    {
        if (state == Paused)
            changeState (Stopped);
        else
            changeState (Stopping);
    }

    //==========================================================================
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    std::unique_ptr<juce::FileChooser> chooser;

    // 3. Other members of our mainComponent class
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    TransportState state;
    
    juce::Label timeLabel; // label that shows the time: should go below
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
