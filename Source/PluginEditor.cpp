/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StafferAudioProcessorEditor::StafferAudioProcessorEditor (StafferAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), inputs(this), viewer()
{
    addAndMakeVisible(inputs);
    addAndMakeVisible(viewer);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1500, 800);
}

StafferAudioProcessorEditor::~StafferAudioProcessorEditor()
{
}

//==============================================================================
void StafferAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    repaint();
}

void StafferAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    auto headerHeight = 90;
    inputs.setBounds(area.removeFromTop(headerHeight));
    viewer.setBounds(area);
}

void StafferAudioProcessorEditor::adsrParamsChange(double attack, double decay, double sustain, double release)
{
    viewer.setParams(attack, decay, sustain, release);
}
