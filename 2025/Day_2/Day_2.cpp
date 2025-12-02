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
    std::cout << "AoC 2025 Day 2" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    struct range {
        unsigned long long firstID;
        unsigned long long lastID;
    };

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    std::vector<std::string> inputList = strSplit(line, ',');
    std::vector<range> ranges;
    for (auto str:inputList)
    {
        range r;
        std::vector<std::string> IDs = strSplit(str, '-');
        r.firstID = stoull(IDs[0]);
        r.lastID = stoull(IDs[1]);
        ranges.push_back(r);
    }
    file.close();

    // Part 1
    unsigned long long sum = 0;
    for (auto r:ranges)
        for (unsigned long long i = r.firstID; i<r.lastID + 1; i++){
            std::string asString = std::to_string(i);
            if (asString.length()%2 == 0){
                std::string half1 = asString.substr(0, asString.length()/2);
                std::string half2 = asString.substr(asString.length()/2, asString.length()/2);
                if (half1 == half2) sum += i;
            }
        }
    
    std::cout << "Part 1: " << sum << std::endl;

    // Part 2
    sum = 0;
    for (auto r:ranges){
        std::vector<unsigned long long> invalids;
        for (unsigned long long i = r.firstID; i<r.lastID + 1; i++){
            std::string asString = std::to_string(i);
            for (int numSplits = 2; numSplits < asString.length()+1; numSplits ++){
                int splitLen = asString.length()/numSplits;
                if (asString.length()%numSplits == 0){
                    std::vector<std::string> parts;
                    for (int n = 0; n < numSplits; n ++)
                        parts.push_back(asString.substr(splitLen * n, splitLen));
                    
                    bool allMatch = true;
                    for (int n = 1; n < parts.size(); n++)
                        if (parts[n] != parts[0]){
                            allMatch = false;
                            break;
                        }
                    
                    if (allMatch) invalids.push_back(i);
                }
            }
        }
        std::sort(invalids.begin(), invalids.end()); 
        auto last_unique = std::unique(invalids.begin(), invalids.end());
        invalids.erase(last_unique, invalids.end());
        for (auto i:invalids) sum += i;
    }
    std::cout << "Part 2: " << sum << std::endl;
    return 0;
}
