#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <string>

/**
 * @brief Representa uma instrução de 6 bits da ULA da Mic-1.
 *
 * A ordem dos sinais é:
 * F0 F1 ENA ENB INVA INC
 */
class Instruction {
private:
    int sll8;
    int sra1;
    int f0;
    int f1;
    int ena;
    int enb;
    int inva;
    int inc;
    std::string rawBits;

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
     * @param rawBits Palavra binária original lida do arquivo.
     */
    Instruction(
        int sll8, int sra1, int f0, int f1, int ena, int enb, int inva, int inc,
        const std::string& rawBits
    );

    /**
     * @brief Cria uma instrução a partir de uma string de 6 bits.
     * @param line Linha lida do arquivo.
     * @return Instrução construída.
     */
    static Instruction fromString(const std::string& line);

    /**
     * @brief Informa se a linha representa fim de programa.
     * @return true se a linha estiver vazia.
     */
    static bool isEndOfProgramLine(const std::string& line);

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
     * @brief Retorna a palavra binária original.
     * @return String com os 8 bits lidos do arquivo.
     */
    std::string getRawBits() const;
};

#endif
