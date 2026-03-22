#include "ExecutionLogger.hpp"

#include "Registers.hpp"
#include "../include/ALU.hpp"
#include <bitset>
#include <stdexcept>

/**
 * @brief Converte um valor de 32 bits para string binária.
 * @param value Valor a ser convertido.
 * @return std::string Representação binária com 32 bits.
 */
static std::string toBinary32(uint32_t value) {
    return std::bitset<32>(value).to_string();
}

/**
 * @brief Cria o logger e abre o arquivo de saída.
 * @param fileName Caminho do arquivo de log.
 */
ExecutionLogger::ExecutionLogger(const std::string& fileName) {
    out.open(fileName);

    if (!out.is_open()) {
        throw std::runtime_error("Nao foi possivel criar o arquivo de log: " + fileName);
    }
}

/**
 * @brief Escreve o cabeçalho do log com os valores iniciais.
 * @param inputB Valor original de B.
 * @param inputA Valor original de A.
 */
void ExecutionLogger::writeHeader(uint32_t inputB, uint32_t inputA) {
    out << "b = " << toBinary32(inputB) << "\n";
    out << "a = " << toBinary32(inputA) << "\n\n";
    out << "Start of Program\n";
    out << "============================================================\n";
}

/**
 * @brief Escreve um ciclo de execução no log.
 * @param cycle Número do ciclo.
 * @param registers Registradores.
 * @param result Resultado do último ciclo da ALU.
 */
void ExecutionLogger::writeCycle(std::size_t cycle,
                                 const Registers& registers,
                                 const ALUResult& result) {
    out << "Cycle " << cycle << "\n\n";
    out << "PC = " << registers.getPC() + 1 << "\n";
    out << "IR = " << registers.getIR() << "\n";

    if (result.invalido)
    {
        out << ">> ERRO: Instrução inválida!" << "\n";
    }
    else
    {
        out << "b  = " << toBinary32(result.b) << "\n";
        out << "a  = " << toBinary32(result.a) << "\n";
        out << "s  = " << toBinary32(result.s) << "\n";
        out << "sd = " << toBinary32(result.sd) << "\n";
        out << "co = " << result.co << "\n";
        out << "n  = " << result.n << "\n";
        out << "z  = " << result.z << "\n";
    }
    out << "============================================================\n";
}

/**
 * @brief Escreve a mensagem de fim de programa.
 * @param cycle Número do ciclo final.
 * @param pc Valor final do contador de programa.
 */
void ExecutionLogger::writeEndOfProgram(std::size_t cycle, std::size_t pc) {
    out << "Cycle " << cycle << "\n\n";
    out << "PC = " << pc << "\n";
    out << "> Line is empty, EOP.\n";
}