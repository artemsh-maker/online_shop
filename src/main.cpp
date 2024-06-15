#define CROW_USE_BOOST true

#include "crow.h"

int main() {
    crow::SimpleApp app;

    // root path { Home page }
    CROW_ROUTE(app, "/")
    ([](){
        try {
            return crow::response(200, "Hello world!!!");
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Error: ") + e.what());
        }
    });


    app.port(18080).multithreaded().run();
}
