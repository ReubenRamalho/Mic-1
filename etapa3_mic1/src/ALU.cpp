#include "../include/ALU.hpp"
#include "../include/Instruction.hpp"

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
 * SLL8 realiza o shift lógico dos bits 8 casas para a esquerda.
 * SRA1 realiza o shift aritmético dos bits 1 casa para a direita.
 *
 * @param inputA Palavra de entrada A.
 * @param inputB Palavra de entrada B.
 * @param instruction Instrução atual.
 * @return ALUResult Resultado completo da execução.
 */
ALUResult ALU::execute(uint32_t inputA, uint32_t inputB, const Instruction &instruction) const
{
    ALUResult result{};

    result.a = instruction.getENA() ? inputA : 0;
    result.b = instruction.getENB() ? inputB : 0;

    if (instruction.getINVA())
    {
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

    // Operações definidas for F0 e F1
    if (f0 == 0 && f1 == 0)
    {
        result.s = andResult;
        result.co = 0;
    }
    else if (f0 == 0 && f1 == 1)
    {
        result.s = orResult;
        result.co = 0;
    }
    else if (f0 == 1 && f1 == 0)
    {
        result.s = notBResult;
        result.co = 0;
    }
    else
    {
        result.s = sumResult;
        result.co = carryOut;
    }

    // Aplicação de SLL8 ou SRA1 (sempre após a operação de F0 e F1)
    const int sll8 = instruction.getSLL8();
    const int sra1 = instruction.getSRA1();

    result.sd = result.s;
    if (sll8)
    {
        result.sd = (result.s << 8);
    }
    else if (sra1)
    {
        const int msb = (result.s & (1 << 31)); // msb: most significant bit
        result.sd = ((result.s >> 1) | msb);
    }

    result.n = ((result.sd & (1 << 31)) != 0); // bit mais significativo = 1
    result.z = (result.sd == 0);
    result.invalido = (sll8 && sra1);

    return result;
}