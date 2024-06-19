#include "utils.h"

// Функция для чтения содержимого текстового файла в std::string
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    
    if (!file)    { throw std::runtime_error("Could not open file: " + filePath); }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string content;
    content.reserve(fileSize);
    content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}


// Функция для загрузки изображения в память
std::vector<char> loadImage(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    
    // Получение размера файла
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // Чтение данных файла в память
    std::vector<char> imageData(fileSize);
    file.read(imageData.data(), fileSize);
    
    return imageData;
}


// Инициализация логирования
void init_logging_consol_and_file(const short& type_log) {
    // Логирование в файл с ротацией по размеру (10 MB) и времени (в полноч)
    boost::log::add_file_log (
        boost::log::keywords::file_name = "../logs/sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024, // 10 MB
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]  %Message%", // в таком виде: [2024-06-16 19:17:06.121083] [0x00007faee9e006c0] [info]: Received request at /
        boost::log::keywords::auto_flush = true
    );

    // Логирование в консоль
    boost::log::add_console_log (
        std::cout, 
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]  %Message%" // в таком виде: [2024-06-16 19:17:06.121083] [0x00007faee9e006c0] [info]: Received request at /
    );  

    // Установка уровня логирования
    boost::log::core::get()->set_filter (
        boost::log::trivial::severity >= type_log
    );

    // Добавление общих атрибутов
    boost::log::add_common_attributes();
}


std::string get_client_IPv4(const crow::request& req) {
    // Проверка заголовка X-Forwarded-For
    auto x_forwarded_for = req.get_header_value("X-Forwarded-For");
    if (!x_forwarded_for.empty()) {
        return x_forwarded_for + std::string(": ");
    }

    // Если заголовок X-Forwarded-For отсутствует, используем адрес из соединения
    return req.remote_ip_address + std::string(": ");
}