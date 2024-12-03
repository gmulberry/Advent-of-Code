#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

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

bool argIsGood(const std::string &arg)
{
    bool good = true;
    if (arg.length() > 0 && arg.length() < 4)
    {
        for (int j = 0; j < arg.length(); j++)
            if (!isdigit(arg.at(j)))
                good = false;
    }
    else
        good = false;
    return good;
}

int main()
{
    std::cout << "AoC 2024 Day 3" << std::endl;
    std::string fileName = "Day_3/input.txt";
    // std::string fileName = "Day_3/example.txt";
    // std::string fileName = "Day_3/example2.txt";

    // read in the file
    std::ifstream file(fileName);
    std::stringstream mem;
    char c;
    while (file.get(c))
        mem << c;

    file.close();

    // Part 1
    int total = 0;
    std::vector<std::string> splitUp = strSplit(mem.str(), '(');
    for (int i = 0; i < splitUp.size() - 1; i++)
    {
        std::string leftSide = splitUp.at(i);
        std::string rightSide = splitUp.at(i + 1);

        // check left side for multiply instruction
        if (leftSide.size() >= 3 && leftSide.substr(leftSide.size() - 3) == "mul")
        {
            // now check right side for valid arguments
            std::vector<std::string> betweenBrackets = strSplit(rightSide, ')');
            std::vector<std::string> args = strSplit(betweenBrackets.at(0), ',');
            if (args.size() == 2 && argIsGood(args.at(0)) && argIsGood(args.at(1)))
            {
                int a0 = stoi(args.at(0));
                int a1 = stoi(args.at(1));
                int result = a0 * a1;
                total += result;
                std::cout << a0 << " * " << a1 << " = " << result << std::endl;
            }
        }
    }
    std::cout << "Part 1: " << total << std::endl;

    // Part 2
    total = 0;
    bool enabled = true;
    for (int i = 0; i < splitUp.size() - 1; i++)
    {
        std::string leftSide = splitUp.at(i);
        std::string rightSide = splitUp.at(i + 1);

        // check left side for do instruction
        if (leftSide.size() >= 2 && leftSide.substr(leftSide.size() - 2) == "do")
        {
            enabled = true;
        }
        // check left side for don't instruction
        else if (leftSide.size() >= 5 && leftSide.substr(leftSide.size() - 5) == "don't")
        {
            enabled = false;
        }
        // check left side for multiply instruction
        else if (leftSide.size() >= 3 && leftSide.substr(leftSide.size() - 3) == "mul")
        {
            // now check right side for valid arguments
            std::vector<std::string> betweenBrackets = strSplit(rightSide, ')');
            std::vector<std::string> args = strSplit(betweenBrackets.at(0), ',');
            if (args.size() == 2 && argIsGood(args.at(0)) && argIsGood(args.at(1)))
            {
                int a0 = stoi(args.at(0));
                int a1 = stoi(args.at(1));
                int result = a0 * a1;
                if (enabled)
                    total += result;
                std::cout << a0 << " * " << a1 << " = " << result << std::endl;
            }
        }
    }
    std::cout << "Part 2: " << total << std::endl;

    return 0;
}