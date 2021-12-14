#ifndef INPUTUTIL_H
#define INPUTUTIL_H

#include <string>
#include <vector>

/**
 * @brief A class of helper methods for selecting a suitable audio source.
 */
class InputUtil
{
public:
    InputUtil() = delete;

    /**
     * @brief Get a vector of all inputs detected by SFML.
     * @return Vector of device names as strings.
     */
    static std::vector<std::string> getAllInputs();

    /**
     * @brief Get the volume of an input.
     *
     * @details Determines the volume of the input by sampling from that input for a
     * very short timespan and then determining the root-mean-square volume.
     * @param input Device name as string.
     * @return Volume as root-mean-square value.
     */
    static double getVolumeOfInput(const std::string& input);

    /**
     * @brief Gets a vector of all inputs paired with their current volume level.
     * @return
     */
    static std::vector<std::pair<std::string, double>> getAllInputsWithVolumes();

    /**
     * @brief Get the input that is currently recording the loudest signal.
     * @return
     */
    static std::string getLoudestInput();
};

#endif // INPUTUTIL_H
