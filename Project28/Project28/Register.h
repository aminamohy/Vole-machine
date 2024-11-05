#pragma once
#include<string>
#include<vector>
using namespace std;
class Register
{
private:
    vector<string> registers;
public:
    Register(int size = 16);
    void setCell(int index, string value);
    string getCell(int index);
};


