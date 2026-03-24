# Etapa 1 - ULA da Mic-1 em C++

Este projeto implementa a **Etapa 1** do projeto de Arquitetura de Computadores II em C++, utilizando **orientação a objetos** para organizar os componentes da simulação da ULA da Mic-1.

A implementação foi estruturada em classes separadas para facilitar a leitura, manutenção e explicação do código.

---

## Objetivo

O programa simula a execução da ULA da Mic-1 a partir de um arquivo de instruções de 6 bits no formato:

```txt
F0 F1 ENA ENB INVA INC
````

Cada linha do arquivo representa uma instrução da ULA.

Durante a execução, o simulador:

* lê as instruções do arquivo;
* atualiza os registradores `PC` e `IR`;
* executa a operação correspondente na ULA;
* gera um arquivo de log com o histórico da execução.

---

## Observação sobre o log

Nesta implementação, os valores de `a` e `b` registrados no log representam os **valores efetivamente utilizados pela ULA** após a aplicação dos sinais de controle (`ENA`, `ENB` e `INVA`), e não apenas os valores originais de entrada.

Isso significa, por exemplo, que:

* se `ENA = 0`, então o valor efetivo de `a` usado na operação será `0`;
* se `ENB = 0`, então o valor efetivo de `b` usado na operação será `0`;
* se `INVA = 1`, então o valor efetivo de `a` será invertido antes da operação.

Essa interpretação foi adotada por ser a mais coerente com o funcionamento lógico da ULA.

---

## Estrutura do projeto

```txt
etapa1_mic1/
├── include/        # Arquivos de cabeçalho (.hpp)
├── src/            # Implementações (.cpp)
├── data/           # Arquivos de entrada e saída
├── main.cpp        # Ponto de entrada do programa
├── Makefile        # Compilação do projeto
└── README.md       # Documentação
```

---

## Classes do projeto

### `Instruction`

Representa uma instrução de 6 bits da ULA e permite acessar separadamente os campos:

* `F0`
* `F1`
* `ENA`
* `ENB`
* `INVA`
* `INC`

### `ALU`

Implementa a lógica da ULA.
A operação é determinada pelos bits `F0` e `F1`.

Nesta implementação:

* `00` → `A AND B`
* `01` → `A OR B`
* `10` → `NOT(B)`
* `11` → `A + B + INC`

### `ProgramMemory`

Responsável por carregar as instruções a partir de um arquivo texto.

### `Registers`

Representa os registradores usados na simulação:

* `PC` (Program Counter)
* `IR` (Instruction Register)

### `ExecutionLogger`

Gera o arquivo de log no formato exigido pelo projeto.

### `Simulator`

Integra todos os componentes do sistema:

* memória de programa,
* registradores,
* ULA,
* logger.

### `BinaryUtils`

Contém funções auxiliares para conversão e manipulação de valores binários.

---

## Compilação

Para compilar o projeto, execute:

```bash
make
```

Isso irá gerar o executável:

```bash
etapa1
```

---

## Execução

A execução é feita por linha de comando, informando:

1. o valor de `A`
2. o valor de `B`
3. o arquivo de instruções
4. opcionalmente, o arquivo de log

### Sintaxe

```bash
./etapa1 <A> <B> <arquivo_instrucoes> [arquivo_log]
```

### Exemplos

Usando valores hexadecimais sem prefixo:

```bash
./etapa1 FFFFFFFF 00000001 data/programa_etapa1.txt
```

Usando valores hexadecimais com prefixo `0x`:

```bash
./etapa1 0xFFFFFFFF 0x00000001 data/programa_etapa1.txt
```

Especificando também o arquivo de saída:

```bash
./etapa1 FFFFFFFF 00000001 data/programa_etapa1.txt data/log_etapa1.txt
```

---

## Arquivo de entrada

O arquivo de instruções deve conter **uma instrução por linha**, com 6 bits por instrução.

Exemplo:

```txt
111100
110101
110100
011100
```

Linhas vazias são ignoradas.

---

## Formato do log

O log gerado contém:

* valores iniciais de `a` e `b`;
* ciclos de execução;
* valor do `PC`;
* valor do `IR`;
* valor efetivo de `a`;
* valor efetivo de `b`;
* valor de saída `s`;
* valor de `co` (carry-out / vai-um);
* indicação de fim de programa.

---

## Exemplo de interpretação

Considere a instrução:

```txt
110101
```

Separando os campos:

* `F0 = 1`
* `F1 = 1`
* `ENA = 0`
* `ENB = 1`
* `INVA = 0`
* `INC = 1`

Se os valores de entrada forem:

* `A = FFFFFFFF`
* `B = 00000001`

então:

* como `ENA = 0`, o valor efetivo de `A` será `00000000`;
* como `ENB = 1`, o valor efetivo de `B` será `00000001`;
* como `F0F1 = 11`, a operação será soma;
* como `INC = 1`, a operação executada será:

```txt
0 + 1 + 1 = 2
```

Logo:

* `a = 00000000000000000000000000000000`
* `b = 00000000000000000000000000000001`
* `s = 00000000000000000000000000000010`
* `co = 0`

---

## Observação final

Durante os testes, foi identificada uma diferença entre esta implementação e um exemplo de log fornecido como referência para o ciclo 2 da instrução `110101`.

A implementação deste projeto adota como critério registrar no log os **valores efetivamente usados pela ULA**, por considerar essa interpretação a mais consistente com os sinais de habilitação da arquitetura.
