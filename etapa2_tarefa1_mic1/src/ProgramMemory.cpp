#include "ProgramMemory.hpp"

#include <cctype>
#include <fstream>
#include <stdexcept>

/**
 * @brief Carrega as instruções a partir de um arquivo texto.
 * @param fileName Caminho do arquivo de instruções.
 */
void ProgramMemory::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo de programa: " + fileName);
    }

    instructions.clear();

    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        std::string cleaned;
        for (char c : line) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                cleaned += c;
            }
        }

        if (cleaned.empty()) {
            continue;
        }

        try {
            instructions.push_back(Instruction::fromString(cleaned));
        } catch (const std::exception& e) {
            throw std::runtime_error(
                "Erro na linha " + std::to_string(lineNumber) + ": " + e.what()
            );
        }
    }
}

/**
 * @brief Retorna a quantidade de instruções carregadas.
 * @return std::size_t Número de instruções.
 */
std::size_t ProgramMemory::size() const {
    return instructions.size();
}

/**
 * @brief Retorna a instrução armazenada em uma posição.
 * @param index Índice da instrução.
 * @return const Instruction& Referência para a instrução.
 */
const Instruction& ProgramMemory::getInstruction(std::size_t index) const {
    if (index >= instructions.size()) {
        throw std::out_of_range("Indice fora da memoria de programa.");
    }

    return instructions[index];
}