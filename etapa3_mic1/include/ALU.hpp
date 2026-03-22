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
    uint32_t sd;    // saída "s" deslocada após as operações SLL8 ou SRA1
    uint32_t co;
    uint32_t n;     // 1 se a saída da ULA é negativa; 0 caso contrário
    uint32_t z;     // 1 se a saída da ULA é zero; 0 caso contrátio
    uint32_t invalido;  // 1 se SLL8 e SRA1 forem 1 ao mesmo tempo; 0 c.c.
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