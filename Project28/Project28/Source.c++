#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"
#include "CPU.h"
#include "Machine.h"
using namespace std;

int hexTodec(const string& hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}

bool isValid(const string& str) {
    for (char c : str) {
        if (!isxdigit(c) && c != 'A' && c != 'B' && c != 'C' && c != 'D' && c != 'E' && c != 'F') {
            return false;
        }
    }
    return true;
}

void menu()
{
    cout << "1)Run file" << endl;
    cout << "2)Run instruction" << endl;
    cout << "3)Print status" << endl;
    cout << "4)Exit" << endl;
    cout << endl;
}
int main() {
    Machine machine(16, 256);
    
    while (true)
    {
        menu();
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            string filename;
            cout << "Enter name of the file with its extension: ";
            cin >> filename;
            machine.loadProgramFromFile(filename);
            machine.run(filename);
            cout << endl;
        }
        else if (choice == 2)
        {
            
            int num;
            cout << "Enter number of instructions: ";
            cin >> num;
            
            vector<string>instructions;
            for (int i = 0;i < num;i++)
            {
                cout << "Enter the instruction: ";
                string instruction;
                cin >> instruction;
                instructions.push_back(instruction);
                
            }
            machine.loadInstructions(instructions);
            machine.runinstruction(instructions);
            cout << endl;
        }
        else if (choice == 3)
        {
            machine.PrintStatus();
            cout << endl;
        }
        else if (choice == 4)
        {
            cout << "Thanks for using our program\n";
            break;
        }
        else
        {
            cout << "Invalid choice ,please choose from 1 to 3 or 4 to exit.\n";
            cout << endl;
        }

    }
    return 0;
}