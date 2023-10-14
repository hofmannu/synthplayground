// a simple test to see if we can playback a tone
#include "catch2/catch.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <thread>

#include "player.h"

TEST_CASE("Playing a random noise tone", "player") {
    player p(2, 44100);

    // sleep for a second
    std::this_thread::sleep_for(std::chrono::seconds(1));


}