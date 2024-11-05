#pragma once
#include<vector>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"
using namespace std;
class CPU
{

public:
    bool running = true;
    vector<int>OutputLog;
    int hexTodec(const string& hexStr);
    void executeInstruction(const string& instruction, Register& reg, Memory& mem, int& PC, ALU& alu);
        

    void loadImmediate(int idxReg, const string& value, Register& reg);

    void halt();

    void printOutput() const;

    void printRegisters(Register reg) const;


    void printMemories(Memory mem) const;

};

