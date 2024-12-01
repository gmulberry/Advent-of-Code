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

int main()
{
    std::cout << "AoC 2024 Day 1" << std::endl;
    std::string fileName = "input.txt";
    //std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<int> leftCol;
    std::vector<int> rightCol;
    while (std::getline(file, line))
    {
        std::string tempLine = "";
        bool gotSpace = false;
        for (int i = 0; i < line.length(); i ++){
            char c = line.at(i);
            if (gotSpace == false){
                tempLine += c;
                if (c == ' ') gotSpace = true;
            } else {
                if (c != ' ') tempLine += c;
            }
        }
        std::vector<std::string> lineElements = strSplit(tempLine, ' ');
        leftCol.push_back(stoi(lineElements[0]));
        rightCol.push_back(stoi(lineElements[1]));
    }
    file.close();

    // Part 1
    std::sort(leftCol.begin(), leftCol.end());
    std::sort(rightCol.begin(), rightCol.end());
    int sum = 0;
    for (int i = 0; i < (int)leftCol.size(); i ++){
        int temp = leftCol.at(i) - rightCol.at(i);
        if (temp < 0) sum += -temp;
        else sum += temp;
    }
    std::cout << "Part 1: " << sum << std::endl;
    
    // Part 2
    sum = 0;
    for (int i = 0; i < leftCol.size(); i ++){
        int lookingFor = leftCol.at(i);
        int count = 0;
        for (int j = 0; j < rightCol.size(); j ++)
            if (rightCol.at(j) == lookingFor) count++;
        
        int similarityScore = count * lookingFor;
        sum += similarityScore;
    }
    std::cout << "Part 2: " << sum << std::endl;
    return 0;
}

