#define BOOST_LOG_DYN_LINK 1

#include "utils.h"
#include "ErrorHandlerMiddleware.h"

int main() {
    init_logging_consol_and_file(boost::log::trivial::debug);

    crow::App<ErrorHandlerMiddleware> app;
    BOOST_LOG_TRIVIAL(debug) << "The homepage is available at the path: http://0.0.0.0:18080";

    // root path { Home page }
    CROW_ROUTE(app, "/")
    ([&](const crow::request& req){
        try {
            BOOST_LOG_TRIVIAL(info) << get_client_IPv4(req) << "Received request at /" << std::endl;
            return crow::response(200, "Hello world!!!");
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << std::string("Error: ") + e.what();
            return crow::response(500, std::string("Error: ") + e.what());
        }
    });


    // Асинхронное чтение изображения в память
    const std::shared_future<std::vector<char>> imageDataFutureFaviconIco = std::async(std::launch::async, loadImage, "../assets/img/favicon.jpeg").share();
    
    CROW_ROUTE(app, "/favicon.ico")    // Маршрут для обработки запроса изображения
    ([&imageDataFutureFaviconIco]() {
        try {
            // Ожидание завершения асинхронной операции чтения изображения
            const std::vector<char>& imageData = imageDataFutureFaviconIco.get();
            auto res = crow::response(std::string(imageData.begin(), imageData.end()));
            res.set_header("Content-Type", "image/jpeg");
            return res;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << std::string("Error: ") + e.what();
            return crow::response(404, "Image not found");
        }
    });
    


    app.loglevel(crow::LogLevel::WARNING);
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