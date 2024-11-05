#pragma once
#include<string>
#include<vector>
#include "Register.h"
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;
class ALU
{
public:
    int hexTodec(const string& hexStr);
    float decodeFloat8Bit(string hexValue);

    string encodeFloat8Bit(float decimalValue);

    int twoComplementToInt(const string& hexValue);

    string intToTwoComplement(int value);

    void addInteger(int idxR, int idxS, int idxT, Register& reg);

    void addTwoComplement(int idxR, int idxS, int idxT, Register& reg);

    void addFloatingPoint(int idxR, int idxS, int idxT, Register& reg);

    // bonus
    string rotateRight(string value, int steps);

    string bitwiseOR(string valA, string valB);

    string bitwiseAND(string valA, string valB);

    string bitwiseXOR(string valA, string valB);
};

