#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

uint32_t get_uint32(std::string hexString);
std::string get_hex(uint32_t hexNum);
std::string to_upper(std::string str);
bool substr_exists(std::string& str, std::string substr);

int main() {
    std::unordered_map<std::string, unsigned int> opcodeNum;
    std::unordered_map<std::string, std::uint32_t> registers;
    opcodeNum["ADD"] = 0;
    opcodeNum["SUB"] = 1;
    opcodeNum["AND"] = 2;
    opcodeNum["ORR"] = 3;
    opcodeNum["XOR"] = 4;
    opcodeNum["ASR"] = 5;
    opcodeNum["LSR"] = 6;
    opcodeNum["LSL"] = 7;
    opcodeNum["MOV"] = 8;
    registers["R0"] = 0;
    registers["R1"] = 0;
    registers["R2"] = 0;
    registers["R3"] = 0;
    registers["R4"] = 0;
    registers["R5"] = 0;
    registers["R6"] = 0;
    registers["R7"] = 0;

    std::string fileName = "Programming-Project-3.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        throw std::runtime_error("File does not exist.");
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        std::vector<std::string> data;
        std::string chars, opcode, operand0, operand1, operand2;
        bool immVal = false;
        
        // Parse single instruction
        std::stringstream temp(line);
        immVal = substr_exists(line, "#");
        while (std::getline(temp, chars, ' '))
        {
            data.push_back(chars);
        }

        // Get opcode
        opcode = to_upper(data[0]);
        if (opcodeNum.find(opcode) == opcodeNum.end())
        {
            throw std::runtime_error("Invalid opcode.");
            return 1;
        }

        // Get operand0
        data[1].pop_back();
        operand0 = to_upper(data[1]);
        if (registers.find(operand0) == registers.end())
        {
            throw std::runtime_error("Invalid register " + operand0);
            return 1;
        }
        
        // Get operand1
        if (opcode != "MOV")
        {
            data[2].pop_back();
            operand1 = to_upper(data[2]);

            // Get operand2
            if (immVal)
            {
                operand2 = data[3].substr(1); // Remove #
            } else {
                operand2 = to_upper(data[3]);
            }
        } else {
            operand1 = data[2].substr(1); // Remove #
        }

        // Logic
        uint32_t op1 = (opcode == "MOV") ? get_uint32(operand1) : registers[operand1];
        uint32_t op2 = (immVal) ? get_uint32(operand2) : registers[operand2];
        unsigned int result = 0;
        switch (opcodeNum[opcode])
        {
            case 0: // ADD
                result = op1 + op2;
                break;
            case 1: // SUB
                result = op1 - op2;
                break;
            case 2: // AND
                result = op1 & op2;
                break;
            case 3: // ORR
                result = op1 | op2;
                break;
            case 4: // XOR
                result = op1 ^ op2;
                break;
            case 5: // ASR
                result = ((int32_t) op1) >> ((int32_t) op2);
                break;
            case 6: // LSR
                result = op1 >> op2;
                break;
            case 7: // LSL
                result = op1 << op2;
                break;
            case 8: // MOV
                result = op1;
                break;
            default:
                throw std::runtime_error("Switch error.");
                return 1;
        }
        registers[operand0] = result;

        // Output instruction
        std::cout << opcode << " " << operand0 << ", ";
        if (opcode == "MOV")
        {
            std::cout << "#" << operand1 << "\n";
        } else {
            std::cout << operand1 << ", ";
            if (immVal)
                std::cout << "#";
            std::cout << operand2 << "\n";
        }
        // Output registers
        for (size_t i = 0; i < registers.size(); i++)
        {
            std::string regName = "R" + std::to_string(i);
            std::string out = regName + ": " + get_hex(registers[regName]);
            std::cout  << std::setw(16) << std::left << out;
            if (i == 3)
                std::cout << "\n";
        }
        std::cout << "\n\n";
    }
    inFile.close();
    return 0;
}

uint32_t get_uint32(std::string hexString)
{
    uint32_t result;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> result;
    return result;
}

std::string get_hex(uint32_t hexNum)
{
    std::stringstream ss;
    ss << std::hex << hexNum;
    return to_upper("0x" + ss.str());
}

std::string to_upper(std::string str)
{
    std::locale loc;
    std::string result = "";
    for (std::size_t i = 0; i < str.length(); ++i)
    {
        result += std::toupper(str[i], loc);
    }
    return result;
}

bool substr_exists(std::string& str, std::string substr)
{
    return str.find(substr) != std::string::npos;
}
