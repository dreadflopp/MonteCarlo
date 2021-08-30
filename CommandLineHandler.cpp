#include "CommandLineHandler.h"

bool CommandLineHandler::parseArguments(int argc, char **argv, int &processes, int &darts) {
    // only accept two arguments
    if (argc != 3)
        return false;

    // parse first argument
    std::istringstream firstArg(argv[1]);
    if (!(firstArg >> processes))
        return false;
    if (processes < 0)
        return false;

    // parse second argument
    std::istringstream secondArg(argv[2]);
    if (!(secondArg >> darts))
        return false;
    if (darts < 0)
        return false;

    return true;
}
