#include "ALU.h"
#include<iostream>
using namespace std;
int ALU:: hexTodec(const string& hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}
float ALU:: decodeFloat8Bit(string hexValue) {
        int value = hexTodec(hexValue);
        int sign = (value & 0x80) ? -1 : 1;
        int exponent = ((value >> 4) & 0x07) - 4;
        float mantissa = 1 + ((value & 0x0F) / 16.0);
        return sign * mantissa * pow(2, exponent);
}

string ALU:: encodeFloat8Bit(float decimalValue) {
        int sign = (decimalValue < 0) ? 1 : 0;
        decimalValue = fabs(decimalValue);

        int exponent = floor(log2(decimalValue));
        exponent = max(-4, min(3, exponent));
        decimalValue /= pow(2, exponent);
        int mantissa = round((decimalValue - 1) * 16);

        int encodedValue = (sign << 7) | ((exponent + 4) << 4) | (mantissa & 0x0F);
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << encodedValue;
        return ss.str();
}

int ALU:: twoComplementToInt(const string& hexValue) {
        int value = stoi(hexValue, nullptr, 16);
        // If the number is negative (check the sign bit)
        if (value & 0x80) {
            // Convert to negative using two's complement
            value -= 256; // Subtract 2^8 for an 8-bit integer
        }
        return value;
}

string ALU:: intToTwoComplement(int value) {
        if (value < 0) {
            value += 256; // Convert to two's complement
        }
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << (value & 0xFF);
        return ss.str();
}

void ALU:: addInteger(int idxR, int idxS, int idxT, Register& reg) {
        string valS_hex = reg.getCell(idxS);
        string valT_hex = reg.getCell(idxT);

        int valS = twoComplementToInt(valS_hex);
        int valT = twoComplementToInt(valT_hex);
        int result = valS + valT;

        reg.setCell(idxR, intToTwoComplement(result)); // Store the result in two's complement
}

void ALU:: addTwoComplement(int idxR, int idxS, int idxT, Register& reg) {
        string valS_hex = reg.getCell(idxS);
        string valT_hex = reg.getCell(idxT);

        // Convert both registers to integers using two's complement
        int valS = twoComplementToInt(valS_hex);
        int valT = twoComplementToInt(valT_hex);

        // Perform addition
        int result = valS + valT;

        // Store the result in register idxR as two's complement
        reg.setCell(idxR, intToTwoComplement(result));
}

void ALU:: addFloatingPoint(int idxR, int idxS, int idxT, Register& reg) {
        float valS = decodeFloat8Bit(reg.getCell(idxS));
        float valT = decodeFloat8Bit(reg.getCell(idxT));
        float result = valS + valT;
        reg.setCell(idxR, encodeFloat8Bit(result));
}

    // bonus
string ALU:: rotateRight(string value, int steps) {
        int n = value.length();
        steps = steps % n; // Ensure steps are within the bounds of the string length
        return value.substr(n - steps) + value.substr(0, n - steps);
}

string ALU:: bitwiseOR(string valA, string valB) {
        int a = hexTodec(valA);
        int b = hexTodec(valB);
        return encodeFloat8Bit(a | b);
}

string ALU:: bitwiseAND(string valA, string valB) {
        int a = hexTodec(valA);
        int b = hexTodec(valB);
        return encodeFloat8Bit(a & b);
}

string ALU:: bitwiseXOR(string valA, string valB) {
        int a = hexTodec(valA);
        int b = hexTodec(valB);
        return encodeFloat8Bit(a ^ b);
}
