#ifndef TUNINGMEDIATOR_H
#define TUNINGMEDIATOR_H

#include <memory>
#include <string>

#include "sampler.h"

class TuningMediator
{
public:
    TuningMediator();
    ~TuningMediator();

    double getFundamentalFrequency() const;
    double getVolume() const;

    void setInput(const std::string& name);
    std::string getInput() const;

private:
    std::unique_ptr<Sampler> sampler;
};

#endif // TUNINGMEDIATOR_H
