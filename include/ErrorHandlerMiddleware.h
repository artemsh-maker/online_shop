#pragma once
#ifndef ERROR_HANDLER_MIDDLEWARE_H
#define ERROR_HANDLER_MIDDLEWARE_H

#include "crow.h"
#include "utils.h"


struct ErrorHandlerMiddleware {
    struct context {};

    void before_handle(crow::request &req, crow::response &res, context &ctx)
    {}

    void after_handle(crow::request &req, crow::response &res, context &ctx) {
        if (res.code == 404) {
            try {
                res.body = readFile("../assets/pages/NotFoundPage.html");
                res.set_header("Content-Type", "text/html");
            } catch(const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
};


#endif // UTILS_H