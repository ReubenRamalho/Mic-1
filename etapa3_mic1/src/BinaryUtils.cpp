#include "BinaryUtils.hpp"

#include <algorithm>
#include <bitset>
#include <stdexcept>
#include <cctype>

std::size_t toString32bits(const std::string &binaryStr)
{
    std::size_t processed = 0;
    uint32_t value = 0;

    bool isBinary = true;
    for (char c : binaryStr)
    {
        if (c != '1' && c != '0')
        {
            isBinary = false;
            break;
        }
    }

    if (!isBinary)
    {
        throw std::invalid_argument("o valor a seguir não é binário: " + binaryStr);
    }

    value = static_cast<uint32_t>(std::stoul(binaryStr, &processed, 2));

    if (processed != binaryStr.size())
    {
        throw std::invalid_argument("Valor numérico inválido: " + binaryStr);
    }

    return value;
}

std::string toBinary32(uint32_t value)
{
    return std::bitset<32>(value).to_string();
}

std::string trim(const std::string &text)
{
    std::size_t begin = 0;
    while (begin < text.size() && std::isspace(static_cast<unsigned char>(text[begin])))
    {
        ++begin;
    }

    std::size_t end = text.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(text[end - 1])))
    {
        --end;
    }

    return text.substr(begin, end - begin);
}
