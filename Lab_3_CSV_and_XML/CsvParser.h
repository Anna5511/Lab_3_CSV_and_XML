#pragma once
#include "IAddressParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

class CsvParser : public IAddressParser {
public:
    std::vector<Address> parse(const std::string& filePath) override {
        std::vector<Address> addresses;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл " << filePath << "\n";
            return addresses;
        }

        std::string line;
        // Пропускаем первую строку с заголовками
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Address addr;
            std::stringstream ss(line);
            std::string token;

            // Читаем город
            std::getline(ss, token, ';');
            addr.city = removeQuotes(token);

            // Читаем улицу
            std::getline(ss, token, ';');
            addr.street = removeQuotes(token);

            // Читаем дом (в CSV он без кавычек)
            std::getline(ss, token, ';');
            addr.house = std::stoi(token);

            // Читаем этаж (без кавычек)
            std::getline(ss, token, ';');
            addr.floor = std::stoi(token);

            addresses.push_back(addr);
        }
        return addresses;
    }

private:
    // Вспомогательный метод для очистки от кавычек
    std::string removeQuotes(std::string str) {
        str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
        return str;
    }
};