#pragma once
#include "IAddressParser.h"
#include <fstream>
#include <iostream>

class XmlParser : public IAddressParser {
public:
    std::vector<Address> parse(const std::string& filePath) override {
        std::vector<Address> addresses;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл " << filePath << "\n";
            return addresses;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Ищем только строки с <item
            if (line.find("<item") == std::string::npos) continue;

            Address addr;
            addr.city = extractAttribute(line, "city=\"");
            addr.street = extractAttribute(line, "street=\"");
            addr.house = std::stoi(extractAttribute(line, "house=\""));
            addr.floor = std::stoi(extractAttribute(line, "floor=\""));

            addresses.push_back(addr);
        }
        return addresses;
    }

private:
    // Функция ищет начало атрибута, например city=", и вырезает значение до закрывающей кавычки
    std::string extractAttribute(const std::string& line, const std::string& attrName) {
        size_t startPos = line.find(attrName);
        if (startPos == std::string::npos) return "";

        startPos += attrName.length();
        size_t endPos = line.find('"', startPos);

        return line.substr(startPos, endPos - startPos);
    }
};