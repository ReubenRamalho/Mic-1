#ifndef BINARY_UTILS_HPP
#define BINARY_UTILS_HPP

#include <cstdint>
#include <string>

/**
 * @brief Converte uma string binária para um inteiro de 32 bits.
 * @param value Valor a ser convertido.
 * @return String binária com 32 caracteres.
 */
std::size_t toString32bits(const std::string &binaryStr);

/**
 * @brief Converte um inteiro de 32 bits para sua representação binária.
 * @param value Valor a ser convertido.
 * @return String binária com 32 caracteres.
 */
std::string toBinary32(uint32_t value);

/**
 * @brief Converte um inteiro de 8 bits para sua representação binária.
 * @param value Valor a ser convertido.
 * @return String binária com 8 caracteres.
 */
std::string toBinary8(uint32_t value);

/**
 * @brief Remove espaços em branco do início e do fim de uma string.
 * @param text Texto original.
 * @return Texto sem espaços laterais.
 */
std::string trim(const std::string &text);

#endif
