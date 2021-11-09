#include "tuningmediator.h"

#include "audioutil.h"
#include "inpututil.h"

TuningMediator::TuningMediator()
{
    auto loudestInput = InputUtil::getLoudestInput();

    // TODO: Make the frequency range adjustable
    // - Convert minimum frequency of range into minimum sampling time needed
    //   to detect that frequency
    sampler = std::make_unique<Sampler>(sf::milliseconds(32));
    sampler->setDevice(loudestInput);
    sampler->start();
}

TuningMediator::~TuningMediator()
{
    sampler->stop();
}

double TuningMediator::getFundamentalFrequency() const
{
    auto fundamentalPeriod = sampler->getCurrentlyDetectedPeriod();
    return AudioUtil::periodToFrequency(fundamentalPeriod, sampler->getSampleRate());
}

double TuningMediator::getVolume() const
{
    return AudioUtil::rmsVolumeToDecibels(sampler->getCurrentVolume());
}

void TuningMediator::setInput(const std::string& name)
{
    sampler->stop();
    sampler->setDevice(name);
    sampler->start();
}
