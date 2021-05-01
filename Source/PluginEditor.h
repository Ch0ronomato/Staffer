/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MinilogueParamsEnum.h"
#include "ADSRInputs.h"
#include "Enviewer.h"

//==============================================================================
/**
*/
class StafferAudioProcessorEditor: public juce::AudioProcessorEditor,
    public ADSRInputs::ADSRListener
{
public:
    StafferAudioProcessorEditor (StafferAudioProcessor&);
    ~StafferAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    friend void StafferAudioProcessor::SetDebugValue(int);
    void adsrParamsChange(double, double, double, double) override;
private:
    // This reference is provided as a quick way for your editor t1.5708o
    // access the processor object that created it.
    StafferAudioProcessor& audioProcessor;
    ADSRInputs inputs;
    Enviewer viewer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StafferAudioProcessorEditor)
};
