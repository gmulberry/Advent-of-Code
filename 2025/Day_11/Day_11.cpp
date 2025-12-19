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

std::vector<std::string> strSplit(const std::string &in, char delimiter)
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

struct device {
    std::string name;
    std::vector<std::string> connections;
};

int findIdx(const std::vector<device> &devices, std::string name){
    for (int idx = 0; idx < devices.size(); idx++)
        if (devices[idx].name == name) return idx;

    std::cout << "could not find " << name << std::endl;
    return -1;
}

int nextLayer(std::vector<device> &devices, int posIdx, const std::string dest){
    int sum = 0;
    for (std::string nextConnection:devices[posIdx].connections){
        if (nextConnection == dest) sum++;
        else sum += nextLayer(devices, findIdx(devices, nextConnection), dest);
    }
    return sum;
}

int main()
{
    std::cout << "AoC 2025 Day 11" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";
    // std::string fileName = "example2.txt";
 
    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<device> devices;
    while(std::getline(file, line)){
        device d;
        auto splitUp = strSplit(line, ' ');
        
        d.name = splitUp[0].substr(0, splitUp[0].size()-1);

        for (int i = 1; i < splitUp.size(); i++)
            d.connections.push_back(splitUp[i]);

        devices.push_back(d);
    }
    file.close();

    // Part 1
    tick();
    int sum = nextLayer(devices, findIdx(devices, "you"), "out");
    tock();
    std::cout << "Part 1: " << sum << std::endl;
    printMicroseconds(); 

    // Part 2
    tick();
    tock();
    std::cout << "Part 2: not yet solved!" << std::endl;
    printMicroseconds();
    return 0;
}
