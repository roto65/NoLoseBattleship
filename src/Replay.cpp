#include <string>

#include "Replay.h"

enum Arguments {
    invalidArgument, v, f
};

Arguments resolveArgument(std::string input) {
    if (input == "v") return v;
    if (input == "f") return f;

    return invalidArgument;
}

int main (int argc, char* argv[]) {
    return 0;
}