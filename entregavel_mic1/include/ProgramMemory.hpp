#ifndef PROGRAM_MEMORY_HPP
#define PROGRAM_MEMORY_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "Instruction.hpp"

/**
 * @brief Armazena as instruções lidas do arquivo do programa.
 */
class ProgramMemory {
private:
    std::vector<Instruction> instructions;

    void appendInstructions(const std::vector<Instruction>& newInstr);

public:
    /**
     * @brief Carrega as instruções a partir de um arquivo texto.
     * @param fileName Caminho do arquivo de instruções.
     */
    void loadFromFile(const std::string& fileName);

    /**
     * @brief Retorna a quantidade de instruções carregadas.
     * @return std::size_t Número de instruções.
     */
    std::size_t size() const;

    /**
     * @brief Retorna a instrução armazenada em uma posição.
     * @param index Índice da instrução.
     * @return const Instruction& Referência para a instrução.
     */
    const Instruction& getInstruction(std::size_t index) const;
};

#endif