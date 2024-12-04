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

bool searchForward(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    if(linePos + 4 <= wordSearch.at(1).size() && wordSearch.at(lineNum).substr(linePos, 4) == "XMAS") return true;
    else return false;
}

bool searchBackward(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    if(linePos - 3 >= 0 && wordSearch.at(lineNum).substr(linePos - 3, 4) == "SAMX") return true;
    else return false;
}

bool searchDownward(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    if(lineNum + 4 <= wordSearch.size()){
        std::string testString = "";
        for (int i = lineNum; i < lineNum + 4; i++)
            testString += wordSearch.at(i).at(linePos);
        
        if (testString == "XMAS") return true;
        else return false;
    } 
    else return false;
}

bool searchUpward(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    if(lineNum - 3 >= 0){
        std::string testString = "";
        for (int i = lineNum; i >= lineNum - 3; i--)
            testString += wordSearch.at(i).at(linePos);
        
        if (testString == "XMAS") return true;
        else return false;
    } 
    else return false;
}

int searchDiagonal(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    const int height = wordSearch.size();
    const int width = wordSearch.at(1).size();
    int count = 0;

    // search down and right
    if(lineNum + 4 <= height && linePos + 4 <= width){
        std::string testString = "";
        for (int i = 0; i < 4; i++)
            testString += wordSearch.at(lineNum + i).at(linePos + i);
        
        if (testString == "XMAS") count ++;
    } 
    
    // search up and right
    if(lineNum - 3 >= 0 && linePos + 4 <= width){
        std::string testString = "";
        for (int i = 0; i < 4; i++)
            testString += wordSearch.at(lineNum - i).at(linePos + i);
        
        if (testString == "XMAS") count ++;
    } 

    // search down and left
    if(lineNum + 4 <= height && linePos - 3 >= 0){
        std::string testString = "";
        for (int i = 0; i < 4; i++)
            testString += wordSearch.at(lineNum + i).at(linePos - i);
        
        if (testString == "XMAS") count ++;
    } 
    
    // search up and left
    if(lineNum - 3 >= 0 && linePos - 3 >= 0){
        std::string testString = "";
        for (int i = 0; i < 4; i++)
            testString += wordSearch.at(lineNum - i).at(linePos - i);
        
        if (testString == "XMAS") count ++;
    } 
    
    return count;
}

bool searchX_MAS(const int &lineNum, const int &linePos, const std::vector<std::string> &wordSearch){
    const int height = wordSearch.size();
    const int width = wordSearch.at(1).size();
    if(wordSearch.at(lineNum).at(linePos) == 'A' && lineNum > 0 && lineNum < height - 1 && linePos > 0 && linePos < width - 1){
        const char c_al = wordSearch.at(lineNum - 1).at(linePos - 1);
        const char c_ar = wordSearch.at(lineNum - 1).at(linePos + 1);
        const char c_bl = wordSearch.at(lineNum + 1).at(linePos - 1);
        const char c_br = wordSearch.at(lineNum + 1).at(linePos + 1);
        
        if (!((c_al == 'M' && c_br == 'S') || (c_al == 'S' && c_br == 'M'))) return false;
        if (!((c_ar == 'M' && c_bl == 'S') || (c_ar == 'S' && c_bl == 'M'))) return false;
        return true;
    } 
    else return false;
}

int main()
{
    std::cout << "AoC 2024 Day 4" << std::endl;
    std::string fileName = "Day_4/input.txt";
    //std::string fileName = "Day_4/example.txt";

    // read in the file
    std::ifstream file(fileName);

    std::string line;
    std::vector<std::string> wordSearch;
    while (std::getline(file, line))
        wordSearch.push_back(line);

    file.close();

    const int height = wordSearch.size();
    const int width = wordSearch.at(1).size();

    // Part 1
    int total = 0;
    for (int lineNum = 0; lineNum < height; lineNum++)
        for (int linePos = 0; linePos < width; linePos++){
            total += searchForward(lineNum, linePos, wordSearch);
            total += searchBackward(lineNum, linePos, wordSearch);
            total += searchDownward(lineNum, linePos, wordSearch);
            total += searchUpward(lineNum, linePos, wordSearch);
            total += searchDiagonal(lineNum, linePos, wordSearch);
        }

    std::cout << "Part 1: " << total << std::endl;

    // Part 2
    total = 0;
    for (int lineNum = 0; lineNum < height; lineNum++)
        for (int linePos = 0; linePos < width; linePos++)
            total += searchX_MAS(lineNum, linePos, wordSearch);

    std::cout << "Part 2: " << total << std::endl;

    return 0;
}