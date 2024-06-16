#define CROW_USE_BOOST true
#define BOOST_LOG_DYN_LINK 1

#include "crow.h"
#include "utils.h"
#include "ErrorHandlerMiddleware.h"

int main() {
    init_logging_consol_and_file();

    crow::App<ErrorHandlerMiddleware> app;

    // root path { Home page }
    CROW_ROUTE(app, "/")
    ([](){
        try {
            BOOST_LOG_TRIVIAL(info) << "Received request at /";
            return crow::response(200, "Hello world!!!");
        }
        catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << std::string("Error: ") + e.what();
            return crow::response(500, std::string("Error: ") + e.what());
        }
    });

    app.port(18080).multithreaded().run();
    return 0;
}


// Примеры логирования
//    BOOST_LOG_TRIVIAL(trace) << "Это сообщение уровня trace.";
//    BOOST_LOG_TRIVIAL(debug) << "Это сообщение уровня debug.";
//    BOOST_LOG_TRIVIAL(info) << "Это информационное сообщение.";
//    BOOST_LOG_TRIVIAL(warning) << "Это предупреждение.";
//    BOOST_LOG_TRIVIAL(error) << "Это сообщение об ошибке.";
//    BOOST_LOG_TRIVIAL(fatal) << "Это критическое сообщение.";