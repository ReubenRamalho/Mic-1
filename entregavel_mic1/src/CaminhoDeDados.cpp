#include "../include/CaminhoDeDados.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief construtor padrão
 */
CaminhoDeDados::CaminhoDeDados() {}

/**
 * @brief altera os valores internos dos registradores
 */
CaminhoDeDados::CaminhoDeDados(const Registers &registers, const ALU &alu)
    : registers(registers), alu(alu) {}

/**
 * @brief O valor contido no registrador MDR é escrito na linha do
 * arquivo dados.txt correspondente ao endereço apontado pelo valor de MAR.
 */
void CaminhoDeDados::writeAtMemory() {
  std::size_t mar = registers.getRegisterValue("mar");
  std::size_t mdr = registers.getRegisterValue("mdr");

  if (mar >= 8) {
    std::cerr << "Erro: endereço MAR fora do intervalo\n";
    return;
  }

  std::ifstream infile("data/dados.txt");
  if (!infile) {
    std::cerr << "Erro ao abrir arquivo para leitura\n";
    return;
  }

  std::vector<std::string> linhas;
  std::string linha;

  while (std::getline(infile, linha)) {
    linhas.push_back(linha);
  }
  infile.close();

  // garante que existem pelo menos 8 linhas
  while (linhas.size() < 8) {
    linhas.push_back("0");
  }

  // atualiza a linha correspondente ao MAR
  linhas[mar] = toBinary32(mdr);

  std::ofstream outfile("data/dados.txt");
  if (!outfile) {
    std::cerr << "Erro ao abrir arquivo para escrita\n";
    return;
  }

  for (const auto &l : linhas) {
    outfile << l << "\n";
  }
}

/**
 * @brief O valor contido na linha do arquivo dados.txt correspondente ao
 * endereço apontado pelo valor de MAR é copiado para o registrador MDR.
 */
void CaminhoDeDados::readFromMemory() {
  std::size_t mar = registers.getRegisterValue("mar");

  if (mar >= 8) {
    std::cerr << "Erro: endereço MAR fora do intervalo\n";
    return;
  }

  std::ifstream infile("data/dados.txt");
  if (!infile) {
    std::cerr << "Erro ao abrir arquivo\n";
    return;
  }

  std::string linha;
  std::size_t currentLine = 0;

  while (std::getline(infile, linha)) {
    if (currentLine == mar) {
      std::size_t valor = toString32bits(linha);
      registers.setRegisterValue("mdr", valor);
      return;
    }
    currentLine++;
  }

  std::cerr << "Erro: linha não encontrada no arquivo\n";
}

/**
 * @brief Carrega o arquivo com aos valores iniciais dos registradores.
 * @param programFile Caminho do arquivo de entrada.
 */
void CaminhoDeDados::loadRegisters(const std::string &programFile) {
  registers.loadFromFile(programFile);
}

/**
 * @brief seleciona os registradores que sofrerão alteração da ULA.
 * @param value valor a ser inserido nos registradores.
 * @param cBits bits para barramento C.
 * @return ALUResult Resultado da operação.
 */
std::vector<std::string>
CaminhoDeDados::seletor(const std::string &cBits) const {

  std::vector<std::string> selected;

  if (cBits[8] == '1') {
    // registers.setRegisterValue("mar", value);
    selected.push_back("mar");
  }

  if (cBits[7] == '1') {
    // registers.setRegisterValue("mdr", value);
    selected.push_back("mdr");
  }

  if (cBits[6] == '1') {
    // registers.setRegisterValue("pc", value);
    selected.push_back("pc");
  }

  if (cBits[5] == '1') {
    // registers.setRegisterValue("sp", value);
    selected.push_back("sp");
  }

  if (cBits[4] == '1') {
    // registers.setRegisterValue("lv", value);
    selected.push_back("lv");
  }

  if (cBits[3] == '1') {
    // registers.setRegisterValue("cpp", value);
    selected.push_back("cpp");
  }

  if (cBits[2] == '1') {
    // registers.setRegisterValue("tos", value);
    selected.push_back("tos");
  }

  if (cBits[1] == '1') {
    // registers.setRegisterValue("opc", value);
    selected.push_back("opc");
  }

  if (cBits[0] == '1') {
    // registers.setRegisterValue("h", value);
    selected.push_back("h");
  }

  return selected;
}

