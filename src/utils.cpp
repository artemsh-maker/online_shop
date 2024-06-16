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
void init_logging_consol_and_file() {
    // Логирование в файл с ротацией по размеру и времени
    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024, // 10 MB
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0), // ежедневно в полночь
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%",
        boost::log::keywords::auto_flush = true
    );

    // Логирование в консоль
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );  

    // Установка уровня логирования (опционально)
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info
    );

    // Добавление общих атрибутов
    boost::log::add_common_attributes();
}