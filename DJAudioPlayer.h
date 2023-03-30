/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 20 Mar 2023 4:51:10pm
    Author:  Alysha Hizam

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DJAudioPlayer : public juce::AudioSource {
    public:

        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void loadURL(juce::URL audioURL); //Reads the audio file from a URL
        void setGain(double gain); // Sets the audio gain from 0 to 1.0
        void setSpeed(double ratio); // Sets the speed from a ratio of 0 to 10.0
        void setPosition(double posInSecs); // Sets the position of the audio file from seconds
        void setPositionRelative(double pos); //Sets the position of the audio file from 0 to 1.0

        void start(); //Starts playing the audio file
        void stop(); //Stops playing the audio file

        /** get the relative position of the playhead*/
        double getPositionRelative();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DJAudioPlayer)
};
