#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> strSplit(std::string in, char delimiter)
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

// returns true if the report is safe
bool isSafe(std::vector<int> report)
{
    bool safe = false;
    bool decreasing = true;
    bool increasing = true;
    bool differs = true;
    int prevLevel = report.at(0);
    for (int i = 1; i < report.size(); i++)
    {
        int level = report.at(i);
        int difference = level - prevLevel;
        int magnitude = difference > 0 ? difference : -difference;
        prevLevel = level;

        if (difference > 0)
            decreasing = false;
        if (difference < 0)
            increasing = false;
        if (magnitude < 1 || magnitude > 3)
            differs = false;
    }
    if (differs && (decreasing || increasing))
        safe = true;
    return safe;
}

int main()
{
    std::cout << "AoC 2024 Day 2" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::vector<int>> reports;
    while (std::getline(file, line))
    {
        std::vector<std::string> lineElements = strSplit(line, ' ');
        std::vector<int> report;
        for (std::string el : lineElements)
        {
            report.push_back(stoi(el));
        }
        reports.push_back(report);
    }
    file.close();

    // Part 1
    int safe = 0;
    for (std::vector<int> report : reports)
        safe += isSafe(report);

    std::cout << "Part 1: " << safe << std::endl;

    // Part 2
    safe = 0;
    for (std::vector<int> report : reports)
    {
        if (isSafe(report))
        {
            safe++;
            continue;
        }
        else
        {
            for (int i = 0; i < report.size(); i++)
            {
                std::vector<int> reportDampened = report;
                reportDampened.erase(reportDampened.begin() + i);
                if (isSafe(reportDampened))
                {
                    safe++;
                    break;
                }
            }
        }
    }
    std::cout << "Part 2: " << safe << std::endl;

    return 0;
}