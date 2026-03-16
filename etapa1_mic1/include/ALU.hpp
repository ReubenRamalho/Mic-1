#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

#include "Instruction.hpp"

/**
 * @brief Estrutura que armazena o resultado da execução da ULA.
 */
struct ALUResult {
    uint32_t a;
    uint32_t b;
    uint32_t s;
    uint32_t co;
};

/**
 * @brief Representa a ULA da Etapa 1.
 */
class ALU {
public:
    /**
     * @brief Executa uma instrução da ULA.
     * @param inputA Valor original de A.
     * @param inputB Valor original de B.
     * @param instruction Instrução atual.
     * @return ALUResult Resultado da operação.
     */
    ALUResult execute(uint32_t inputA, uint32_t inputB, const Instruction& instruction) const;
};

#endif