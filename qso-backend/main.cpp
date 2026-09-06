#include <iostream>
#include "RadioUtils.h"

using namespace std;

int main()
{
    Coordinates toronto = { 43.7, -79.4 };
    Coordinates berlin = { 52.52, 13.405 };

    cout << "Toronto:" << endl;
    cout << "2: " << coordinatesToGrid(toronto, 2) << endl;
    cout << "4: " << coordinatesToGrid(toronto, 4) << endl;
    cout << "6: " << coordinatesToGrid(toronto, 6) << endl;
    cout << "8: " << coordinatesToGrid(toronto, 8) << endl;

    cout << endl;

    cout << "Berlin:" << endl;
    cout << "2: " << coordinatesToGrid(berlin, 2) << endl;
    cout << "4: " << coordinatesToGrid(berlin, 4) << endl;
    cout << "6: " << coordinatesToGrid(berlin, 6) << endl;
    cout << "8: " << coordinatesToGrid(berlin, 8) << endl;

    cout << endl;

    cout << "Validation:" << endl;

    Coordinates invalidLat = { 100.0, -79.4 };
    Coordinates invalidLon = { 43.7, 200.0 };

    cout << "Invalid latitude: "
        << coordinatesToGrid(invalidLat, 4) << endl;

    cout << "Invalid longitude: "
        << coordinatesToGrid(invalidLon, 4) << endl;

    cout << "Invalid precision: "
        << coordinatesToGrid(toronto, 5) << endl;

    return 0;
}