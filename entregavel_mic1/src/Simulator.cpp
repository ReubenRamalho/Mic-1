#include "../include/Simulator.hpp"
#include <iostream>

#include "../include/ALU.hpp"
#include "../include/ExecutionLogger.hpp"
#include "../include/Instruction.hpp"

// /**
//  * @brief Constrói o simulador.
//  */
Simulator::Simulator() {}

/**
 * @brief Carrega o programa de instruções a partir de um arquivo.
 * @param programFile Caminho do arquivo de instruções.
 */
void Simulator::loadProgram(const std::string &programFile) {
  programMemory.loadFromFile(programFile);
}

/**
 * @brief Carrega o arquivo com aos valores iniciais dos registradores.
 * @param programFile Caminho do arquivo de entrada.
 */
void Simulator::loadRegisters(const std::string &programFile) {
  caminhoDeDados.loadRegisters(programFile);
}

/**
 * @brief Executa o programa carregado e gera o arquivo de log.
 * @param logFile Caminho do arquivo de saída do log.
 */
void Simulator::run(const std::string &logFile) {
  size_t line = 0;

  ExecutionLogger logger(logFile);

  logger.writeHeader(programMemory, caminhoDeDados.getRegisters());

  std::size_t cycle = 0;

  while (line < programMemory.size()) {
    cycle++;
    const Instruction &instruction = programMemory.getInstruction(line);
    // registers.setIR(instruction.getulaBits());

    const CDresult result = caminhoDeDados.execute(instruction);

    logger.writeCycle(cycle, caminhoDeDados.getRegisters(), result);

    // registers.incrementPC();
    line++;
  }

  logger.writeEndOfProgram(cycle);
}