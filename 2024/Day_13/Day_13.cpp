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

int main()
{
    std::cout << "AoC 2024 Day 13" << std::endl;
    std::string fileName = "Day_13/input.txt";
    // std::string fileName = "Day_13/example.txt";

    struct machine
    {
        int Sx = 0;
        int Sy = 0;
        int Ax = 0;
        int Bx = 0;
        int Ay = 0;
        int By = 0;
        int B = 0;
        int A = 0;
        int numTokens = 0;

        bool calculate()
        {
            bool foundSolution = false;
            int maxIters = 100;
            int min = maxIters * 3 + maxIters;
            for (int testA = 1; testA <= maxIters; testA++)
                for (int testB = 1; testB <= maxIters; testB++)
                    if (((testA * Ax) + (testB * Bx) == Sx) && ((testA * Ay) + (testB * By) == Sy))
                        if (3 * testA + testB < min)
                        {
                            A = testA;
                            B = testB;
                            numTokens = 3 * A + B;
                            foundSolution = true;
                        }

            return foundSolution;
        }
    };

    std::vector<machine> machines;

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    int step = 0;
    machine m;
    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ' ');
        std::vector<std::string> split;

        switch (step)
        {
        case 0:
            split = strSplit(splitUp.at(splitUp.size() - 1), '+');
            m.Ay = stoi(split.at(split.size() - 1));
            split = strSplit(splitUp.at(splitUp.size() - 2), '+');
            m.Ax = stoi(split.at(split.size() - 1));
            step++;
            break;
        case 1:
            split = strSplit(splitUp.at(splitUp.size() - 1), '+');
            m.By = stoi(split.at(split.size() - 1));
            split = strSplit(splitUp.at(splitUp.size() - 2), '+');
            m.Bx = stoi(split.at(split.size() - 1));
            step++;
            break;
        case 2:
            split = strSplit(splitUp.at(splitUp.size() - 1), '=');
            m.Sy = stoi(split.at(split.size() - 1));
            split = strSplit(splitUp.at(splitUp.size() - 2), '=');
            m.Sx = stoi(split.at(split.size() - 1));
            step++;
            machines.push_back(m);
            break;
        case 3:
            step = 0;
            break;
        }
    }
    file.close();

    int totalTokens = 0;
    for (machine m : machines)
        if (m.calculate())
            totalTokens += m.numTokens;

    // Part 1
    std::cout << "Part 1: " << totalTokens << std::endl;

    // Part 2
    std::cout << "Part 2: " << "Not implemented yet!" << std::endl;
    return 0;
}