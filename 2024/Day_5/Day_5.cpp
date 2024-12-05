#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
    std::cout << "AoC 2024 Day 5" << std::endl;
    std::string fileName = "Day_5/input.txt";
    //std::string fileName = "Day_5/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::pair<int,int>> rules;
    std::vector<std::vector<int>> updates;
    bool readingRules = true;
    while (std::getline(file, line)){
        if (readingRules){
            if (line != ""){
                std::vector<std::string> splitUp = strSplit(line, '|');
                std::pair<int, int> rule(stoi(splitUp[0]), stoi(splitUp[1]));
                rules.push_back(rule);
            }
            else readingRules = false;
        } else {
            std::vector<std::string> splitUp = strSplit(line, ',');
            std::vector<int> update;
            for (auto pageNum : splitUp){
                update.push_back(stoi(pageNum));
            }
            updates.push_back(update);

        }
    }
    file.close();

    // Part 1
    int total = 0;
    for (auto update : updates){
        bool ordered = true;
        for (auto rule : rules){
            const int firstPage = rule.first;
            const int secondPage = rule.second;
            auto firstPageLoc = std::find(update.begin(), update.end(), firstPage);
            auto secondPageLoc = std::find(update.begin(), update.end(), secondPage);
            if(firstPageLoc != update.end() && firstPageLoc != update.end() && firstPageLoc > secondPageLoc){
                ordered = false;
                break;
            }
        }
        if (ordered) total += update.at((int)(update.size()/2));
    }
    std::cout << "Part 1: " << total << std::endl;

    // Part 2
    total = 0;
    for (int updateNumber = 0; updateNumber < updates.size() ; updateNumber++){
        std::vector<int> update = updates.at(updateNumber);
        bool ordered = false;
        bool flagged = false;
        while (ordered == false){
            ordered = true;
            for (auto rule : rules){
                update = updates.at(updateNumber);
                const int firstPage = rule.first;
                const int secondPage = rule.second;
                auto firstPageLoc = std::find(update.begin(), update.end(), firstPage);
                auto secondPageLoc = std::find(update.begin(), update.end(), secondPage);
                if(firstPageLoc != update.end() && firstPageLoc != update.end() && firstPageLoc > secondPageLoc){
                    ordered = false;
                    flagged = true;
                    std::vector<int> newOrder = update;
                    int first = std::distance(update.begin(), firstPageLoc);
                    int second = std::distance(update.begin(), secondPageLoc);
                    newOrder.at(first) = secondPage;
                    newOrder.at(second) = firstPage;
                    updates.at(updateNumber) = newOrder;
                }   
            }
        }
        
        if (flagged == true){
            update = updates.at(updateNumber);
            total += update.at((int)(update.size()/2));
        }
    }
    std::cout << "Part 2: " << total << std::endl;
    return 0;
}