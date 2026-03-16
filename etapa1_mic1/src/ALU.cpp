#include "ALU.hpp"

/**
 * @brief Executa a operação da ULA para uma instrução.
 *
 * A interpretação usada é:
 * - F0F1 = 00 -> A AND B
 * - F0F1 = 01 -> A OR B
 * - F0F1 = 10 -> NOT(B)
 * - F0F1 = 11 -> A + B + INC
 *
 * ENA e ENB habilitam as entradas.
 * INVA inverte A após a habilitação.
 *
 * @param inputA Palavra de entrada A.
 * @param inputB Palavra de entrada B.
 * @param instruction Instrução atual.
 * @return ALUResult Resultado completo da execução.
 */
ALUResult ALU::execute(uint32_t inputA, uint32_t inputB, const Instruction& instruction) const {
    ALUResult result{};

    result.a = instruction.getENA() ? inputA : 0;
    result.b = instruction.getENB() ? inputB : 0;

    if (instruction.getINVA()) {
        result.a = ~result.a;
    }

    const uint32_t andResult = result.a & result.b;
    const uint32_t orResult = result.a | result.b;
    const uint32_t notBResult = ~result.b;

    const uint64_t sum64 =
        static_cast<uint64_t>(result.a) +
        static_cast<uint64_t>(result.b) +
        static_cast<uint64_t>(instruction.getINC());

    const uint32_t sumResult = static_cast<uint32_t>(sum64);
    const uint32_t carryOut = (sum64 >> 32) & 0x1;

    const int f0 = instruction.getF0();
    const int f1 = instruction.getF1();

    if (f0 == 0 && f1 == 0) {
        result.s = andResult;
        result.co = 0;
    } else if (f0 == 0 && f1 == 1) {
        result.s = orResult;
        result.co = 0;
    } else if (f0 == 1 && f1 == 0) {
        result.s = notBResult;
        result.co = 0;
    } else {
        result.s = sumResult;
        result.co = carryOut;
    }

    return result;
}