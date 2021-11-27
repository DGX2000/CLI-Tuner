#include "inpututil.h"

#include <chrono>
#include <thread>
#include <tuple>

#include <SFML/Audio.hpp>

#include "audioutil.h"

std::vector<std::string> InputUtil::getAllInputs()
{
    return sf::SoundRecorder::getAvailableDevices();
}

double InputUtil::getVolumeOfInput(const std::string &input)
{
    auto recorder = sf::SoundBufferRecorder();
    recorder.setDevice(input);

    recorder.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    recorder.stop();

    const auto& buffer = recorder.getBuffer();
    return AudioUtil::computeRmsVolume(AudioUtil::Signal{buffer.getSamples(), buffer.getSampleCount()});
}

std::vector<std::pair<std::string, double> > InputUtil::getAllInputsWithVolumes()
{
    auto inputs = getAllInputs();
    auto inputVolumePairs = std::vector<std::pair<std::string, double>>();

    for(const auto& input : inputs)
    {
        // TODO: Spawn threads for these
        inputVolumePairs.emplace_back(std::pair(input, getVolumeOfInput(input)));
    }

    return inputVolumePairs;
}

std::string InputUtil::getLoudestInput()
{
    auto inputVolumePairs = getAllInputsWithVolumes();

    auto maxVolumePair =
            std::max_element(inputVolumePairs.begin(), inputVolumePairs.end(),
                             [](const auto& lhs, const auto& rhs)
    {
        return lhs.second < rhs.second;
    });

    return maxVolumePair->first;
}
