#include <string>
#include <thread>
#include <chrono> // per lo sleep

#include "Replay.h"
#include "FilesIO.h"

enum Arguments {
    invalidArgument, v, f
};

Arguments resolveArgument (std::string input) {
    if (input == "v") return v;
    if (input == "f") return f;

    return invalidArgument;
}

int main (int argc, char* argv[]) {
    return 0;
}

//std::this_thread::sleep_for(std::chrono::seconds(5));