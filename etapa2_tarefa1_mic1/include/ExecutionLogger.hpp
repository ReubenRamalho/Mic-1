#ifndef EXECUTION_LOGGER_HPP
#define EXECUTION_LOGGER_HPP

#include "Registers.hpp"
#include "ALU.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

/**
 * @brief Responsável por gerar o arquivo de log da execução.
 */
class ExecutionLogger {
private:
    std::ofstream out;

public:
    /**
     * @brief Cria o logger e abre o arquivo de saída.
     * @param fileName Caminho do arquivo de log.
     */
    explicit ExecutionLogger(const std::string& fileName);

    /**
     * @brief Escreve o cabeçalho do log com os valores iniciais.
     * @param inputB Valor original de B.
     * @param inputA Valor original de A.
     */
    void writeHeader(uint32_t inputB, uint32_t inputA);

    /**
     * @brief Escreve um ciclo de execução no log.
     * @param cycle Número do ciclo.
     * @param registers Registradores.
     * @param result Resultado do último ciclo da ALU.
     */
    void writeCycle(std::size_t cycle,
                    const Registers& registers,
                    const ALUResult& result);

    /**
     * @brief Escreve a mensagem de fim de programa.
     * @param cycle Número do ciclo final.
     * @param pc Valor final do contador de programa.
     */
    void writeEndOfProgram(std::size_t cycle, std::size_t pc);
};

#endif