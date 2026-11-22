#pragma once
#include <vector>
#include <string>
#include "Address.h"

class IAddressParser {
public:
    virtual ~IAddressParser() = default;

    virtual std::vector<Address> parse(const std::string& filePath) = 0;
};