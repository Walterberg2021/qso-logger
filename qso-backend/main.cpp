#include <iostream>
#include "RadioUtils.h"
#include "QSO.h";
#include "Server.h"

using namespace std;

void testGrid(const string& grid)
{
    Coordinates coord = gridToCoordinates(grid);

    cout << "Grid: " << grid << endl;
    cout << "Latitude: " << coord.latitude << endl;
    cout << "Longitude: " << coord.longitude << endl;

    if (!isnan(coord.latitude) && !isnan(coord.longitude))
    {
        cout << "Back to grid: "
            << coordinatesToGrid(coord, static_cast<int>(grid.length()))
            << endl;
    }

    cout << "------------------------" << endl;
}

int main()
{
    //Coordinates toronto = { 43.7, -79.4 };
    //Coordinates berlin = { 52.52, 13.405 };

    //cout << "Toronto:" << endl;
    //cout << "2: " << coordinatesToGrid(toronto, 2) << endl;
    //cout << "4: " << coordinatesToGrid(toronto, 4) << endl;
    //cout << "6: " << coordinatesToGrid(toronto, 6) << endl;
    //cout << "8: " << coordinatesToGrid(toronto, 8) << endl;

    //cout << endl;

    //cout << "Berlin:" << endl;
    //cout << "2: " << coordinatesToGrid(berlin, 2) << endl;
    //cout << "4: " << coordinatesToGrid(berlin, 4) << endl;
    //cout << "6: " << coordinatesToGrid(berlin, 6) << endl;
    //cout << "8: " << coordinatesToGrid(berlin, 8) << endl;

    //cout << endl;

    //cout << "Validation:" << endl;

    //Coordinates invalidLat = { 100.0, -79.4 };
    //Coordinates invalidLon = { 43.7, 200.0 };

    //cout << "Invalid latitude: "
    //    << coordinatesToGrid(invalidLat, 4) << endl;

    //cout << "Invalid longitude: "
    //    << coordinatesToGrid(invalidLon, 4) << endl;

    //cout << "Invalid precision: "
    //    << coordinatesToGrid(toronto, 5) << endl;

    ////=========================================================

    //cout << "\n***\n";

    //testGrid("FN");
    //testGrid("FN03");
    //testGrid("FN03hq");
    //testGrid("FN03hq17");

    //testGrid("JO");
    //testGrid("JO62");
    //testGrid("JO62qm");
    //testGrid("JO62qm84");

    //cout << "\nInvalid tests:\n";

    //testGrid("ZZ03");
    //testGrid("FN0");
    //testGrid("FN03zz");
    //testGrid("ABC123");

    ////=========================================

    //cout << "\n***\n";

    //cout << "Toronto -> Berlin: " << calculateDistance(toronto, berlin) << " km\n";
    //cout << "Toronto -> Toronto: " << calculateDistance(toronto, toronto) << " km\n";

    //Coordinates montreal = { 45.5017, -73.5673 };
    //cout << "Toronto -> Montreal: " << calculateDistance(toronto, montreal) << " km\n";

    //Coordinates invalidLatitude = { 100.0, -79.4 };
    //cout << "Invalid latitude: " << calculateDistance(toronto, invalidLatitude) << " km\n";

    //Coordinates invalidLongitude = { 43.7, -200.0 };
    //cout << "Invalid longitude: " << calculateDistance(toronto, invalidLongitude) << " km\n";

    QSO qso;

    qso.setCorCall("VE3ABC");
    qso.setFrequency(12.250);
    qso.setMode("USB");
    qso.setTxRst("59");
    qso.setRxRst("57");
    qso.setNotes("Test QSO");

    Coordinates myLocation;
    myLocation.latitude = 43.73;
    myLocation.longitude = -79.76;

    qso.setMyCoordinates(myLocation);

    DateTime time;
    time.year = 2026;
    time.month = 9;
    time.day = 10;
    time.hour = 16;
    time.minute = 30;
    time.second = 0;

    qso.setQsoDateTime(time);

    qso.setCorGrid("FN03");
    qso.setCorLocationKnown(true);
    qso.setCorLocationFromGrid(true);

    if (qso.validate())
    {
        qso.updateDerivedFields();

        cout << "QSO valid\n";
        cout << "Call: " << qso.getCorCall() << '\n';
        cout << "Frequency: " << qso.getFrequency() << " MHz\n";
        cout << "Band: " << qso.getBand() << '\n';
        cout << "Mode: " << qso.getMode() << '\n';

        cout << "My grid: " << qso.getMyGrid() << '\n';
        cout << "Cor grid: " << qso.getCorGrid() << '\n';

        Coordinates cor = qso.getCorCoordinates();

        cout << "Cor latitude: " << cor.latitude << '\n';
        cout << "Cor longitude: " << cor.longitude << '\n';

        cout << "Distance: " << qso.getDistance() << " km\n";
    }
    else
    {
        cout << "QSO invalid\n";
    }

    startServer();

    return 0;
}