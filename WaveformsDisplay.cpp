/*
  ==============================================================================

    WaveformsDisplay.cpp
    Created: 20 Mar 2023 4:51:25pm
    Author:  Alysha Hizam

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformsDisplay.h"

//==============================================================================
WaveformsDisplay::WaveformsDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse)
                                    : audioThumb(1000,formatManagerToUse,cacheToUse),
                                      fileLoaded(false),
                                      position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformsDisplay::~WaveformsDisplay()
{
}

void WaveformsDisplay::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::mediumaquamarine);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::orange);
    if (fileLoaded) {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f);
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 30, getHeight());
    } else {
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }

    
}

void WaveformsDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformsDisplay::loadURL(juce::URL audioURL) {
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
}

void WaveformsDisplay::changeListenerCallback(juce::ChangeBroadcaster* source) {
    repaint();
}

void WaveformsDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;
        repaint();
    }
    
}
