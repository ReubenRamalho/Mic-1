#ifndef EXECUTION_LOGGER_HPP
#define EXECUTION_LOGGER_HPP

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
     * @param pc Valor do contador de programa.
     * @param ir Instrução atual.
     * @param b Valor de B mostrado no log.
     * @param a Valor de A mostrado no log.
     * @param s Saída da ULA.
     * @param co Carry-out mostrado no log.
     */
    void writeCycle(std::size_t cycle,
                    std::size_t pc,
                    const std::string& ir,
                    uint32_t b,
                    uint32_t a,
                    uint32_t s,
                    uint32_t co);

    /**
     * @brief Escreve a mensagem de fim de programa.
     * @param cycle Número do ciclo final.
     * @param pc Valor final do contador de programa.
     */
    void writeEndOfProgram(std::size_t cycle, std::size_t pc);
};

#endif