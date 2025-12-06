#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

std::chrono::high_resolution_clock::time_point tickTime;
std::chrono::high_resolution_clock::time_point tockTime;

void static inline tick(){
    tickTime = std::chrono::high_resolution_clock::now();
}

void static inline tock(){
    tockTime = std::chrono::high_resolution_clock::now();
}

void static inline printMicroseconds() {
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tockTime - tickTime).count() << " us" << std::endl;
}

std::vector<std::string> strSplit(const std::string &in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (char c : in)
    {
        if (c == delimiter)
        {
            if (temp != "") out.push_back(temp);
            temp = "";
        }
        else
            temp = temp + c;
    }
    if (temp != "") out.push_back(temp);
    return out;
}

int main()
{
    std::cout << "AoC 2025 Day 6" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::string> splitUp;
    std::vector<std::vector<int>> operands;
    std::vector<char> operations;
    while(std::getline(file, line)){
        lines.push_back(line);
        splitUp = strSplit(line, ' ');
        if ((splitUp[0] != "+" && splitUp[0] != "*")){
            std::vector<int> operandLine;
            for (auto s:splitUp)
                operandLine.push_back(stoi(s));

            operands.push_back(operandLine);
        } else {
            for (auto s:splitUp) operations.push_back(s[0]);
        }
    }
    file.close();

    // Part 1
    tick();
    unsigned long long sum = 0;
    for (int i = 0; i < operations.size(); i ++){
        char op = operations[i];
        unsigned long long temp;
        switch (op){
            case '+':
                temp = 0;
                for (int j = 0; j < operands.size(); j++) temp += operands[j][i];
                break;
            case '*':
                temp = 1;
                for (int j = 0; j < operands.size(); j++) temp *= operands[j][i];
                break;
        }
        sum += temp;
    }
    tock();
    std::cout << "Part 1: " << sum << std::endl;
    printMicroseconds();

    // Part 2
    tick();
    sum = 0;
    int opIdx = operations.size()-1;
    unsigned long long temp;
    for (int j = lines[0].size()-1; j >=0 ; j--){
        std::string numString = "";
            for (int i = 0; i < lines.size()-1; i++){
                if (lines[i][j] != ' ') numString += lines[i][j];
        }

        if (numString == ""){
            sum += temp;
            opIdx --;
            if (operations[opIdx] == '+') temp = 0;
            else temp = 1;
        }
        else {
            switch (operations[opIdx]){
                case '+':
                    temp += stoi(numString);
                    break;
                case '*':
                    temp *= stoi(numString);
                    break;
            }
        }
    }
    sum += temp;
    tock();
    std::cout << "Part 2: " << sum << std::endl;
    printMicroseconds();
    return 0;
}
