#pragma once

#include <JuceHeader.h>
#include <memory>
class ADSRInputs : public juce::Component, private juce::Slider::Listener
{

public:
    class ADSRListener
    {
    public: 
        virtual void adsrParamsChange(double, double, double, double) = 0;
    };
    ADSRInputs(ADSRListener*);
    void resized() override;
    void paint(juce::Graphics&) override;
private:
    juce::Slider attack;
    juce::Slider decay;
    juce::Slider sustain;
    juce::Slider release;
    std::unique_ptr<ADSRListener> l;
    void setupSlider(juce::Slider&); // can't setup popup with a const this -_-
    void sliderValueChanged(juce::Slider *slider) override;
};

