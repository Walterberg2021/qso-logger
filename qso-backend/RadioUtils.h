#ifndef RADIO_UTILS_H
#define RADIO_UTILS_H

#include <string>
#include "Coordinates.h"

std::string getBandFromFrequency(double frequency);

Coordinates gridToCoordinates(const std::string& grid);

std::string coordinatesToGrid(const Coordinates& coordinates);

double calculateDistance(const Coordinates& from, const Coordinates& to
);

struct BandRange {
    double minFrequency;
    double maxFrequency;
    std::string bandName;
};

#endif
