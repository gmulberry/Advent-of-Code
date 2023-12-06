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

int main()
{
    std::cout << "AoC 2023 Day 6" << std::endl;
    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string lineIn;
    std::vector<int> times, dists;
    long time;
    long dist;

    while (std::getline(file, lineIn))
    {
        std::string line;
        std::string lineNoSpaces;
        line = line + lineIn.at(0);
        lineNoSpaces = lineNoSpaces + lineIn.at(0);
        for (int i = 1; i < lineIn.length(); i++)
        {
            char c = lineIn.at(i);
            if (!(c == ' ' && line.back() == ' '))
                line += c;
            if (!(c == ' '))
                lineNoSpaces += c;
        }
        std::vector<std::string> splitUp = strSplit(line, ' ');
        std::vector<std::string> splitUp2 = strSplit(lineNoSpaces, ':');

        if (splitUp[0] == "Time:")
        {
            for (int i = 1; i < splitUp.size(); i++)
                times.push_back(stol(splitUp[i]));
            time = stol(splitUp2[1]);
        }

        if (splitUp[0] == "Distance:")
        {
            for (int i = 1; i < splitUp.size(); i++)
                dists.push_back(stol(splitUp[i]));
            dist = stol(splitUp2[1]);
        }
    }
    file.close();

    int out = 1;
    for (int i = 0; i < times.size(); i++)
    {
        int numWays2Win = 0;
        for (int hold = 0; hold <= times[i]; hold++)
            if (hold * (times[i] - hold) > dists[i])
                numWays2Win++;

        out = out * numWays2Win;
    }
    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    long numWays2Win = 0;
    for (long hold = 0; hold <= time; hold++)
        if (hold * (time - hold) > dist)
            numWays2Win++;
    std::cout << "Part 2: " << numWays2Win << std::endl;
    return 0;
}