/**
 * @brief seleciona o registrador que fornecerá a entrada B da ULA.
 * @param cBits bits para barramento B.
 * @return ALUResult Resultado da operação.
 */
std::pair<uint32_t, std::string>
CaminhoDeDados::decodificador(const std::string &bBits) const {
  size_t register_id = toString32bits(bBits);

  std::pair<uint32_t, std::string> result_pair;

  if (register_id == 0) {
    result_pair.second = "mdr";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 1) {
    result_pair.second = "pc";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 2) {
    result_pair.second = "mbr";

    std::string extra_bits = "";
    std::string binary_mbr =
        toBinary8(registers.getRegisterValue(result_pair.second));
    for (int i = 0; i < 24; i++) {
      extra_bits += binary_mbr[0];
    }
    binary_mbr = extra_bits + binary_mbr;

    // std::cout << binary_mbr << "\n";

    result_pair.first = toString32bits(binary_mbr);
  } else if (register_id == 3) {
    result_pair.second = "mbru";
    result_pair.first = registers.getRegisterValue("mbr");
  } else if (register_id == 4) {
    result_pair.second = "sp";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 5) {
    result_pair.second = "lv";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 6) {
    result_pair.second = "cpp";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 7) {
    result_pair.second = "tos";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  } else if (register_id == 8) {
    result_pair.second = "opc";
    result_pair.first = registers.getRegisterValue(result_pair.second);
  }
  return result_pair;
}

/**
 * @brief Executa o caminho de dados para uma instrução.
 *
 * @param instruction instrução de 21 bits atual.
 * @return CDresult Resultado completo da execução.
 */
CDresult CaminhoDeDados::execute(const Instruction &instruction) {
  CDresult result{};

  result.ulaBits = instruction.getulaBits();
  result.cBits = instruction.getcBits();
  result.memoryBits = instruction.getMemoryBits();
  result.bBits = instruction.getbBits();

  std::pair<uint32_t, std::string> par = decodificador(instruction.getbBits());
  result.b_bus = par.second;
  const uint32_t entrada_b = par.first;

  result.s_mar = registers.getRegisterValue("mar");
  result.s_mdr = registers.getRegisterValue("mdr");
  result.s_pc = registers.getRegisterValue("pc");
  result.s_mbr = registers.getRegisterValue("mbr");
  result.s_sp = registers.getRegisterValue("sp");
  result.s_lv = registers.getRegisterValue("lv");
  result.s_cpp = registers.getRegisterValue("cpp");
  result.s_tos = registers.getRegisterValue("tos");
  result.s_opc = registers.getRegisterValue("opc");
  result.s_h = registers.getRegisterValue("h");

  std::string memoryBits = instruction.getMemoryBits();

  if (memoryBits[0] == '1' && memoryBits[1] == '1') {
    bipushFetch(instruction.getulaBits());
  }

  else {
    const ALUResult aluResult =
        alu.execute(registers.getRegisterValue("h"), entrada_b, instruction);
    result.c_bus = seletor(instruction.getcBits());
  
    for (std::string name : result.c_bus) {
      registers.setRegisterValue(name, aluResult.sd);
    }
  
  
    if (memoryBits[0] == '1') {
      writeAtMemory();
    }
    if (memoryBits[1] == '1') {
      readFromMemory();
    }
  }
  
  result.e_mar = registers.getRegisterValue("mar");
  result.e_mdr = registers.getRegisterValue("mdr");
  result.e_pc = registers.getRegisterValue("pc");
  result.e_mbr = registers.getRegisterValue("mbr");
  result.e_sp = registers.getRegisterValue("sp");
  result.e_lv = registers.getRegisterValue("lv");
  result.e_cpp = registers.getRegisterValue("cpp");
  result.e_tos = registers.getRegisterValue("tos");
  result.e_opc = registers.getRegisterValue("opc");
  result.e_h = registers.getRegisterValue("h");

  return result;
}

void CaminhoDeDados::bipushFetch(const std::string &byte) {
  size_t transformed_byte = std::stoull(byte, nullptr, 2);
  registers.setRegisterValue("mbr", transformed_byte);
  registers.setRegisterValue("h", transformed_byte);
}