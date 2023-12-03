#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    std::cout << "AoC 2023 Day 2" << std::endl;
    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string line;
    unsigned int out = 0;
    bool failed = false;
    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ':');
        std::vector<std::string> gameInfo = strSplit(splitUp[0], ' ');
        int gameID = stoi(gameInfo[1]);
        splitUp = strSplit(splitUp[1], ';');
        for (int i = 0; i < splitUp.size(); i++)
        {
            std::vector<std::string> drawInfo = strSplit(splitUp[i], ',');
            for (int j = 0; j < drawInfo.size(); j++)
            {
                std::vector<std::string> colorInfo = strSplit(drawInfo[j], ' ');
                int num = stoi(colorInfo[1]);
                if (colorInfo[2] == "red" && num > 12)
                    failed = true;
                else if (colorInfo[2] == "green" && num > 13)
                    failed = true;
                else if (colorInfo[2] == "blue" && num > 14)
                    failed = true;
            }
        }
        if (failed)
            failed = false;
        else
            out += gameID;
    }
    std::cout << "Part 1: " << out << std::endl;
    file.close();

    // Part 2
    std::ifstream file2("input.txt");
    // std::ifstream file2("example.txt");
    out = 0;
    while (std::getline(file2, line))
    {
        int minRed = 0;
        int minGreen = 0;
        int minBlue = 0;
        std::vector<std::string> splitUp = strSplit(line, ':');
        splitUp = strSplit(splitUp[1], ';');
        for (int i = 0; i < splitUp.size(); i++)
        {
            std::vector<std::string> drawInfo = strSplit(splitUp[i], ',');
            for (int j = 0; j < drawInfo.size(); j++)
            {
                std::vector<std::string> colorInfo = strSplit(drawInfo[j], ' ');
                int num = stoi(colorInfo[1]);
                if (colorInfo[2] == "red" && num > minRed)
                    minRed = num;
                else if (colorInfo[2] == "green" && num > minGreen)
                    minGreen = num;
                else if (colorInfo[2] == "blue" && num > minBlue)
                    minBlue = num;
            }
        }
        out += minRed * minGreen * minBlue;
    }
    std::cout << "Part 2: " << out << std::endl;
    file2.close();
    return 0;
}
