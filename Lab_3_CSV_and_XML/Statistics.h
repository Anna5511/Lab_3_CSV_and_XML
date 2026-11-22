#pragma once
#include "Address.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>

class Statistics {
public:
    void process(const std::vector<Address>& addresses) {
        // Хэш-таблица для поиска дубликатов. Ключ - Адрес, Значение - количество повторений.
        std::unordered_map<Address, int, AddressHash> duplicates;

        // Хэш-таблица для этажей. Ключ - Город. Значение - массив на 5 элементов (индексы 0-4 соответствуют 1-5 этажам).
        std::unordered_map<std::string, std::vector<int>> cityFloors;

        // Делаем всего ОДИН проход по списку (это гарантирует максимальную скорость, О(N))
        for (const auto& addr : addresses) {
            duplicates[addr]++;

            // Инициализируем массив из 5 нулей для нового города
            if (cityFloors.find(addr.city) == cityFloors.end()) {
                cityFloors[addr.city] = std::vector<int>(5, 0);
            }

            // Если этаж от 1 до 5, увеличиваем счетчик (этаж 1 -> индекс 0)
            if (addr.floor >= 1 && addr.floor <= 5) {
                cityFloors[addr.city][addr.floor - 1]++;
            }
        }

        printDuplicates(duplicates);
        printCityFloors(cityFloors);
    }

private:
    void printDuplicates(const std::unordered_map<Address, int, AddressHash>& duplicates) {
        std::cout << "\n--- Дублирующиеся записи ---\n";
        bool hasDuplicates = false;
        for (const auto& pair : duplicates) {
            if (pair.second > 1) { // Если встречалось больше 1 раза
                const Address& a = pair.first;
                std::cout << a.city << ", " << a.street << ", д." << a.house
                    << ", эт." << a.floor << " -> Повторений: " << pair.second << "\n";
                hasDuplicates = true;
            }
        }
        if (!hasDuplicates) std::cout << "Дубликатов не найдено.\n";
    }

    void printCityFloors(const std::unordered_map<std::string, std::vector<int>>& cityFloors) {
        std::cout << "\n--- Статистика этажности по городам ---\n";
        for (const auto& pair : cityFloors) {
            std::cout << "Город: " << pair.first << "\n";
            for (int i = 0; i < 5; ++i) {
                std::cout << "  " << (i + 1) << "-этажных: " << pair.second[i] << "\n";
            }
        }
    }
};