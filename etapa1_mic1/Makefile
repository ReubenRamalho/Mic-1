CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = etapa1
SOURCES = main.cpp \
          src/Instruction.cpp \
          src/ALU.cpp \
          src/ProgramMemory.cpp \
          src/Registers.cpp \
          src/BinaryUtils.cpp \
          src/ExecutionLogger.cpp \
          src/Simulator.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
