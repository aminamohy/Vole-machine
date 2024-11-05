#pragma once
#include "Register.h"
#include "Memory.h"
#include "ALU.H"
#include "CPU.h"
#include <fstream>
using namespace std;
class Machine
{
private:
    int pc = 0xA;
    Register reg;
    Memory mem;
    CPU cpu;
    ALU alu;
public:
    Machine(int regSize, int memSize);

    void loadProgramFromFile(const string& fileName);
    void loadInstructions(vector<string>instructions);

    void run(string fileName);

    void runinstruction(vector<string>instructions);
    void PrintStatus();

};

