#include "Simulator.hpp"

#include "../include/ALU.hpp"
#include "../include/ExecutionLogger.hpp"
#include "Instruction.hpp"

// /**
//  * @brief Constrói o simulador.
//  */
// Simulator::Simulator() {}

/**
 * @brief Carrega o programa de instruções a partir de um arquivo.
 * @param programFile Caminho do arquivo de instruções.
 */
void Simulator::loadProgram(const std::string &programFile)
{
    programMemory.loadFromFile(programFile);
}

/**
 * @brief Carrega o arquivo com aos valores iniciais dos registradores.
 * @param programFile Caminho do arquivo de entrada.
 */
void Simulator::loadRegisters(const std::string &programFile)
{
    registers.loadFromFile(programFile);
}

/**
 * @brief Executa o programa carregado e gera o arquivo de log.
 * @param logFile Caminho do arquivo de saída do log.
 */
void Simulator::run(const std::string &logFile)
{
    // ExecutionLogger logger(logFile);

    // registers.setPC(0);

    // logger.writeHeader(inputB, inputA);

    // std::size_t cycle = 1;

    // while (registers.getPC() < programMemory.size()) {
    //     const Instruction& instruction = programMemory.getInstruction(registers.getPC());
    //     registers.setIR(instruction.getRawBits());

    //     const ALUResult result = alu.execute(inputA, inputB, instruction);

    //     logger.writeCycle(cycle, registers, result);

    //     registers.incrementPC();
    //     cycle++;
    // }

    // logger.writeEndOfProgram(cycle, registers.getPC() + 1);
}