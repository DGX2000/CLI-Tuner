#include "musicutil.h"

#include <array>
#include <cmath>
#include <map>
#include <string>

MusicUtil::Note MusicUtil::createNoteFromFrequency(double frequency)
{
    auto semitones = getDistanceBetweenFrequenciesInSemitones(frequency, REFERENCE_FREQUENCY_C0);
    return addSemitonesToNote(semitones, Note{});
}

double MusicUtil::getFrequencyOfNote(const Note &note)
{
    static const std::map<std::string, int> NOTE_LETTER_TO_SEMITONE =
    {
        {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
        {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
    };

    auto frequencyWithOctavesApplied = REFERENCE_FREQUENCY_C0 * std::pow(2, note.octave);
    auto frequencyWithSemitonesApplied =
            frequencyWithOctavesApplied * std::pow(1.059463094, NOTE_LETTER_TO_SEMITONE.at(note.letter));

    return frequencyWithSemitonesApplied;
}

MusicUtil::Note MusicUtil::addSemitonesToNote(double semitones, const Note &note)
{
    static const std::array<std::string, 12> NOTE_LETTERS =
    {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };

    semitones += getDistanceBetweenNotesInSemitones(note, Note{});

    // TODO: Make this handle negative semitones
    auto letterIndex = static_cast<std::size_t>(semitones) % SEMITONES_IN_AN_OCTAVE;
    auto octave = static_cast<int>(semitones / SEMITONES_IN_AN_OCTAVE);

    return Note{NOTE_LETTERS.at(letterIndex), octave};
}

double MusicUtil::getDistanceBetweenNotesInSemitones(const Note &lhs, const Note &rhs)
{
    // TODO: Complete this function
    // TODO: Change type for semitones to int
    return 0.0;
}

double MusicUtil::getDistanceBetweenFrequenciesInSemitones(double f1, double f2)
{
    return std::round(getDistanceBetweenFrequenciesInCents(f1, f2) / CENTS_IN_A_SEMITONE);
}

double MusicUtil::getDistanceBetweenFrequenciesInCents(double f1, double f2)
{
    return CENTS_IN_AN_OCTAVE * std::log2(f1 / f2);
}

bool operator==(const MusicUtil::Note& lhs, const MusicUtil::Note& rhs)
{
    return (lhs.letter == rhs.letter) && (lhs.octave == rhs.octave);
}

bool operator!=(const MusicUtil::Note& lhs, const MusicUtil::Note& rhs)
{
    return !(lhs == rhs);
}
