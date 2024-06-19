#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <streambuf>
#include <fstream>

#define CROW_USE_BOOST true
#include "crow.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>

// Функция для чтения содержимого текстового файла в std::string
std::string readFile(const std::string& filePath);

// Функция для загрузки изображения в память
std::vector<char> loadImage(const std::string& filePath);

// Инициализация логирования
void init_logging_consol_and_file(const short& type_log);

// Получение реального IP пользователя, если приложение работает за прокси-сервером или балансировщиком нагрузки
std::string get_client_IPv4(const crow::request& req);

#endif // UTILS_H
