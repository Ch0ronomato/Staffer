/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StafferAudioProcessorEditor::StafferAudioProcessorEditor (StafferAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    attackParam.setSliderStyle(juce::Slider::LinearBarVertical);
    attackParam.setRange(0.0, 127.0, 1.0);
    attackParam.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    attackParam.setPopupDisplayEnabled(true, false, this);
    attackParam.setTextValueSuffix(" attack");
    attackParam.setValue(1.0);
    addAndMakeVisible(&attackParam);
    
    attackParam.addListener(this);
}

StafferAudioProcessorEditor::~StafferAudioProcessorEditor()
{
}

//==============================================================================
void StafferAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    
    g.setColour(juce::Colours::black);
    
    g.setFont(15.0f);
    
    g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    
    
    // paint the graph
    g.drawLine(juce::Line<float>(
                                 1.0f, (float)getWidth(), 1.0f, (float)getHeight()
                                 ));
    //DBG("I tried to draw a line");
}

void StafferAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    attackParam.setBounds (40, 30, 20, getHeight() - 60);
}

void StafferAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    audioProcessor.noteOnVel = attackParam.getValue();
}
