/*
  ==============================================================================

    Enviewer.cpp
    Created: 30 Apr 2021 5:17:16pm
    Author:  ischweer

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Enviewer.h"

//==============================================================================
Enviewer::Enviewer() : attack(0), decay(0), sustain(0), release(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Enviewer::~Enviewer()
{
}

void Enviewer::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    int attackEndX = bounds.getTopLeft().getX() + attack;
    int decayEndX = attackEndX + decay;
    int releaseStartX = bounds.getRight() - release;
    g.drawLine(bounds.getBottomLeft().getX(), bounds.getBottomLeft().getY(), attackEndX, bounds.getTopLeft().getY(), 2.0f);
    g.drawLine(attackEndX, bounds.getTopLeft().getY(), decayEndX, bounds.getBottom() - sustain, 2.0f);
    g.drawLine(decayEndX, bounds.getBottom() - sustain, releaseStartX, bounds.getBottom() - sustain, 2.0f);
    g.drawLine(releaseStartX, bounds.getBottom() - sustain, bounds.getBottomRight().getX(), bounds.getBottomRight().getY(), 2.0f);
}

void Enviewer::setParams(double _attack, double _decay, double _sustain, double _release)
{
    attack = _attack;
    decay = _decay;
    sustain = _sustain;
    release = _release;
}
