#include "Server.h"
#include "QSO.h"
#include "external/httplib.h"
#include "external/json.hpp"

using namespace std;

using json = nlohmann::json;

DateTime parseDateTime(const json& data) {
    json dt = data["dateTime"];
    DateTime qsoDateTime;

    qsoDateTime.year = dt["year"].get<int>();
    qsoDateTime.month = dt["month"].get<int>();
    qsoDateTime.day = dt["day"].get<int>();
    qsoDateTime.hour = dt["hour"].get<int>();
    qsoDateTime.minute = dt["minute"].get<int>();
    qsoDateTime.second = dt["second"].get<int>();

    return qsoDateTime;
}

void qsoPostHandler(const httplib::Request& req, httplib::Response& res) {

    try {
        json data = json::parse(req.body);

        string corCall = data["corCall"].get<string>();
        double frequency = data["frequency"].get<double>();
        string mode = data["mode"].get<string>();

        DateTime qsoDateTime = parseDateTime(data);

        QSO qso;

        qso.setCorCall(corCall);
        qso.setFrequency(frequency);
        qso.setMode(mode);
        qso.setQsoDateTime(qsoDateTime);

        if (qso.validate()) {
            qso.updateDerivedFields();
            res.status = 201;
        }
        else {
            res.status = 400;
            res.set_content("Invalid QSO data", "text/plain");
        }
    }
    catch (const nlohmann::json::exception& e) {
        cout << "json error: \n" << e.what() << "\n***" << endl;

        res.status = 400;
        res.set_content("Json error", "text/plain");

        return;
    }

    /*res.set_content(out, "text/plain");*/
}

void startServer()
{
    httplib::Server server;

    server.Get("/api/test",
        [](const httplib::Request& req, httplib::Response& res)
        {
            res.set_content("QSO backend is running", "text/plain");
        });

    server.Post("/api/qso", qsoPostHandler);

    server.listen("localhost", 8080);
}