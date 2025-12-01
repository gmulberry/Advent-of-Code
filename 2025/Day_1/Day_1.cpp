#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::cout << "AoC 2025 Day 1" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<int> rotations;
    while (std::getline(file, line))
    {
        int rotation = 0;
        rotation = std::stoi(line.substr(1));
        if (line.at(0) == 'L') rotation *= -1;
        rotations.push_back(rotation);
    }
    file.close();

    // Part 1
    int sum = 0;
    int pos = 50;
    for (auto rotation:rotations){
        pos = (pos + rotation) % 100;
        if (pos == 0) sum ++;
    }
    std::cout << "Part 1: " << sum << std::endl;

    // Part 2
    sum = 0;
    pos = 50;
    for (auto rotation:rotations){
        int dir = rotation < 0 ? -1 : 1;
        for (int i = 0; i < abs(rotation); i++){
            pos = (pos + dir) % 100;
            if (pos == 0) sum ++;
        }
    }
    std::cout << "Part 2: " << sum << std::endl;
    return 0;
}
