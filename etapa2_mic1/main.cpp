#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Simulator.hpp"

/**
 * @brief Converte uma string para um valor de 32 bits sem sinal.
 *
 * Aceita:
 * - hexadecimal com prefixo 0x
 * - hexadecimal sem prefixo (ex.: FFFFFFFF)
 * - decimal
 *
 * @param text Texto recebido pela linha de comando.
 * @return uint32_t Valor convertido.
 */
static uint32_t parseWord32(const std::string& text) {
    std::size_t processed = 0;
    uint32_t value = 0;

    if (text.size() > 2 && (text[0] == '0') && (text[1] == 'x' || text[1] == 'X')) {
        value = static_cast<uint32_t>(std::stoul(text, &processed, 16));
    } else {
        bool hasHexLetter = false;
        for (char c : text) {
            if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
                hasHexLetter = true;
                break;
            }
        }

        if (hasHexLetter) {
            value = static_cast<uint32_t>(std::stoul(text, &processed, 16));
        } else {
            value = static_cast<uint32_t>(std::stoul(text, &processed, 10));
        }
    }

    if (processed != text.size()) {
        throw std::invalid_argument("Valor numérico inválido: " + text);
    }

    return value;
}

/**
 * @brief Ponto de entrada do programa.
 *
 * Uso:
 * ./etapa1 <A> <B> <arquivo_instrucoes> [arquivo_log]
 *
 * Exemplos:
 * ./etapa1 FFFFFFFF 00000001 data/programa_etapa1.txt
 * ./etapa1 0xFFFFFFFF 0x00000001 data/programa_etapa1.txt
 * ./etapa1 4294967295 1 data/programa_etapa1.txt
 *
 * @param argc Quantidade de argumentos.
 * @param argv Vetor de argumentos.
 * @return int Código de saída do programa.
 */
int main(int argc, char* argv[]) {
    try {
        if (argc < 4 || argc > 5) {
            std::cerr << "Uso:\n";
            std::cerr << "  ./etapa1 <A> <B> <arquivo_instrucoes> [arquivo_log]\n\n";
            std::cerr << "Exemplos:\n";
            std::cerr << "  ./etapa1 FFFFFFFF 00000001 data/programa_etapa1.txt\n";
            std::cerr << "  ./etapa1 0xFFFFFFFF 0x00000001 data/programa_etapa1.txt\n";
            return 1;
        }

        const uint32_t inputA = parseWord32(argv[1]);
        const uint32_t inputB = parseWord32(argv[2]);
        const std::string programFile = argv[3];
        const std::string logFile = (argc == 5) ? argv[4] : "data/log_etapa1.txt";

        Simulator simulator(inputA, inputB);
        simulator.loadProgram(programFile);
        simulator.run(logFile);

        std::cout << "Execução concluída com sucesso.\n";
        std::cout << "Programa lido: " << programFile << "\n";
        std::cout << "Log gerado: " << logFile << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return 1;
    }

    return 0;
}