#include <iostream>
#include <string>
#include <cmath>
#include <regex>
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
    regex gridPattern("^[A-Ra-r]{2}([0-9]{2}([A-Xa-x]{2}([0-9]{2})?)?)?$");

    if (!regex_match(grid, gridPattern))
    {
        cout << "Invalid grid\n";
        return { NAN, NAN };
    }
    Coordinates coord;

    coord.latitude = 0;
    coord.longitude = 0;

    string normGrid = grid;
    for (char& ch : normGrid)
    {
        ch = static_cast<char>(toupper(ch));
    }

    coord.longitude = (normGrid[0] - 'A') * 20;
    coord.latitude = (normGrid[1] - 'A') * 10;

    if (normGrid.length() >= 4) {

        coord.longitude += (normGrid[2] - '0') * 2;
        coord.latitude += (normGrid[3] - '0') * 1;

        if (normGrid.length() >= 6) {

            coord.longitude += (normGrid[4] - 'A') * (2.0 / 24.0);
            coord.latitude += (normGrid[5] - 'A') * (1.0 / 24.0);

            if (normGrid.length() == 8) {

                coord.longitude += (normGrid[6] - '0') * ((2.0 / 24.0) / 10.0);
                coord.latitude += (normGrid[7] - '0') * ((1.0 / 24.0) / 10.0);
            }
        }
    }

    switch (normGrid.length()) {
    case 2:
        coord.longitude += 10.0;
        coord.latitude += 5.0;
        break;

    case 4:
        coord.longitude += 1.0;
        coord.latitude += 0.5;
        break;

    case 6:
        coord.longitude += (2.0 / 24.0) / 2.0;
        coord.latitude += (1.0 / 24.0) / 2.0;
        break;

    case 8:
        coord.longitude += ((2.0 / 24.0) / 10.0) / 2.0;
        coord.latitude += ((1.0 / 24.0) / 10.0) / 2.0;
        break;
    }

    coord.longitude -= 180;
    coord.latitude -= 90;

    return coord;
}

string coordinatesToGrid(const Coordinates& coordinates, int precision) {

    if (coordinates.latitude < -90.0 || coordinates.latitude > 90.0)
    {
        return "Invalid";
    }

    if (coordinates.longitude < -180.0 || coordinates.longitude > 180.0)
    {
        return "Invalid";
    }

    if (precision != 2 &&
        precision != 4 &&
        precision != 6 &&
        precision != 8)
    {
        return "Invalid";
    }

    double lon = coordinates.longitude + 180;
    double lat = coordinates.latitude + 90;

    int lonField = lon / 20;
    double lonRem = fmod(lon, 20.0);

    int latField = lat / 10;
    double latRem = fmod(lat, 10.0);

    char lonChar = 'A' + lonField;
    char latChar = 'A' + latField;

    string code = "";
    code += lonChar;
    code += latChar;

    if (precision == 2) {
        return code;
    }
    else {
        int lonNum =  lonRem/ 2.0;
        lonRem = fmod(lonRem, 2.0);

        int latNum = latRem / 1.0;
        latRem = fmod(latRem, 1.0);

        code += to_string(lonNum);
        code += to_string(latNum);

        if (precision == 4) {
            return code;
        }
        else {
            int lonSub = lonRem / (2.0 / 24.0);
            lonRem = fmod(lonRem, (2.0 / 24.0));

            int latSub = latRem / (1.0 / 24.0);
            latRem = fmod(latRem, (1.0 / 24.0));

            code += ('a' + lonSub);
            code += ('a' + latSub);

            if (precision == 6) {
                return code;
            }
            else {
                int lonExtended = lonRem / ((2.0 / 24.0) / 10);
                int latExtended = latRem / ((1.0 / 24.0) / 10);

                code += to_string(lonExtended);
                code += to_string(latExtended);

                return code;
            }
        }
    }

}

double calculateDistance(const Coordinates& from, const Coordinates& to) {
    
    if (isnan(from.latitude) || isnan(from.longitude) ||
        isnan(to.latitude) || isnan(to.longitude))
    {
        return NAN;
    }

    if (from.latitude < -90 || from.latitude > 90 ||
        to.latitude < -90 || to.latitude > 90 ||
        from.longitude < -180 || from.longitude > 180 ||
        to.longitude < -180 || to.longitude > 180)
    {
        return NAN;
    }

    double pi = 3.14159265358979323846;
    double r = 6371.0; // km

    Coordinates radFrom = { (from.latitude * pi / 180), (from.longitude * pi / 180)};
    Coordinates radTo = { (to.latitude * pi / 180), (to.longitude * pi / 180) };

    double dLatRad = radTo.latitude - radFrom.latitude;
    double dLonRad = radTo.longitude - radFrom.longitude;

    double a = pow(sin(dLatRad / 2.0), 2) + cos(radFrom.latitude) * cos(radTo.latitude) * pow(sin(dLonRad / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return r * c;
}