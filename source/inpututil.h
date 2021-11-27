#ifndef INPUTUTIL_H
#define INPUTUTIL_H

#include <string>
#include <vector>

class InputUtil
{
public:
    InputUtil() = delete;

    static std::vector<std::string> getAllInputs();
    static double getVolumeOfInput(const std::string& input);
    static std::vector<std::pair<std::string, double>> getAllInputsWithVolumes();
    static std::string getLoudestInput();
};

#endif // INPUTUTIL_H
