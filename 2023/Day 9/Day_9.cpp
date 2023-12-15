#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> strSplit(std::string in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (int idx = 0; idx < in.length(); idx++)
    {
        char c = in.at(idx);
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

int nextValue(std::vector<int> in)
{
    std::vector<int> differences;
    for (int j = 0; j < in.size() - 1; j++)
    {
        int temp = in[j + 1] - in[j];
        differences.push_back(temp);
    }

    if (differences.size() == 1)
        return 0;
    else
        return in.back() + nextValue(differences);
}

int prevValue(std::vector<int> in)
{
    std::vector<int> differences;
    for (int j = 0; j < in.size() - 1; j++)
    {
        int temp = in[j + 1] - in[j];
        differences.push_back(temp);
    }

    if (differences.size() == 1)
        return 0;
    else
        return in.front() - prevValue(differences);
}

int main()
{
    std::cout << "AoC 2023 Day 9" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1 & 2
    std::ifstream file(fileName);
    std::string line;
    int out = 0;
    int out2 = 0;

    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ' ');
        std::vector<int> history;
        for (int i = 0; i < splitUp.size(); i++)
            history.push_back(stoi(splitUp[i]));

        out += nextValue(history);
        out2 += prevValue(history);
    }
    file.close();

    std::cout << "Part 1: " << out << std::endl;
    std::cout << "Part 2: " << out2 << std::endl;
    return 0;
}
