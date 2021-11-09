#include <catch2/catch.hpp>

#include "musicutil.h"

bool wasNoteCreatedCorrectly(double frequency, std::string letter, int octave)
{
    auto note = MusicUtil::createNoteFromFrequency(frequency);
    return note == MusicUtil::Note{letter, octave};
}

TEST_CASE("Note closest to frequency is correctly created")
{
    SECTION("Exactly on the frequency")
    {
        REQUIRE(wasNoteCreatedCorrectly(440.0, "A", 4));
        REQUIRE(wasNoteCreatedCorrectly(82.41, "E", 2));
        REQUIRE(wasNoteCreatedCorrectly(2217.46, "C#", 7));
        REQUIRE(wasNoteCreatedCorrectly(30.87, "B", 0));
        REQUIRE(wasNoteCreatedCorrectly(261.63, "C", 4));
        REQUIRE(wasNoteCreatedCorrectly(329.63, "E", 4));
        REQUIRE(wasNoteCreatedCorrectly(16.35, "C", 0));
    }
}
