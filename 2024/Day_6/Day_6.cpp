#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

inline bool isBlocked(const std::vector<std::string> &map, const int &x, const int &y)
{
    return map.at(y).at(x) == '#';
}

bool isOB(const std::vector<std::string> &map, const int &x, const int &y)
{
    const int height = map.size();
    const int width = map.at(0).length();
    if (x < 0 || x >= width || y < 0 || y >= height)
        return true;
    else
        return false;
}

void turnRight(char &dir)
{
    switch (dir)
    {
    case '^':
        dir = '>';
        break;

    case '>':
        dir = 'v';
        break;

    case 'v':
        dir = '<';
        break;

    case '<':
        dir = '^';
        break;
    }
}

void getNextPos(const char &dir, const int &x, const int &y, int &newX, int &newY)
{
    switch (dir)
    {
    case '^':
        newX = x;
        newY = y - 1;
        break;

    case '>':
        newX = x + 1;
        newY = y;
        break;

    case 'v':
        newX = x;
        newY = y + 1;
        break;

    case '<':
        newX = x - 1;
        newY = y;
        break;
    }
}

int main()
{
    std::cout << "AoC 2024 Day 6" << std::endl;
    std::string fileName = "Day_6/input.txt";
    // std::string fileName = "Day_6/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::vector<std::string> map;
    std::string line;
    int width = 0;
    int height = 0;
    int startX = 0;
    int startY = 0;
    char dir = '^';
    while (std::getline(file, line))
    {
        map.push_back(line);
        for (int i = 0; i < line.size(); i++)
            if (line.at(i) == '^')
            {
                startX = i;
                startY = height;
            }

        height++;
        width = line.size();
    }
    file.close();

    // Part 1
    std::vector<std::pair<int, int>> distPos;
    distPos.push_back({startX, startY});
    int x = startX;
    int y = startY;
    int newX;
    int newY;
    bool walking = true;
    while (walking)
    {
        getNextPos(dir, x, y, newX, newY);

        if (isOB(map, newX, newY))
            walking = false;

        else if (isBlocked(map, newX, newY))
            turnRight(dir);

        else
        {
            x = newX;
            y = newY;
            distPos.push_back({x, y});
        }
    }
    std::sort(distPos.begin(), distPos.end());
    distPos.erase(std::unique(distPos.begin(), distPos.end()), distPos.end());
    std::cout << "Part 1: " << distPos.size() << std::endl;

    // Part 2
    std::vector<std::string> originalMap = map;
    int numObstructions = 0;
    const int MAX_STEPS = 10000;
    for (int obstructionY = 0; obstructionY < height; obstructionY++)
    {
        for (int obstructionX = 0; obstructionX < width; obstructionX++)
        {
            if (!(obstructionX == startX && obstructionY == startY))
            {
                map = originalMap;
                // inset an obstruction into the map
                map.at(obstructionY).at(obstructionX) = '#';
                dir = '^';
                x = startX;
                y = startY;
                walking = true;
                int steps = 0;
                while (walking && steps < MAX_STEPS)
                {
                    getNextPos(dir, x, y, newX, newY);

                    if (isOB(map, newX, newY))
                        walking = false;

                    else if (isBlocked(map, newX, newY))
                        turnRight(dir);

                    else
                    {
                        x = newX;
                        y = newY;
                        distPos.push_back({x, y});
                    }
                    steps++;
                }
                if (steps == MAX_STEPS)
                    numObstructions++;
            }
        }
    }
    std::cout << "Part 2: " << numObstructions << std::endl;
    return 0;
}