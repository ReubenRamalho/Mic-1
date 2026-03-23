#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <string>

/**
 * @brief Representa uma instrução de 6 bits da ULA da Mic-1.
 *
 * A ordem dos sinais é:
 * F0 F1 ENA ENB INVA INC
 */
class Instruction
{
private:
    int sll8;
    int sra1;
    int f0;
    int f1;
    int ena;
    int enb;
    int inva;
    int inc;
    std::string ulaBits;
    std::string cBits;
    std::string bBits;

public:
    /**
     * @brief Constrói uma instrução nula.
     */
    Instruction();

    /**
     * @brief Constrói uma instrução a partir dos seus sinais individuais.
     * @param sll8 Bit SLL8.
     * @param sra1 Bit SRA1.
     * @param f0 Bit F0.
     * @param f1 Bit F1.
     * @param ena Bit ENA.
     * @param enb Bit ENB.
     * @param inva Bit INVA.
     * @param inc Bit INC.
     * @param ulaBits trecho da ULA da palavra binária original lida do arquivo.
     * @param cBits trecho do barramento C da palavra original lida do arquivo.
     * @param bBits trecho do barramento B da palavra original lida do arquivo.
     */
    Instruction(
        int sll8, int sra1, int f0, int f1, int ena, int enb, int inva, int inc,
        const std::string &ulaBits, const std::string &cBits, const std::string &bBits);

    /**
     * @brief Cria uma instrução a partir de uma string de 6 bits.
     * @param line Linha lida do arquivo.
     * @return Instrução construída.
     */
    static Instruction fromString(const std::string &line);

    /**
     * @brief Informa se a linha representa fim de programa.
     * @return true se a linha estiver vazia.
     */
    static bool isEndOfProgramLine(const std::string &line);

    /** @brief Retorna o bit SLL8. */
    int getSLL8() const;

    /** @brief Retorna o bit SRA1. */
    int getSRA1() const;

    /** @brief Retorna o bit F0. */
    int getF0() const;

    /** @brief Retorna o bit F1. */
    int getF1() const;

    /** @brief Retorna o bit ENA. */
    int getENA() const;

    /** @brief Retorna o bit ENB. */
    int getENB() const;

    /** @brief Retorna o bit INVA. */
    int getINVA() const;

    /** @brief Retorna o bit INC. */
    int getINC() const;

    /**
     * @brief Retorna o trecho da ULA da palavra binária original.
     * @return String com os 8 bits correspondentes à ULA da instrução.
     */
    std::string getulaBits() const;

    /**
     * @brief Retorna o trecho do barramento C da palabra original.
     * @return String com os 9 bits correspondentes ao barramento C.
     */
    std::string getcBits() const;

    /**
     * @brief Retorna o trecho do barramento B da palabra original.
     * @return String com os 4 bits correspondentes ao barramento B.
     */
    std::string getbBits() const;
};

#endif
