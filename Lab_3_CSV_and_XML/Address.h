#pragma once
#include <string>
#include <functional>

// Модель одной записи из справочника
struct Address {
    std::string city;
    std::string street;
    int house;
    int floor;

    // Перегрузка оператора == необходима для использования структуры в качестве ключа в hashmap
    bool operator==(const Address& other) const {
        return city == other.city &&
            street == other.street &&
            house == other.house &&
            floor == other.floor;
    }
};

// Структура для вычисления хэша нашего объекта (требуется для std::unordered_map)
struct AddressHash {
    std::size_t operator()(const Address& addr) const {
        // Комбинируем хэши всех полей с помощью побитовых операций сдвига (^)
        std::size_t h1 = std::hash<std::string>{}(addr.city);
        std::size_t h2 = std::hash<std::string>{}(addr.street);
        std::size_t h3 = std::hash<int>{}(addr.house);
        std::size_t h4 = std::hash<int>{}(addr.floor);

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};