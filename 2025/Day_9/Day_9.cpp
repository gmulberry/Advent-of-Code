#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
 
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

std::vector<std::string> strSplit(const std::string &in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (char c : in)
    {
        if (c == delimiter)
        {
            if (temp != "") out.push_back(temp);
            temp = "";
        }
        else
            temp = temp + c;
    }
    if (temp != "") out.push_back(temp);
    return out;
}

struct point {
    unsigned long long x;
    unsigned long long y;
};

int main()
{
    std::cout << "AoC 2025 Day 9" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";
 
    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<point> redTiles;
    while(std::getline(file, line)){
        point temp;
        auto splitUp = strSplit(line, ',');
        temp.x = stoull(splitUp[0]);
        temp.y = stoull(splitUp[1]);
        redTiles.push_back(temp);
    }
    file.close();
 
    // Part 1
    tick();
    unsigned long long largest = 0;
    for (int i = 0; i < redTiles.size()-1; i++){
        for (int j = i+1; j < redTiles.size(); j++){
            auto &a = redTiles[i];
            auto &b = redTiles[j];
            unsigned long long dx = a.x > b.x ? a.x - b.x + 1 : b.x - a.x + 1;
            unsigned long long dy = a.y > b.y ? a.y - b.y + 1 : b.y - a.y + 1;
            unsigned long long area = dx * dy;
            if (area > largest) largest = area;
        }
    }
    tock();
    std::cout << "Part 1: " << largest << std::endl;
    printMicroseconds(); 

    // Part 2
    tick();
    tock();
    std::cout << "Part 2: " << "Not yet solved!" << std::endl;
    printMicroseconds();
    return 0;
}
