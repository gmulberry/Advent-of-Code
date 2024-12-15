#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> strSplit(const std::string &in, const char &delimiter)
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

void printMap(const std::vector<std::string> &map)
{
    for (int y = 0; y < map.size(); y++)
    {
        std::cout << map.at(y) << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "AoC 2024 Day 15" << std::endl;
    std::string fileName = "Day_15/input.txt";
    // std::string fileName = "Day_15/example.txt";
    //  std::string fileName = "Day_15/example1.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> map;
    std::string instructions;
    bool readingMap = true;
    while (std::getline(file, line))
    {
        if (line == "")
        {
            readingMap = false;
        }
        else if (readingMap)
        {
            map.push_back(line);
        }
        else
        {
            instructions += line;
        }
    }
    file.close();

    printMap(map);
    int height = map.size();
    int width = map.at(0).length();

    // get robot position
    int x, y;
    for (int yy = 0; yy < height; yy++)
        for (int xx = 0; xx < width; xx++)
        {
            char c = map.at(yy).at(xx);
            if (c == '@')
            {
                x = xx;
                y = yy;
                break;
            }
        }

    for (int i = 0; i < instructions.length(); i++)
    {
        char inst = instructions.at(i);
        // std::cout << "Move " << inst << ":" << std::endl;
        char inFront;
        switch (inst)
        {
        case '<':
            inFront = map.at(y).at(x - 1);
            if (inFront == '.')
            {
                map.at(y).at(x) = '.';
                map.at(y).at(x - 1) = '@';
                x = x - 1;
            }
            else if (inFront == 'O')
            {
                bool allStones = true;
                int testX = x - 2;
                while (allStones)
                {
                    if (map.at(y).at(testX) != 'O')
                    {
                        allStones = false;
                        break;
                    }
                    testX--;
                }
                if (map.at(y).at(testX) == '.')
                {
                    map.at(y).at(x) = '.';
                    map.at(y).at(x - 1) = '@';
                    x = x - 1;
                    for (; testX < x; testX++)
                        map.at(y).at(testX) = 'O';
                }
            }
            break;
        case '>':
            inFront = map.at(y).at(x + 1);
            if (inFront == '.')
            {
                map.at(y).at(x) = '.';
                map.at(y).at(x + 1) = '@';
                x = x + 1;
            }
            else if (inFront == 'O')
            {
                bool allStones = true;
                int testX = x + 2;
                while (allStones)
                {
                    if (map.at(y).at(testX) != 'O')
                    {
                        allStones = false;
                        break;
                    }
                    testX++;
                }
                if (map.at(y).at(testX) == '.')
                {
                    map.at(y).at(x) = '.';
                    map.at(y).at(x + 1) = '@';
                    x = x + 1;
                    for (; testX > x; testX--)
                        map.at(y).at(testX) = 'O';
                }
            }
            break;
        case 'v':
            inFront = map.at(y + 1).at(x);
            if (inFront == '.')
            {
                map.at(y).at(x) = '.';
                map.at(y + 1).at(x) = '@';
                y = y + 1;
            }
            else if (inFront == 'O')
            {
                bool allStones = true;
                int testY = y + 2;
                while (allStones)
                {
                    if (map.at(testY).at(x) != 'O')
                    {
                        allStones = false;
                        break;
                    }
                    testY++;
                }
                if (map.at(testY).at(x) == '.')
                {
                    map.at(y).at(x) = '.';
                    map.at(y + 1).at(x) = '@';
                    y = y + 1;
                    for (; testY > y; testY--)
                        map.at(testY).at(x) = 'O';
                }
            }
            break;
        case '^':
            inFront = map.at(y - 1).at(x);
            if (inFront == '.')
            {
                map.at(y).at(x) = '.';
                map.at(y - 1).at(x) = '@';
                y = y - 1;
            }
            else if (inFront == 'O')
            {
                bool allStones = true;
                int testY = y - 2;
                while (allStones)
                {
                    if (map.at(testY).at(x) != 'O')
                    {
                        allStones = false;
                        break;
                    }
                    testY--;
                }
                if (map.at(testY).at(x) == '.')
                {
                    map.at(y).at(x) = '.';
                    map.at(y - 1).at(x) = '@';
                    y = y - 1;
                    for (; testY < y; testY++)
                        map.at(testY).at(x) = 'O';
                }
            }
            break;
        }
        // printMap(map);
    }

    int GPS = 0;
    for (int yy = 0; yy < height; yy++)
        for (int xx = 0; xx < width; xx++)
            if (map.at(yy).at(xx) == 'O')
                GPS += yy * 100 + xx;

    // Part 1
    std::cout << "Part 1: " << GPS << std::endl;

    // Part 2
    std::cout << "Part 2: " << "Not yet implemented!" << std::endl;
    return 0;
}