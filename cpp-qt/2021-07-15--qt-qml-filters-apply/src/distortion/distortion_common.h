#ifndef DISTORTION_COMMON_H
#define DISTORTION_COMMON_H

#include <random>

namespace distortion {
    inline void swapIntIfFirstIsGreater(int &f, int &s) {
        if (f > s) {
            std::swap(f, s);
        }
    }

    inline void swapDoubleIfFirstIsGreater(double& f, double& s) {
        if (f > s) {
            std::swap(f, s);
        }
    }

    inline int randomInt(int min, int max) {
        swapIntIfFirstIsGreater(min, max);
        static std::random_device
          rd; // Will be used to obtain a seed for the random number engine
        static std::mt19937 gen(
          rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(min, max);

        return distrib(gen);
    }

    inline double randomReal(double min, double max) {
        swapDoubleIfFirstIsGreater(min, max);
        static std::random_device
          rd; // Will be used to obtain a seed for the random number engine
        static std::mt19937 gen(
          rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> distrib(min, max);

        return distrib(gen);
    }
}

#endif // DISTORTION_COMMON_H
