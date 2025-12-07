#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
 
int main()
{
    std::cout << "AoC 2025 Day 7" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";
 
    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> map;
    while(std::getline(file, line)){
        map.push_back(line);
    }
    file.close();
 
    // Part 1
    tick();
    int numSplits = 0;
    for (int i = 0; i < map[0].size(); i++){
        if (map[0][i] == 'S'){
            map[0][i] = '|';
        }
    }
    
    for (int i = 1; i < map.size(); i ++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '^' && map[i-1][j] == '|'){
                if (j > 0) map[i][j-1] = '|';
                if (j < map[i].size()-1) map[i][j+1] = '|';
                numSplits ++;
            } 
            else if (map[i-1][j] == '|'){
                map[i][j] = '|';
            }
        }
    }
    tock();
    std::cout << "Part 1: " << numSplits << std::endl;
    printMicroseconds();
 
    // Part 2
    tick();
    std::vector<std::vector<unsigned long long>> newMap;
    newMap.reserve(map.size());

    std::vector<unsigned long long> temp;
    for (int j = 0; j < map[0].size(); j++){
        if (map[0][j] == '|') temp.push_back(1);
        else temp.push_back(0);
    }
    newMap.push_back(temp);

    for (int i = 1; i < map.size(); i++){
        temp.clear();
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '|'){
                if ((j > 0 && map[i][j-1] == '^') && (j < map[i].size()-1 && map[i][j+1] == '^'))
                    temp.push_back((newMap[i-1][j-1] + newMap[i-1][j]) + (newMap[i-1][j+1]));
                else if (j > 0 && map[i][j-1] == '^')
                    temp.push_back(newMap[i-1][j-1] + newMap[i-1][j]);
                else if (j < map[i].size()-1 && map[i][j+1] == '^')
                    temp.push_back(newMap[i-1][j+1] + newMap[i-1][j]);
                else
                    temp.push_back(newMap[i-1][j]);
            } else {
                temp.push_back(0);
            }
        }
        newMap.push_back(temp);
    }

    unsigned long long sum = 0;
    for (int j = 0; j < newMap.back().size(); j++){
        sum += newMap.back()[j];
    }
 
    tock();
    std::cout << "Part 2: " << sum << std::endl;
    printMicroseconds();
    return 0;
}
