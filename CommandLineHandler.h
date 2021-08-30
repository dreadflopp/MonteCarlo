/**
 * @author Mattias Lindell
 * @date 180909
 * @desc class responsible for parsing arguments
 */

#ifndef COMMANDLINEHANDLER_H
#define COMMANDLINEHANDLER_H

#include <sstream>

class CommandLineHandler {
public:
    bool parseArguments(int argc, char *argv[], int &processes, int &darts);
};

#endif //COMMANDLINEHANDLER_H
