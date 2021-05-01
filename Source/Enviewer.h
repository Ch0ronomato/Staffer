/*
  ==============================================================================

    Enviewer.h
    Created: 30 Apr 2021 5:17:16pm
    Author:  ischweer

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Enviewer  : public juce::Component
{
public:
    Enviewer();
    ~Enviewer() override;

    void paint (juce::Graphics&) override;
    void setParams(double, double, double, double);
private:
    double attack;
    double decay; 
    double sustain;
    double release;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Enviewer)
};
