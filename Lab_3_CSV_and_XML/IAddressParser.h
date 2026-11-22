#pragma once
#include <vector>
#include <string>
#include "Address.h"

// Общий контракт для всех парсеров
class IAddressParser {
public:
    virtual ~IAddressParser() = default;

    // Чисто виртуальный метод. Любой парсер обязан его реализовать.
    virtual std::vector<Address> parse(const std::string& filePath) = 0;
};