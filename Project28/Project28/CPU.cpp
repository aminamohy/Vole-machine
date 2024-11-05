#include "CPU.h"
#include<iostream>
using namespace std;

int CPU::hexTodec(const string& hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}
void CPU:: executeInstruction(const string& instruction, Register& reg, Memory& mem, int& PC, ALU& alu) {
        char opcode = instruction[0];
        int regIndex = hexTodec(instruction.substr(1, 1));
        int regS = hexTodec(instruction.substr(2, 1));
        int regT = hexTodec(instruction.substr(3, 1));
        stringstream log;
        log << "PC: " << PC << " Instruction: " << instruction << endl;
        cout << "PC: " << PC << " Instruction: " << instruction << endl;

        switch (opcode) {
        case '2': // Load immediate value into register R
            loadImmediate(regIndex, instruction.substr(2), reg);
            cout << "Loaded immediate value " << instruction.substr(2) << " into register " << regIndex << endl;

            break;
        case '1': // Load from memory into register R
            reg.setCell(regIndex, mem.getCell(hexTodec(instruction.substr(2))));
            cout << "Loaded value from memory address " << instruction.substr(2) << " into register " << regIndex << endl;
            break;
        case '3':
            if (instruction.substr(2) == "00") { // Store to screen
                cout << "Output to screen: " << reg.getCell(regIndex) << endl;
                OutputLog.push_back(hexTodec(reg.getCell(regIndex)));
            }
            else {
                mem.setCell(hexTodec(instruction.substr(2)), reg.getCell(regIndex));
                cout << "Stored value from register " << regIndex << " into memory address " << instruction.substr(2) << endl;
            }
            break;
        case '4': // Move register R to register S
            reg.setCell(regS, reg.getCell(regIndex));
            cout << "Moved value from register " << regIndex << " to register " << regS << endl;
            break;
        case '5': // Add two's complement integers
            alu.addInteger(regIndex, regS, regT, reg);
            cout << "Added values in registers " << regS << " and " << regT << ", result in register " << regIndex << endl;
            break;
        case '6': // Add floating-point values
            alu.addFloatingPoint(regIndex, regS, regT, reg);
            cout << "Added floating-point values in registers " << regS << " and " << regT << ", result in register " << regIndex << endl;
            break;
        case '7': // Bitwise OR
            reg.setCell(regIndex, alu.bitwiseOR(reg.getCell(regS), reg.getCell(regT)));
            cout << "Performed bitwise OR on registers " << regS << " and " << regT << ", result in register " << regIndex << endl;
            break;
        case '8': // Bitwise AND
            reg.setCell(regIndex, alu.bitwiseAND(reg.getCell(regS), reg.getCell(regT)));
            cout << "Performed bitwise AND on registers " << regS << " and " << regT << ", result in register " << regIndex << endl;
            break;
        case '9': // Bitwise XOR
            reg.setCell(regIndex, alu.bitwiseXOR(reg.getCell(regS), reg.getCell(regT)));
            cout << "Performed bitwise XOR on registers " << regS << " and " << regT << ", result in register " << regIndex << endl;
            break;
        case 'A': { // Rotate Right
            int steps = hexTodec(reg.getCell(regT));
            reg.setCell(regIndex, alu.rotateRight(reg.getCell(regS), steps));
            cout << "Rotated register " << regS << " right by " << steps << " steps, result in register " << regIndex << endl;
            break;
        }
        case 'B': // Jump

            if (reg.getCell(regIndex) == reg.getCell(0))
            {
                int address = hexTodec(instruction.substr(2));
                PC = address;
            }
            break;
        case 'D': // Jump and link (set PC to address, link return address)
            PC = hexTodec(instruction.substr(1));
            cout << "Jump and link to address " << PC << endl;
            break;
        case 'C': // Exit
            halt();
            break;
        default:
            cout << "Unknown opcode." << endl;
            break;
        }

        // Print register  and memory values after executing the instruction
        printRegisters(reg);
        printMemories(mem);
}

void CPU:: loadImmediate(int idxReg, const string& value, Register& reg) {
        reg.setCell(idxReg, value);
}

void CPU:: halt() {
        cout << "Execution halted." << endl;
        running = false;
}

void CPU:: printOutput() const {
        for (const auto& value : OutputLog) {
            cout << char(value) << " "; // Print the ASCII characters from OutputLog
        }
        cout << endl;
}

    void CPU:: printRegisters(Register reg) const {
        for (int i = 0; i < 16; i++) {
            cout << "R" << i << ": " << reg.getCell(i) << " ";
        }
        cout << endl;
    }


    void CPU::printMemories(Memory mem) const {
        cout << "The memory out put" << endl;
        cout << endl;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                int index = i * 16 + j;
                cout << mem.getCell(index) << " ";
            }
            cout << endl;
        }
    }

