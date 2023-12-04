#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::vector<std::string> strSplit(std::string in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    int idx = 0;
    while (idx < in.length())
    {
        char c = in.at(idx);
        if (c == delimiter)
        {
            idx++;
            out.push_back(temp);
            temp = "";
        }
        else
        {
            temp = temp + c;
            idx++;
        }
    }
    out.push_back(temp);
    return out;
}

int main()
{
    std::cout << "AoC 2023 Day 4" << std::endl;
    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string lineIn;
    unsigned int out = 0;
    std::vector<int> numWinners;

    while (std::getline(file, lineIn))
    {
        std::string line;
        line = line + lineIn.at(0);
        for (int i = 1; i < lineIn.length(); i++)
        {
            char c = lineIn.at(i);
            if (!(c == ' ' && line.back() == ' '))
                line += c;
        }
        std::vector<std::string> splitUp = strSplit(line, '|');
        std::vector<std::string> winNumStrings = strSplit(splitUp[0], ' ');
        std::vector<int> winNums;
        for (int i = 2; i < winNumStrings.size() - 1; i++)
            winNums.push_back(stoi(winNumStrings.at(i)));

        std::vector<std::string> cardNumStrings = strSplit(splitUp[1], ' ');
        std::vector<int> cardNums;
        for (int i = 1; i < cardNumStrings.size(); i++)
            cardNums.push_back(stoi(cardNumStrings.at(i)));

        int numWinning = 0;
        for (int i = 0; i < winNums.size(); i++)
            for (int j = 0; j < cardNums.size(); j++)
                if (winNums[i] == cardNums[j])
                    numWinning++;

        out += pow(2, numWinning - 1);
        numWinners.push_back(numWinning);
    }
    file.close();
    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    out = 0;
    std::vector<int> numCards;
    for (int i = 0; i < numWinners.size(); i++)
        numCards.push_back(1);

    for (int i = 0; i < numWinners.size(); i++)
    {
        for (int j = 1; j <= numWinners[i]; j++)
            if (i + j < numCards.size())
                numCards[i + j] += numCards[i];

        out += numCards[i];
    }
    std::cout << "Part 2: " << out << std::endl;
}
