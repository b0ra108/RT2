#ifndef INTERVAL_H
#define INTERVAL_H

#include "utilities.hpp"
#include <limits>

class Interval{
    public:
        float min,max;
        Interval() : min(-std::numeric_limits<float>::infinity()), max(std::numeric_limits<float>::infinity()) {}
        Interval(float min, float max) : min(min), max(max) {}

        float size() const{
            return max - min;
        }

        bool contains(float x) const{
            return x >= min && x <= max;
        }

        bool surrounds(float x) const{
            return x > min && x < max;
        }
};

#endif