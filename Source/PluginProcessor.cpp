/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MinilogueParamsEnum.h"

//==============================================================================
StafferAudioProcessor::StafferAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

StafferAudioProcessor::~StafferAudioProcessor()
{
}

//==============================================================================
const juce::String StafferAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StafferAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StafferAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StafferAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StafferAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StafferAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StafferAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StafferAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StafferAudioProcessor::getProgramName (int index)
{
    return {};
}

void StafferAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StafferAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StafferAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StafferAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StafferAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    
    /**
            minilogue props:
            1. Attack: Maximum time is 00:20:03.10 - 00:22:21.28 = 00:02:18.18, roughly two seconds
            2. Decay: Max time seems to be roughly 15s
            3. Release: max time seems to be roughly 16s

            These parameters do not seem to be affected by the bpm set by the minilouge.
            Instead, perhaps adjusting to trying to map over time (meh?), I could instead
            try to map by the midi volumes. Because sustain is the only non time param, 
            we will have to give that one special treatment.

            Attack: From 0deg (straight up Y-axis) to 45deg
            Decay: From 0deg (straight down to sustain value) to 45deg
            Release: From 0deg (straight down to X axis *from* sustain point) to 45deg

            Sustain will go upward from the X axis
     
    */
    // non-destructive of the buffer. We're just reading values
    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        // const auto time = metadata.samplePosition;
        // we don't really need to record the message time in this case.
        if (message.isController())
        {
            auto parameterAmount = message.getControllerValue();
            if (message.isControllerOfType(ATTACK))
            {
                mAttackAmount = parameterAmount;
            }
            else if (message.isControllerOfType(DECAY))
            {
                mDecayAmount = parameterAmount;
            }
            else if (message.isControllerOfType(SUSTAIN))
            {
                mSustainAmount = parameterAmount;
            }
            else if (message.isControllerOfType(RELEASE))
            {
                mReleaseAmount = parameterAmount;
            }
        }
    }
}

//==============================================================================
bool StafferAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StafferAudioProcessor::createEditor()
{
    return new StafferAudioProcessorEditor (*this);
}

//==============================================================================
void StafferAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StafferAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StafferAudioProcessor();
}
