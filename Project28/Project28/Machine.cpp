#include "Machine.h"
#include<iostream>
using namespace std;
Machine::Machine(int regSize, int memSize) : reg(regSize), mem(memSize) {}

    void Machine::loadProgramFromFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }
        string instruction;
        while (file >> instruction) {
            // Ensure instruction has enough characters
            if (instruction.length() >= 4) {
                string lastTwoChars = instruction.substr(2,2);
                mem.setCell(pc++, lastTwoChars);
            }
            else {
                cout << "Error: Invalid instruction format in file: " << instruction << endl;
            }
        }
    }
    void Machine::loadInstructions(vector<string>instructions) {

        
        for (auto instruction : instructions) {
            // Ensure instruction has enough characters
            if (instruction.length() >= 4) {
                string lastTwoChars = instruction.substr(2, 2);
                mem.setCell(pc++, lastTwoChars);
            }
        }
    }

    void Machine::run(string fileName) {
        pc = 0xA;
        ifstream file(fileName);
        string instruction;
        while (cpu.running && pc < mem.size()) {
            while (file >> instruction) {
                cpu.executeInstruction(instruction, reg, mem, pc, alu);
            }
        }
    }

    void Machine::runinstruction(vector<string>instructions) {
        pc = 0xA;

        string instruction;
        while (cpu.running && pc < mem.size()) {
            for (auto instruction : instructions) {
                cpu.executeInstruction(instruction, reg, mem, pc, alu);
            }
        }
    }
    void Machine::PrintStatus()
    {
        cout << endl;
        cout << "Expected output: ";
        cpu.printOutput();
    }


