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

struct xyz {
    long long x;
    long long y;
    long long z;
};

struct dist {
    int a;
    int b;
    double distance;
    bool connected = false;
};

void sortDistances(std::vector<dist> &in){
    std::sort(in.begin(), in.end(), [](const dist& a, const dist& b) {
        return a.distance < b.distance;
    });
}

void sortcircuits(std::vector<std::vector<int>> &in){
    std::sort(in.begin(), in.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() > b.size();
    });
}

void makeCircuitUnique(std::vector<int> &in){
    std::sort(in.begin(), in.end()); 
    auto last_unique = std::unique(in.begin(), in.end());
    in.erase(last_unique, in.end());
}

void addCircuit(std::vector<std::vector<int>>&  circuits, dist d){
    std::vector<int> temp;
    std::vector<int> overlapsWith;
    for (int j = 0; j < circuits.size(); j++){
        temp = circuits[j];

        bool overlap = false;
        for (int k = 0; k < temp.size(); k++)
            if (d.a == temp[k] || d.b == temp[k]) overlap = true;
            
        if(overlap) overlapsWith.push_back(j);
    }

    if (overlapsWith.size() == 0)
        circuits.push_back({d.a, d.b});
    else {
        std::vector<int> newCircuit;
        newCircuit.push_back(d.a);
        newCircuit.push_back(d.b);
        for (int j = 0; j < overlapsWith.size(); j++){
            for (int k = 0; k < circuits[overlapsWith[j]].size(); k++) 
                newCircuit.push_back(circuits[overlapsWith[j]][k]);
        }

        std::sort(overlapsWith.begin(), overlapsWith.end());
        for (auto it = overlapsWith.rbegin(); it != overlapsWith.rend(); ++it)
            circuits.erase(circuits.begin() + *it);

        makeCircuitUnique(newCircuit);
        circuits.push_back(newCircuit);
    }
}

int main()
{
    std::cout << "AoC 2025 Day 8" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";
 
    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<xyz> coordinates;
    while(std::getline(file, line)){
        xyz temp;
        auto splitUp = strSplit(line, ',');
        temp.x = stoll(splitUp[0]);
        temp.y = stoll(splitUp[1]);
        temp.z = stoll(splitUp[2]);
        coordinates.push_back(temp);
    }
    file.close();
 
    // Part 1
    tick();
    std::vector<dist> distances;
    distances.reserve(pow(coordinates.size(), 2));
    for (int i = 0; i < coordinates.size()-1; i++){
        for (int j = i+1; j < coordinates.size(); j++){
            double distance = sqrt(pow(coordinates[i].x - coordinates[j].x, 2) + pow(coordinates[i].y - coordinates[j].y, 2) + pow(coordinates[i].z - coordinates[j].z, 2));
            distances.push_back({i,j,distance});
        }
    }
    sortDistances(distances);

    int numToMake = fileName == "example.txt" ? 10 : 1000;
    std::vector<std::vector<int>> circuits;
    std::vector<int> temp = {distances[0].a, distances[0].b};
    circuits.push_back(temp);
    int i;
    for (i = 1; i < numToMake; i++) addCircuit(circuits, distances[i]);
    sortcircuits(circuits);
    unsigned long long result = 1;
    for (int j = 0; j < 3; j++) result *= circuits[j].size();
    tock();
    std::cout << "Part 1: " << result << std::endl;
    printMicroseconds();
 
    // Part 2
    tick();
    while(circuits.front().size() != coordinates.size()){
        i++;
        addCircuit(circuits, distances[i]);
    }
    tock();
    std::cout << "Part 2: " << coordinates[distances[i].a].x * coordinates[distances[i].b].x << std::endl;
    printMicroseconds();
    return 0;
}
