#include "MonteCarlo.h"

double MonteCarlo::run(int n) {
    // if n has an invalid value, the class will write pi as -1,
    double pi = -1;

    if (n > 0) {
        // Create random double generator
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_real_distribution<double> dis(-1, 1);

        // throw darts
        double hits = 0;
        for (int i = 0; i < n; i++) {
            double x = dis(gen);
            double y = dis(gen);

            // if (x*x + y*y) <= 1, it's a hit
            if ((x*x + y*y) <= 1) {
                hits++;
            }
        }

        // Area of circle is hits percentage times the area of the square
        // ie 4 * hits/n
        // PI equals area of circle / radius*radius
        // ie PI equals area of circle
        pi = 4 * hits / n;
    }
    return pi;
}
