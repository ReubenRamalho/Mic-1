#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstddef>
#include <string>

/**
 * @brief Representa os registradores usados na Etapa 1.
 */
class Registers
{
private:
    std::size_t mar;
    std::size_t mdr;
    std::size_t pc;
    std::size_t mbr;
    std::size_t sp;
    std::size_t lv;
    std::size_t cpp;
    std::size_t tos;
    std::size_t opc;
    std::size_t h;
    std::string ir;

    bool invalidRegister;

public:
    /**
     * @brief Inicializa os registradores com valores padrão.
     */
    Registers();

    /**
     * @brief Carrega os valores dos registradores a partir de um arquivo texto.
     * @param fileName Caminho do arquivo de instruções.
     */
    void loadFromFile(const std::string &fileName);

    /**
     * @brief atualiza o valor de um registrador
     * @param registerName nome do registrador
     * @param value        valor que o registrador deve assumir
     */
    void setRegisterValue(const std::string &registerName, std::size_t value);

    /**
     * @brief Recupera o valor armazenado em um registrador
     * @param registerName nome do registrador.
     */
    size_t getRegisterValue(const std::string &registerName);

    /**
     * @brief Define o valor do IR.
     * @param value Palavra de instrução atual.
     */
    void setIR(const std::string &value);

    /**
     * @brief Retorna o valor atual do IR.
     * @return Palavra binária armazenada em IR.
     */
    std::string getIR() const;
};

#endif
