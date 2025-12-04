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

int numBlocked(const std::vector<std::string> &diagram, int x, int y){
    int height = diagram.size();
    int width = diagram[0].size();
    int blocked = 0;
    if (y > 0          && x > 0         && diagram[y - 1][x - 1] == '@') blocked++;
    if (y > 0          &&                  diagram[y - 1][x    ] == '@') blocked++;
    if (y > 0          && x < width - 1 && diagram[y - 1][x + 1] == '@') blocked++;
    if (                  x > 0         && diagram[y    ][x - 1] == '@') blocked++;
    if (                  x < width - 1 && diagram[y    ][x + 1] == '@') blocked++;
    if (y < height - 1 && x > 0         && diagram[y + 1][x - 1] == '@') blocked++;
    if (y < height - 1 &&                  diagram[y + 1][x    ] == '@') blocked++;
    if (y < height - 1 && x < width - 1 && diagram[y + 1][x + 1] == '@') blocked++;
    return blocked;
}

int countRolls(const std::vector<std::string> &diagram){
    int numRolls = 0;
    for (int y = 0; y < diagram.size();  y++)
        for (int x = 0; x < diagram[0].size();  x++)
            if (diagram[y][x] == '@') numRolls++;
    
    return numRolls;
}

void printDiagram(const std::vector<std::string> &diagram){
    for (int y = 0; y < diagram.size();  y++)
        std::cout << diagram[y] << std::endl;
}

int main()
{
    std::cout << "AoC 2025 Day 4" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> diagram;
    while (std::getline(file, line))
        diagram.push_back(line);
    
    file.close();

    int width = line.size();
    int height = diagram.size();

    // Part 1
    tick();
    int sum = 0;
    for (int y = 0; y < height;  y++)
        for (int x = 0; x < width;  x++)
            if (diagram[y][x] == '@' && numBlocked(diagram, x, y) < 4) sum++;
           
    tock();
    std::cout << "Part 1: " << sum << std::endl;
    printMicroseconds();

    // Part 2
    tick();
    sum = 0;
    int numRolls = -1;
    int oldNumRolls = 0;
    while (numRolls != oldNumRolls){
        oldNumRolls = numRolls;
        numRolls = countRolls(diagram);
        // printDiagram(diagram);
        // std::cout << "numRolls: " << numRolls << std::endl;

        std::vector<std::string> newDiagram = diagram;
        for (int y = 0; y < height;  y++)
            for (int x = 0; x < width;  x++)
                if (diagram[y][x] == '@' && numBlocked(diagram, x, y) < 4){
                    newDiagram[y][x] = '.';
                    sum++;
                }
            
        diagram = newDiagram;
    }
    tock();
    std::cout << "Part 2: " << sum << std::endl;
    printMicroseconds();
    return 0;
}
