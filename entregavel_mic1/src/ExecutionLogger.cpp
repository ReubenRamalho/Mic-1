#include "../include/ExecutionLogger.hpp"
#include "../include/ALU.hpp"
#include "../include/BinaryUtils.hpp"
#include "../include/Registers.hpp"
#include <bitset>
#include <iostream>
#include <stdexcept>

// /**
//  * @brief Converte um valor de 32 bits para string binária.
//  * @param value Valor a ser convertido.
//  * @return std::string Representação binária com 32 bits.
//  */
// static std::string toBinary32(uint32_t value) {
//   return std::bitset<32>(value).to_string();
// }

/**
 * @brief Cria o logger e abre o arquivo de saída.
 * @param fileName Caminho do arquivo de log.
 */
ExecutionLogger::ExecutionLogger(const std::string &fileName) {
  out.open(fileName);

  if (!out.is_open()) {
    throw std::runtime_error("Nao foi possivel criar o arquivo de log: " +
                             fileName);
  }
}

void ExecutionLogger::writeMemory() {
  std::ifstream infile("data/dados.txt");
  if (!infile) {
    std::cerr << "Erro ao abrir data/dados.txt para leitura\n";
    return;
  }

  std::string linha;
  while (std::getline(infile, linha)) {
    out << linha << "\n";
  }
}

/**
 * @brief Escreve o cabeçalho do log com os valores iniciais.
 * @param inputB Valor original de B.
 * @param inputA Valor original de A.
 */
void ExecutionLogger::writeHeader(const ProgramMemory &programMemory,
                                  const Registers &registers) {
  for (size_t i = 0; i < programMemory.size(); i++) {
    out << programMemory.getInstruction(i).getulaBits()
        << programMemory.getInstruction(i).getcBits()
        << programMemory.getInstruction(i).getMemoryBits()
        << programMemory.getInstruction(i).getbBits() << "\n";
  }
  out << "\nStart of Program\n";
  out << "============================================================\n";
  out << "> Initial memory state\n";
  out << "*******************************\n";
  writeMemory();
  out << "*******************************\n";
  out << "> Initial register states\n";
  out << "*******************************\n";
  std::vector<std::string> register_names = registers.getRegisterNames();

  for (std::string name : register_names) {
    if (name != "mbr") {
      out << name << " = " << toBinary32(registers.getRegisterValue(name))
          << "\n";
    } else {
      out << name << " = " << toBinary8(registers.getRegisterValue(name))
          << "\n";
    }
  }
  out << "\n============================================================\n";
  out << "Start of program\n";
  out << "============================================================\n";
}

/**
 * @brief Escreve um ciclo de execução no log.
 * @param cycle Número do ciclo.
 * @param registers Registradores.
 * @param result Resultado do último ciclo da ALU.
 */
void ExecutionLogger::writeCycle(std::size_t cycle, const Registers &registers,
                                 const CDresult &result) {
  out << "Cycle " << cycle << "\n\n";
  // out << "PC = " << registers.getPC() + 1 << "\n";
  out << "IR = " << result.ulaBits << " " << result.cBits << " "
      << result.memoryBits << " " << result.bBits << "\n";

  out << "b_bus = " << result.b_bus << "\n";

  out << "c_bus = ";
  for (int i = 0; i < result.c_bus.size() - 1; i++) {
    out << result.c_bus[i] << ", ";
  }
  out << result.c_bus.back() << "\n\n";

  out << "> Registers before instruction\n";

  out << "mar = " << toBinary32(result.s_mar) << "\n";
  out << "mdr = " << toBinary32(result.s_mdr) << "\n";
  out << "pc = " << toBinary32(result.s_pc) << "\n";
  out << "mbr = " << toBinary8(result.s_mbr) << "\n";
  out << "sp = " << toBinary32(result.s_sp) << "\n";
  out << "lv = " << toBinary32(result.s_lv) << "\n";
  out << "cpp = " << toBinary32(result.s_cpp) << "\n";
  out << "tos = " << toBinary32(result.s_tos) << "\n";
  out << "opc = " << toBinary32(result.s_opc) << "\n";
  out << "h = " << toBinary32(result.s_h) << "\n";

  out << "\n> Registers after instruction\n";
  out << "mar = " << toBinary32(result.e_mar) << "\n";
  out << "mdr = " << toBinary32(result.e_mdr) << "\n";
  out << "pc = " << toBinary32(result.e_pc) << "\n";
  out << "mbr = " << toBinary8(result.e_mbr) << "\n";
  out << "sp = " << toBinary32(result.e_sp) << "\n";
  out << "lv = " << toBinary32(result.e_lv) << "\n";
  out << "cpp = " << toBinary32(result.e_cpp) << "\n";
  out << "tos = " << toBinary32(result.e_tos) << "\n";
  out << "opc = " << toBinary32(result.e_opc) << "\n";
  out << "h = " << toBinary32(result.e_h) << "\n";

  out << "\n> Memory after instruction\n";
  out << "*******************************\n";
  writeMemory();

  //   if (result.invalido) {
  //     out << ">> ERRO: Instrução inválida!" << "\n";
  //   } else {
  //     out << "b  = " << toBinary32(result.b) << "\n";
  //     out << "a  = " << toBinary32(result.a) << "\n";
  //     out << "s  = " << toBinary32(result.s) << "\n";
  //     out << "sd = " << toBinary32(result.sd) << "\n";
  //     out << "co = " << result.co << "\n";
  //     out << "n  = " << result.n << "\n";
  //     out << "z  = " << result.z << "\n";
  //   }
  out << "============================================================\n";
}

/**
 * @brief Escreve a mensagem de fim de programa.
 * @param cycle Número do ciclo final.
 * @param pc Valor final do contador de programa.
 */
void ExecutionLogger::writeEndOfProgram(std::size_t cycle) {
  out << "Cycle " << cycle << "\n";
  out << "No more lines, EOP.\n";
}