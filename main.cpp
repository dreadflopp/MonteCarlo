/**
 * @author Mattias Lindell
 * @date 180909
 * @desc Calculates PI using the Monte Carlo method
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include "MonteCarlo.h"
#include "CommandLineHandler.h"

using namespace std;

int main (int argc, char *argv[]) {
    // Default values for arguments
    int processes, darts = 0;

    // If this variable is zero after a fork, the process is a child
    pid_t childPid = 0;

    // parse arguments
    CommandLineHandler cmdLineHandler;
    if (!cmdLineHandler.parseArguments(argc, argv, processes, darts)) {
        fprintf(stderr, "Usage: %s processes darts\n", argv[0]);
        return 1;
    }

    if (processes < 1 || darts < 1) {
        fprintf(stderr, "Use positive integers as arguments\n");
        return 1;
    }

    // fork processes
    for (int i = 0; i < processes; i++) {
        if ((childPid = fork()) == 0) {
            break;
        } else if (childPid == -1) {
            fprintf(stderr, "Failed to create a process!\n");
            break;
        }
    }

    // If process is a child, calculate pi using monte carlo method
    if (childPid == 0) {
        MonteCarlo calculator;
        double pi = calculator.run(darts);

        // save result to a file
        std::ofstream file;
        file.open(std::to_string(getpid()));
        file << pi;
        file.close();
    }

    // If process is the main process
    else {
        // Wait for all
        vector<double> valuesOfPi; // stores all values of pi
        while (true) {
            int status;
            pid_t pid = wait(&status);

            if ((pid == -1) && (errno != EINTR)) {
                // no more child processes exists
                break;
            } else if (pid != -1) {
                // Check status
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    // Child terminated normally
                    // read pi from file
                    std::ifstream file;
                    file.open(std::to_string(pid));
                    double pi;
                    file >> pi;
                    file.close();

                    // store the value of pi
                    valuesOfPi.push_back(pi);

                    fprintf(stderr, "Process ID: %ld terminated normally with return status %d of PI: %f\n", (long) pid, WEXITSTATUS(status), pi);
                } else if (WIFEXITED(status)) {
                    int error = errno;
                    printf("Process ID: %ld terminated with return status %d: %s\n", (long) pid, WEXITSTATUS(status), strerror(errno));
                    errno = error;
                } else if (WIFSIGNALED(status)) {
                    int error = errno;
                    printf("Process ID: %ld terminated due to uncaught signal %d: %s\n", (long) pid, WTERMSIG(status), strerror(errno));
                    errno = error;
                } else if (WIFSTOPPED(status)) {
                    int error = errno;
                    printf("Process ID: %ld stopped due to signal %d: %s\n", (long) pid, WSTOPSIG(status), strerror(errno));
                    errno = error;
                }
                // create c string and remove file, does nothing if it doesn't exist
                char buffer[12];
                snprintf(buffer, 12, "%ld", (long) pid);
                std::remove(buffer);
            }
        }

        // Print an average value of pi
        if (!valuesOfPi.empty())  {
            double piSum = 0;
            for (auto e: valuesOfPi) {
                piSum += e;
            }

            printf("Average value of PI: %f\n", piSum / valuesOfPi.size());
        }
    }

    return 0;
}
