#include "Register.h"
#include<iostream>
using namespace std;

Register::Register(int size) { registers.resize(size, "00"); }
void Register::setCell(int index, string value) { if (index >= 0 && index < registers.size()) registers[index] = value; }
string Register::getCell(int index) { return (index >= 0 && index < registers.size()) ? registers[index] : "00"; }
