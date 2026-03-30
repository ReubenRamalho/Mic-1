#include "Registers.hpp"

Registers::Registers() : pc(0), ir("000000") {}

void Registers::setPC(std::size_t value) { pc = value; }
void Registers::incrementPC() { ++pc; }
void Registers::setIR(const std::string& value) { ir = value; }
std::size_t Registers::getPC() const { return pc; }
std::string Registers::getIR() const { return ir; }
