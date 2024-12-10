#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printMap(const std::vector<std::vector<int>> &map){
    for (int y = 0; y < map.size(); y++){
        for (int x = 0; x < map.at(0).size(); x++)
        {
            int height = map[y][x];
            if (height == -1) std::cout << '.';
            else std::cout << height;
        }
        std::cout<<std::endl;
    }
}

int main()
{
    std::cout << "AoC 2024 Day 10" << std::endl;
    std::string fileName = "Day_10/input.txt";
    //std::string fileName = "Day_10/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::vector<int>> map;
    int numLines = 0;
    int width = 0;
    while (std::getline(file, line))
    {
        std::vector<int> thisLine;
        for (char c : line){
            thisLine.push_back(c - '0');
        }
        map.push_back(thisLine);
        numLines++;
        width = line.length();
    }
    file.close();

    // Part 1
    int totalScore = 0;
    for (int y = 0; y < numLines; y++)
        for (int x = 0; x < width; x++)
        {
            int height = map[y][x];
            if (height == 0)
            {
                std::vector<std::vector<int>> testMap;
                std::vector<int> emptyLine;
                for (int xx = 0; xx < width; xx++)
                    emptyLine.push_back(-1);

                for (int yy = 0; yy < numLines; yy++)
                    testMap.push_back(emptyLine);

                testMap[y][x] = 0;
                //printMap(testMap);
                //std::cout << std::endl;

                for (int level = 1; level < 10; level++)
                {
                    for (int yy = 0; yy < numLines; yy++)
                        for (int xx = 0; xx < width; xx++)
                            if (map[yy][xx] == level && ((xx - 1 >= 0 && testMap[yy][xx - 1] == level - 1) ||
                                                         (xx + 1 < width && testMap[yy][xx + 1] == level - 1) ||
                                                         (yy - 1 >= 0 && testMap[yy - 1][xx] == level - 1) ||
                                                         (yy + 1 < numLines && testMap[yy + 1][xx] == level - 1)))
                                testMap[yy][xx] = level;
                }

                int score = 0;
                for (int yy = 0; yy < numLines; yy++)
                    for (int xx = 0; xx < width; xx++)
                        if (testMap[yy][xx] == 9) score++;

                //std::cout << "x=" << x<< " y="<< y<< " score= " << score<< std::endl;
                totalScore += score;
            }
        }

    std::cout << "Part 1: " << totalScore << std::endl;
    return 0;
}