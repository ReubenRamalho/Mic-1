#include "ExecutionLogger.hpp"

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
 * @param pc Valor do contador de programa.
 * @param ir Instrução atual.
 * @param b Valor de B mostrado no log.
 * @param a Valor de A mostrado no log.
 * @param s Saída da ULA.
 * @param co Carry-out mostrado no log.
 */
void ExecutionLogger::writeCycle(std::size_t cycle,
                                 std::size_t pc,
                                 const std::string& ir,
                                 uint32_t b,
                                 uint32_t a,
                                 uint32_t s,
                                 uint32_t co) {
    out << "Cycle " << cycle << "\n\n";
    out << "PC = " << pc << "\n";
    out << "IR = " << ir << "\n";
    out << "b = " << toBinary32(b) << "\n";
    out << "a = " << toBinary32(a) << "\n";
    out << "s = " << toBinary32(s) << "\n";
    out << "co = " << co << "\n";
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