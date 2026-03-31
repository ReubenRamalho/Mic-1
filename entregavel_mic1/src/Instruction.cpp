#include "../include/Instruction.hpp"
#include <iostream>
#include <stdexcept>

Instruction::Instruction()
    : sll8(0), sra1(0), f0(0), f1(0), ena(0), enb(0), inva(0), inc(0),
      ulaBits("00000000"), cBits("000000000"), memoryBits("00"), bBits("0000") {
}

Instruction::Instruction(int sll8, int sra1, int f0, int f1, int ena, int enb,
                         int inva, int inc, const std::string &ulaBits,
                         const std::string &cBits,
                         const std::string &memoryBits,
                         const std::string &bBits)
    : sll8(sll8), sra1(sra1), f0(f0), f1(f1), ena(ena), enb(enb), inva(inva),
      inc(inc), ulaBits(ulaBits), cBits(cBits), memoryBits(memoryBits),
      bBits(bBits) {}

Instruction Instruction::fromString(const std::string &line) {
  if (line.size() != 23) {
    throw std::invalid_argument(
        "Cada instrução deve conter exatamente 23 bits.");
  }

  for (char c : line) {
    if (c != '0' && c != '1') {
      throw std::invalid_argument(
          "A instrução deve conter apenas caracteres '0' e '1'.");
    }
  }

  std::string ulaBits = line.substr(0, 8);
  std::string cBits = line.substr(8, 9);
  std::string memoryBits = line.substr(17, 2);
  std::string bBits = line.substr(19, 4);

  return Instruction(line[0] - '0', line[1] - '0', line[2] - '0', line[3] - '0',
                     line[4] - '0', line[5] - '0', line[6] - '0', line[7] - '0',
                     ulaBits, cBits, memoryBits, bBits);
}

bool Instruction::isEndOfProgramLine(const std::string &line) {
  return line.empty();
}

int Instruction::getSLL8() const { return sll8; }
int Instruction::getSRA1() const { return sra1; }
int Instruction::getF0() const { return f0; }
int Instruction::getF1() const { return f1; }
int Instruction::getENA() const { return ena; }
int Instruction::getENB() const { return enb; }
int Instruction::getINVA() const { return inva; }
int Instruction::getINC() const { return inc; }
std::string Instruction::getulaBits() const { return ulaBits; }
std::string Instruction::getcBits() const { return cBits; }
std::string Instruction::getMemoryBits() const { return memoryBits; }
std::string Instruction::getbBits() const { return bBits; }

std::vector<Instruction> Instruction::createDup() {
  std::vector<Instruction> instructions;
  // MAR = SP = SP + 1
  instructions.push_back(Instruction::fromString("00110101000001001000100"));

  // MDR = TOS; wr
  instructions.push_back(Instruction::fromString("00110100000000010100111"));

  return instructions;
}

std::vector<Instruction> Instruction::createIload(const int &x) {
  std::vector<Instruction> instructions;

  // H = LV
  instructions.push_back(Instruction::fromString("00110100100000000000101"));

  for (int i = 0; i < x; i++) {
    // H = H + 1
    instructions.push_back(Instruction::fromString("00111001100000000000000"));
  }

  // MAR = H; rd
  instructions.push_back(Instruction::fromString("00111000000000001010000"));
  // MAR = SP = SP + 1; wr
  instructions.push_back(Instruction::fromString("00110101000001001100100"));
  // TOS = MDR
  instructions.push_back(Instruction::fromString("00110100001000000000000"));

  return instructions;
}

std::vector<Instruction> Instruction::createBipush(const std::string &byte) {
  std::vector<Instruction> instructions;

  // SP = MAR = SP + 1
  instructions.push_back(Instruction::fromString("00110101000001001000100"));
  // fetch
  instructions.push_back(Instruction::fromString(byte + "000000000110000"));
  // MDR = TOS = H; wr
  instructions.push_back(Instruction::fromString("00111000001000010100000"));

  return instructions;
}
