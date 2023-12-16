#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct tile
{
    int x;
    int y;
    char type;
    bool lightNorth;
    bool lightEast;
    bool lightSouth;
    bool lightWest;
    bool isEnergized;
};

std::vector<std::string> strSplit(std::string in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (int idx = 0; idx < in.length(); idx++)
    {
        char c = in.at(idx);
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

int getNumEnergized(const std::vector<tile> &map)
{
    int count = 0;
    for (size_t i = 0; i < map.size(); i++)
        if (map[i].isEnergized)
            count++;

    return count;
}

void updateState(const int &x, const int &y, std::vector<tile> &map, const bool &litFromNorth,
                 const bool &litFromSouth, const bool &litFromEast, const bool &litFromWest,
                 const int &width, const int &height)
{
    if (litFromNorth || litFromSouth || litFromEast || litFromWest)
    {
        map[(y)*width + (x)].isEnergized = true;

        if (map[(y)*width + (x)].type == '.')
        {
            if (litFromNorth)
                map[(y)*width + (x)].lightSouth = true;
            if (litFromSouth)
                map[(y)*width + (x)].lightNorth = true;
            if (litFromWest)
                map[(y)*width + (x)].lightEast = true;
            if (litFromEast)
                map[(y)*width + (x)].lightWest = true;
        }
        else if (map[(y)*width + (x)].type == '-')
        {
            if (litFromNorth)
            {
                map[(y)*width + (x)].lightEast = true;
                map[(y)*width + (x)].lightWest = true;
            }

            if (litFromSouth)
            {
                map[(y)*width + (x)].lightEast = true;
                map[(y)*width + (x)].lightWest = true;
            }
            if (litFromWest)
                map[(y)*width + (x)].lightEast = true;
            if (litFromEast)
                map[(y)*width + (x)].lightWest = true;
        }
        else if (map[(y)*width + (x)].type == '|')
        {
            if (litFromNorth)
                map[(y)*width + (x)].lightSouth = true;
            if (litFromSouth)
                map[(y)*width + (x)].lightNorth = true;
            if (litFromWest)
            {
                map[(y)*width + (x)].lightNorth = true;
                map[(y)*width + (x)].lightSouth = true;
            }
            if (litFromEast)
            {
                map[(y)*width + (x)].lightNorth = true;
                map[(y)*width + (x)].lightSouth = true;
            }
        }
        else if (map[(y)*width + (x)].type == '/')
        {
            if (litFromNorth)
                map[(y)*width + (x)].lightWest = true;
            if (litFromSouth)
                map[(y)*width + (x)].lightEast = true;
            if (litFromWest)
                map[(y)*width + (x)].lightNorth = true;
            if (litFromEast)
                map[(y)*width + (x)].lightSouth = true;
        }
        else if (map[(y)*width + (x)].type == '\\')
        {
            if (litFromNorth)
                map[(y)*width + (x)].lightEast = true;
            if (litFromSouth)
                map[(y)*width + (x)].lightWest = true;
            if (litFromWest)
                map[(y)*width + (x)].lightSouth = true;
            if (litFromEast)
                map[(y)*width + (x)].lightNorth = true;
        }
    }
}

int run(const int &height, const int &width, const std::string &tiles, const int &startingX, const int &startingY,
        const bool &litFromNorth, const bool &litFromSouth, const bool &litFromEast, const bool &litFromWest)
{
    std::vector<tile> map;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            tile t;
            t.x = x;
            t.y = y;
            t.type = tiles[y * width + x];
            t.lightNorth = false;
            t.lightEast = false;
            t.lightSouth = false;
            t.lightWest = false;
            t.isEnergized = false;
            map.push_back(t);
        }
    map[startingY * width + startingX].isEnergized = true;

    updateState(startingX, startingY, map, litFromNorth, litFromSouth, litFromEast, litFromWest, width, height);

    int prevNumEnergized = 0;
    int numEnergized = 0;
    int counter = 0;
    while (counter < 10)
    {
        if (prevNumEnergized == numEnergized)
            counter++;
        else
            counter = 0;

        prevNumEnergized = numEnergized;

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                bool litFromNorth = y > 0 && map[(y - 1) * width + (x)].lightSouth;
                bool litFromSouth = y < height - 1 && map[(y + 1) * width + (x)].lightNorth;
                bool litFromEast = x < width - 1 && map[(y)*width + (x + 1)].lightWest;
                bool litFromWest = x > 0 && map[(y)*width + (x - 1)].lightEast;

                updateState(x, y, map, litFromNorth, litFromSouth, litFromEast, litFromWest, width, height);
            }

        numEnergized = getNumEnergized(map);
    }
    return numEnergized;
}

int main()
{
    std::cout << "AoC 2023 Day 16" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::string tiles;
    int height = 0;
    while (std::getline(file, line))
    {
        tiles += line;
        height++;
    }
    file.close();
    int width = line.length();

    int startingY = 0;
    int startingX = 0;
    int numEnergized = 0;
    int maxNumEnergized = 0;

    bool litFromNorth = false;
    bool litFromSouth = false;
    bool litFromEast = false;
    bool litFromWest = false;

    litFromWest = true;
    startingX = 0;
    for (startingY = 0; startingY < height; startingY++)
    {
        numEnergized = run(height, width, tiles, startingX, startingY, litFromNorth, litFromSouth, litFromEast, litFromWest);
        if (startingX == 0 && startingY == 0 && litFromWest == true)
            std::cout << "Part 1: " << numEnergized << std::endl;
        if (numEnergized > maxNumEnergized)
            maxNumEnergized = numEnergized;
    }

    litFromNorth = false;
    litFromSouth = false;
    litFromEast = false;
    litFromWest = false;

    litFromEast = true;
    startingX = width - 1;
    for (startingY = 0; startingY < height; startingY++)
    {
        numEnergized = run(height, width, tiles, startingX, startingY, litFromNorth, litFromSouth, litFromEast, litFromWest);
        if (startingX == 0 && startingY == 0 && litFromWest == true)
            std::cout << "Part 1: " << numEnergized << std::endl;
        if (numEnergized > maxNumEnergized)
            maxNumEnergized = numEnergized;
    }

    litFromNorth = false;
    litFromSouth = false;
    litFromEast = false;
    litFromWest = false;

    litFromNorth = true;
    startingY = 0;
    for (startingX = 0; startingX < width; startingX++)
    {
        numEnergized = run(height, width, tiles, startingX, startingY, litFromNorth, litFromSouth, litFromEast, litFromWest);
        if (numEnergized > maxNumEnergized)
            maxNumEnergized = numEnergized;
    }

    litFromNorth = false;
    litFromSouth = false;
    litFromEast = false;
    litFromWest = false;

    litFromSouth = true;
    startingY = height - 1;
    for (startingX = 0; startingX < width; startingX++)
    {
        numEnergized = run(height, width, tiles, startingX, startingY, litFromNorth, litFromSouth, litFromEast, litFromWest);
        if (numEnergized > maxNumEnergized)
            maxNumEnergized = numEnergized;
    }

    // Part 2
    std::cout << "Part 2: " << maxNumEnergized << std::endl;
    return 0;
}
