#include "Memory.h"
#include<iostream>
using namespace std;


Memory::Memory(int size) { memory.resize(size, "00"); }

int Memory::size() const { return memory.size(); }
void Memory::setCell(int address, string value) {
    if (address >= 0 && address < memory.size()) {
        memory[address] = value;
    }
    else {
        cerr << "Error: Address " << address << " out of bounds." << endl;
    }
}

string Memory:: getCell(int address) {
        return (address >= 0 && address < memory.size()) ? memory[address] : "00";
}

