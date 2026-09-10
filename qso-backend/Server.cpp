#include "Server.h"
#include "external/httplib.h"

using namespace std;

void startServer()
{
    httplib::Server server;

    server.Get("/api/test",
        [](const httplib::Request& req, httplib::Response& res)
        {
            res.set_content("QSO backend is running", "text/plain");
        });

    server.Post("/api/qso",
        [](const httplib::Request& req, httplib::Response& res) {
            res.set_content("POST received", "text/plain");
        });

    server.listen("localhost", 8080);
}