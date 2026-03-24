#include "../include/Registers.hpp"
#include "../include/BinaryUtils.hpp"
#include <fstream>
#include <stdexcept>

Registers::Registers() : mar(0), mdr(0), pc(0), mbr(0), sp(0), lv(0), cpp(0), tos(0), opc(0), h(0), ir("000000") {}

/**
 * @brief Carrega os valores dos registradores a partir de um arquivo texto.
 * @param fileName Caminho do arquivo de instruções.
 */
void Registers::loadFromFile(const std::string &fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Nao foi possivel abrir o arquivo de programa: " + fileName);
    }

    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        int info = 0;
        std::string registerName = "";
        std::string cleaner = "";
        std::string registerValue = "";

        for (char c : line)
        {
            if (!std::isspace(static_cast<unsigned char>(c)))
            {
                switch (info)
                {
                case 0:
                    registerName += c;
                    break;
                case 1:
                    cleaner += c;
                    break;
                case 2:
                    registerValue += c;
                    break;
                }
            }
            else
            {
                info++;
            }
        }

        if (registerName.empty() || cleaner.empty() || registerValue.empty())
        {
            continue;
        }

        try
        {
            setRegisterValue(registerName, toString32bits(registerValue));
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(
                "Erro na linha " + std::to_string(lineNumber) + ": " + e.what());
        }
    }
}

/**
 * @brief atualiza o valor de um registrador
 * @param registerName nome do registrador
 * @param value        valor que o registrador deve assumir
 */
void Registers::setRegisterValue(const std::string &registerName, std::size_t value)
{
    if (registerName == "mar")
    {
        mar = value;
    }
    else if (registerName == "mdr")
    {
        mdr = value;
    }
    else if (registerName == "pc")
    {
        pc = value;
    }
    else if (registerName == "mbr")
    {
        mbr = value;
    }
    else if (registerName == "sp")
    {
        sp = value;
    }
    else if (registerName == "lv")
    {
        lv = value;
    }
    else if (registerName == "cpp")
    {
        cpp = value;
    }
    else if (registerName == "tos")
    {
        tos = value;
    }
    else if (registerName == "opc")
    {
        opc = value;
    }
    else if (registerName == "h")
    {
        h = value;
    }
    else
    {
        throw std::runtime_error("esse registrador não existe: " + registerName);
    }
}

/**
 * @brief Recupera o valor armazenado em um registrador
 * @param registerName nome do registrador.
 */
size_t Registers::getRegisterValue(const std::string &registerName) const
{
    if (registerName == "mar")
    {
        return this->mar;
    }
    else if (registerName == "mdr")
    {
        return mdr;
    }
    else if (registerName == "pc")
    {
        return pc;
    }
    else if (registerName == "mbr")
    {
        return mbr;
    }
    else if (registerName == "sp")
    {
        return sp;
    }
    else if (registerName == "lv")
    {
        return lv;
    }
    else if (registerName == "cpp")
    {
        return cpp;
    }
    else if (registerName == "tos")
    {
        return tos;
    }
    else if (registerName == "opc")
    {
        return opc;
    }
    else if (registerName == "h")
    {
        return h;
    }
    else
    {
        throw std::runtime_error("esse registrador não existe: " + registerName);
    }
}

void Registers::setIR(const std::string &value) { ir = value; }
std::string Registers::getIR() const { return ir; }
