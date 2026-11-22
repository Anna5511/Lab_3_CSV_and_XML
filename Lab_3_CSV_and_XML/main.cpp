#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include "CsvParser.h"
#include "XmlParser.h"
#include "Statistics.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Приложение для обработки справочников городов.\n";

    while (true) {
        std::cout << "\nВведите путь до файла (.csv или .xml) или 'exit' для выхода: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            std::cout << "Завершение работы.\n";
            break;
        }

        // Фабрика парсеров. Умный указатель сам очистит память.
        std::unique_ptr<IAddressParser> parser = nullptr;

        // Проверяем расширение файла (вытаскиваем подстроку с конца)
        if (input.length() > 4 && input.substr(input.length() - 4) == ".csv") {
            parser = std::make_unique<CsvParser>();
        }
        else if (input.length() > 4 && input.substr(input.length() - 4) == ".xml") {
            parser = std::make_unique<XmlParser>();
        }
        else {
            std::cout << "Ошибка: Неподдерживаемый формат файла. Требуется .csv или .xml\n";
            continue;
        }

        // Засекаем время старта
        auto start = std::chrono::high_resolution_clock::now();

        // Полиморфизм в действии: вызываем parse, не зная на этапе компиляции, какой именно это файл
        std::vector<Address> data = parser->parse(input);

        if (!data.empty()) {
            Statistics stats;
            stats.process(data);
        }

        // Останавливаем таймер
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "\nВремя обработки файла: " << duration.count() << " секунд.\n";
    }

    return 0;
}