#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> strSplit(const std::string &in, const char &delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (char c : in)
    {
        if (c == delimiter)
        {
            out.push_back(temp);
            temp = "";
        }
        else
            temp = temp + c;
    }
    out.push_back(temp);
    return out;
}

int pow(int base, int exp)
{
    int result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

std::vector<int> toBase3(int number, int length)
{
    std::vector<int> base3;
    for (int i = 0; i < length; ++i)
    {
        base3.push_back(number % 3);
        number /= 3;
    }
    return base3;
}

int main()
{
    std::cout << "AoC 2024 Day 7" << std::endl;
    std::string fileName = "Day_7/input.txt";
    // std::string fileName = "Day_7/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    struct equation
    {
        unsigned long long result;
        std::vector<int> operands;
    };
    std::vector<equation> equations;
    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ' ');
        std::string temp = splitUp.at(0);
        equation eq;
        eq.result = stoull(temp.substr(0, temp.length() - 1));

        for (int i = 1; i < splitUp.size(); i++)
        {
            eq.operands.push_back(stoi(splitUp.at(i)));
        }
        equations.push_back(eq);
    }
    file.close();

    // Part 1
    unsigned long long numPossible = 0;
    for (auto eq : equations)
    {
        int numPermutations = pow(2, eq.operands.size() - 1);
        for (int i = 0; i < numPermutations; i++)
        {
            unsigned long long temp = eq.operands.at(0);
            for (int j = 1; j < eq.operands.size(); j++)
            {
                if ((i >> (j - 1)) & 1)
                    temp *= (unsigned long long)eq.operands.at(j);
                else
                    temp += (unsigned long long)eq.operands.at(j);
            }

            if (temp == eq.result)
            {
                numPossible += eq.result;
                break;
            }
        }
    }
    std::cout << "Part 1: " << numPossible << std::endl;

    // Part 2
    numPossible = 0;
    for (auto eq : equations)
    {
        int numPermutations = pow(3, eq.operands.size() - 1);
        for (int i = 0; i < numPermutations; i++)
        {
            std::vector<int> perm = toBase3(i, eq.operands.size() - 1);
            unsigned long long temp = eq.operands.at(0);
            for (int j = 1; j < eq.operands.size(); j++)
            {
                if (perm.at(j - 1) == 0)
                    temp *= (unsigned long long)eq.operands.at(j);
                else if (perm.at(j - 1) == 1)
                    temp += (unsigned long long)eq.operands.at(j);
                else
                {
                    std::string tempStr = std::to_string(temp);
                    tempStr += std::to_string(eq.operands.at(j));
                    temp = stoull(tempStr);
                }
            }

            if (temp == eq.result)
            {
                numPossible += eq.result;
                break;
            }
        }
    }
    std::cout << "Part 2: " << numPossible << std::endl;
    return 0;
}