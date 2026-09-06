#include <iostream>
#include <string>
#include "Coordinates.h"
#include "RadioUtils.h"

using namespace std;

const BandRange bands[] = {
    {0.1357, 0.1378, "2200 m"},
    {0.4720, 0.4790, "630 m"},
    {1.8000, 2.0000, "160 m"},
    {3.5000, 4.0000, "80 m"},
    {5.3515, 5.3665, "60 m"},
    {7.0000, 7.3000, "40 m"},
    {10.1000, 10.1500, "30 m"},
    {14.0000, 14.3500, "20 m"},
    {18.0680, 18.1680, "17 m"},
    {21.0000, 21.4500, "15 m"},
    {24.8900, 24.9900, "12 m"},
    {28.0000, 29.7000, "10 m"},
    {50.0000, 54.0000, "6 m"},
    {144.0000, 148.0000, "2 m"},
    {430.0000, 450.0000, "70 cm"},
    {902.0000, 928.0000, "33 cm"}
};

const int bandCount = size(bands);

string getBandFromFrequency(double frq) {

    for (int i = 0; i < bandCount; i++) {
        if (frq >= bands[i].minFrequency && frq <= bands[i].maxFrequency) {
            return bands[i].bandName;
        }
    }

    return "unknown";
}

Coordinates gridToCoordinates(const string& grid) {

}

string coordinatesToGrid(const Coordinates& coordinates) {

}