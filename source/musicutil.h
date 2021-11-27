#ifndef MUSICUTIL_H
#define MUSICUTIL_H

#include <cstdint>
#include <string>

class MusicUtil
{
public:
    MusicUtil() = delete;

    struct Note
    {
        std::string letter{"C"};
        int octave{0};
    };

    static Note createNoteFromFrequency(double frequency);

    static double getFrequencyOfNote(const Note& note);
    static Note addSemitonesToNote(double semitones, const Note& note);

    static double getDistanceBetweenNotesInSemitones(const Note& lhs, const Note& rhs);
    static double getDistanceBetweenFrequenciesInSemitones(double f1, double f2);
    static double getDistanceBetweenFrequenciesInCents(double f1, double f2);

public:
    static constexpr double REFERENCE_FREQUENCY_C0 = 16.35159783;
    static constexpr double CENTS_IN_AN_OCTAVE = 1200.0;
    static constexpr double CENTS_IN_A_SEMITONE = 100.0;
    static constexpr std::size_t SEMITONES_IN_AN_OCTAVE = 12;
};

bool operator==(const MusicUtil::Note& lhs, const MusicUtil::Note& rhs);
bool operator!=(const MusicUtil::Note& lhs, const MusicUtil::Note& rhs);

#endif // MUSICUTIL_H
