#pragma once
#include<string>
#include<vector>
using namespace std;
class Memory
{
private:
    vector<string> memory;
public:
    Memory(int size = 256);

    int size() const;
    void setCell(int address, string value);

    string getCell(int address);
};

