#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

std::chrono::high_resolution_clock::time_point tickTime;
std::chrono::high_resolution_clock::time_point tockTime;

void static inline tick(){
    tickTime = std::chrono::high_resolution_clock::now();
}

void static inline tock(){
    tockTime = std::chrono::high_resolution_clock::now();
}

void static inline printMicroseconds() {
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tockTime - tickTime).count() << " us" << std::endl;
}

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

struct range {
    unsigned long long firstID;
    unsigned long long lastID;
};

void printRanges(const std::vector<range> &in){
    for (auto r:in){
        std::cout << r.firstID << "-" << r.lastID << std::endl;
    }
}

void sortRanges(std::vector<range> &in){
    std::sort(in.begin(), in.end(), [](const range& a, const range& b) {
        return a.firstID < b.firstID;
    });
}

unsigned long long sumRanges(std::vector<range> &in){
    unsigned long long sum = 0;
    for (auto r:in){
        sum += 1 + r.lastID - r.firstID;
    }
    return sum;
}

int main()
{
    std::cout << "AoC 2025 Day 5" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<range> ranges;
    std::vector<unsigned long long> availableIDs;
    bool doneWithRanges = false;
    while (std::getline(file, line))
    {
        if (!doneWithRanges && line != ""){
            range r;
            std::vector<std::string> IDs = strSplit(line, '-');
            r.firstID = std::min(stoull(IDs[0]), stoull(IDs[1]));
            r.lastID =  std::max(stoull(IDs[0]), stoull(IDs[1]));
            ranges.push_back(r);
        }

        if (line == "") doneWithRanges = true;

        if (doneWithRanges && line != ""){
            availableIDs.push_back(stoull(line));
        }
    }
    file.close();

    // Part 1
    tick();
    unsigned long long sum = 0;
    for (auto ID:availableIDs)
        for (auto range:ranges)
            if (ID >= range.firstID && ID <= range.lastID){
                sum++;
                break;
            }
        
    tock();
    std::cout << "Part 1: " << sum << std::endl;
    printMicroseconds();

    // Part 2
    tick();
    sortRanges(ranges);
    std::vector<range> newRanges;
    newRanges.reserve(ranges.size());
    newRanges.push_back(ranges[0]);
    for (int i = 1; i < ranges.size(); ++i) {
        if ((ranges[i].firstID <= newRanges.back().lastID && ranges[i].lastID >= newRanges.back().firstID)) {
            newRanges.back().firstID = std::min(newRanges.back().firstID, ranges[i].firstID);
            newRanges.back().lastID  = std::max(newRanges.back().lastID,  ranges[i].lastID);
        } else {
            newRanges.push_back(ranges[i]);
        }
    }
    tock();
    std::cout << "Part 2: " << sumRanges(newRanges) << std::endl;
    printMicroseconds();
    return 0;
}
