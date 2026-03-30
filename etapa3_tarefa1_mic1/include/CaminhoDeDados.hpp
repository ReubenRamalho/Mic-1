#ifndef CAMINHO_DE_DADOS_HPP
#define CAMINHO_DE_DADOS_HPP

#include <cstdint>
#include <utility>
#include <vector>

#include "ALU.hpp"
#include "BinaryUtils.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"

/**
 * @brief Estrutura que armazena o resultado da execução do caminho de dados
 */
struct CDresult {
  std::string ulaBits;
  std::string cBits;
  std::string memoryBits;
  std::string bBits;
  std::string b_bus;
  std::vector<std::string> c_bus;
  uint32_t s_mar;
  uint32_t s_mdr;
  uint32_t s_pc;
  uint32_t s_mbr;
  uint32_t s_sp;
  uint32_t s_lv;
  uint32_t s_cpp;
  uint32_t s_tos;
  uint32_t s_opc;
  uint32_t s_h;
  uint32_t e_mar;
  uint32_t e_mdr;
  uint32_t e_pc;
  uint32_t e_mbr;
  uint32_t e_sp;
  uint32_t e_lv;
  uint32_t e_cpp;
  uint32_t e_tos;
  uint32_t e_opc;
  uint32_t e_h;
};

/**
 * @brief Representa a ULA da Etapa 1.
 */
class CaminhoDeDados {
private:
  CDresult result;
  Registers registers;
  ALU alu;

public:
  /**
   * @brief inicializador padrão
   */
  CaminhoDeDados();

  /**
   * @brief altera os valores internos dos registradores
   */
  CaminhoDeDados(const Registers &registers, const ALU &alu);

  /**
   * @brief O valor contido no registrador MDR é escrito na linha do
   * arquivo dados.txt correspondente ao endereço apontado pelo valor de MAR.
   */
  void writeAtMemory();

  /**
   * @brief O valor contido na linha do arquivo dados.txt correspondente ao
   * endereço apontado pelo valor de MAR é copiado para o registrador MDR.
   */
  void readFromMemory();

  /**
   * @brief Carrega o arquivo com aos valores iniciais dos registradores.
   * @param programFile Caminho do arquivo de entrada.
   */
  void loadRegisters(const std::string &programFile);

  /**
   * @brief Executa uma instrução do caminho de dados.
   * @param instruction instrução lida.
   * @return ALUResult Resultado da operação.
   */
  CDresult execute(const Instruction &instruction);

  /**
   * @brief seleciona os registradores que sofrerão alteração da ULA.
   * @param value valor a ser inserido nos registradores.
   * @param cBits bits para barramento C.
   * @return ALUResult Resultado da operação.
   */
  std::vector<std::string> seletor(const std::string &cBits) const;

  /**
   * @brief seleciona o registrador que fornecerá a entrada B da ULA.
   * @param cBits bits para barramento B.
   * @return ALUResult Resultado da operação.
   */
  std::pair<uint32_t, std::string>
  decodificador(const std::string &bBits) const;

  Registers getRegisters() { return registers; }
};

#endif