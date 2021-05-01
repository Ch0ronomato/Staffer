#include "ADSRInputs.h"
#include <JuceHeader.h>

ADSRInputs::ADSRInputs(ADSRListener *_l)
{
    l.reset(_l);
    setupSlider(attack);
    attack.setTextValueSuffix(" attack");
    addAndMakeVisible(attack);

    setupSlider(decay);
    decay.setTextValueSuffix(" decay");
    addAndMakeVisible(decay);

    setupSlider(sustain);
    sustain.setTextValueSuffix(" sustain");
    addAndMakeVisible(sustain);

    setupSlider(release);
    release.setTextValueSuffix(" release");
    addAndMakeVisible(release);
}

void ADSRInputs::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::grey);
}

void ADSRInputs::resized()
{
    // Is a component of components, so we're going ultra relative
    // when you remove from the left, it's mutating state. 

    auto bounds = getLocalBounds();
    bounds.removeFromTop(10);
    bounds.removeFromBottom(10);
    auto spacer = 50;
    attack.setBounds(bounds.removeFromLeft(spacer));
    bounds.removeFromLeft(spacer);
    decay.setBounds(bounds.removeFromLeft(spacer));
    bounds.removeFromLeft(spacer);
    sustain.setBounds(bounds.removeFromLeft(spacer));
    bounds.removeFromLeft(spacer);
    release.setBounds(bounds.removeFromLeft(spacer));
}

void ADSRInputs::setupSlider(juce::Slider &slider)
{
    slider.setRange(0, 127, 1.0);
    slider.setSliderStyle(juce::Slider::LinearBarVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    slider.setPopupDisplayEnabled(false, this, this);
    slider.addListener(this);
}

void ADSRInputs::sliderValueChanged(juce::Slider *slider)
{
    l->adsrParamsChange(attack.getValue(), decay.getValue(), sustain.getValue(), release.getValue());
}
