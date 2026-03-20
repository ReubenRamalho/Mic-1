#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstddef>
#include <string>

/**
 * @brief Representa os registradores usados na Etapa 1.
 */
class Registers {
private:
    std::size_t pc;
    std::string ir;

public:
    /**
     * @brief Inicializa os registradores com valores padrão.
     */
    Registers();

    /**
     * @brief Define o valor do PC.
     * @param value Novo valor do PC.
     */
    void setPC(std::size_t value);

    /**
     * @brief Incrementa o PC em uma unidade.
     */
    void incrementPC();

    /**
     * @brief Define o valor do IR.
     * @param value Palavra de instrução atual.
     */
    void setIR(const std::string& value);

    /**
     * @brief Retorna o valor atual do PC.
     * @return Valor atual do PC.
     */
    std::size_t getPC() const;

    /**
     * @brief Retorna o valor atual do IR.
     * @return Palavra binária armazenada em IR.
     */
    std::string getIR() const;
};

#endif
