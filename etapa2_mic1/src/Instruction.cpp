#include "../include/Instruction.hpp"
#include <stdexcept>

Instruction::Instruction() : sll8(0), sra1(0), f0(0), f1(0), ena(0), enb(0), inva(0), inc(0), rawBits("00000000") {}

Instruction::Instruction(
    int sll8, int sra1, int f0, int f1, int ena, int enb, int inva, int inc,
    const std::string& rawBits
)   : sll8(sll8), sra1(sra1), f0(f0), f1(f1), ena(ena), enb(enb), inva(inva), inc(inc), rawBits(rawBits) {}

Instruction Instruction::fromString(const std::string& line) {
    if (line.size() != 8) {
        throw std::invalid_argument("Cada instrução deve conter exatamente 8 bits.");
    }

    for (char c : line) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("A instrução deve conter apenas caracteres '0' e '1'.");
        }
    }

    return Instruction(line[0] - '0',
                       line[1] - '0',
                       line[2] - '0',
                       line[3] - '0',
                       line[4] - '0',
                       line[5] - '0',
                       line[6] - '0',
                       line[7] - '0',
                       line);
}

bool Instruction::isEndOfProgramLine(const std::string& line) {
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
std::string Instruction::getRawBits() const { return rawBits; }
