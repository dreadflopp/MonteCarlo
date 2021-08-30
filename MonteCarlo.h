/**
 * @author Mattias Lindell
 * @date 180909
 * @desc Class responsible for calculations
 */

#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <random>
#include <fstream>
#include <unistd.h>

class MonteCarlo {
public:
    double run(int n);
};

#endif // MONTECARLO_H
