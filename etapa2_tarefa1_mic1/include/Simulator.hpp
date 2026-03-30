#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <cstdint>
#include <string>
#include "ALU.hpp"
#include "ProgramMemory.hpp"
#include "Registers.hpp"

/**
 * @brief Coordena toda a simulação da Etapa 1.
 */
class Simulator {
private:
    ProgramMemory programMemory;
    Registers registers;
    ALU alu;
    uint32_t inputA;
    uint32_t inputB;

public:
    /**
     * @brief Constrói o simulador com os valores iniciais de A e B.
     * @param inputA Valor inicial de A.
     * @param inputB Valor inicial de B.
     */
    Simulator(uint32_t inputA, uint32_t inputB);

    /**
     * @brief Carrega o arquivo com as instruções da ULA.
     * @param programFile Caminho do arquivo de entrada.
     */
    void loadProgram(const std::string& programFile);

    /**
     * @brief Executa o programa e gera o arquivo de log.
     * @param logFile Caminho do arquivo de saída.
     */
    void run(const std::string& logFile);
};

#endif
