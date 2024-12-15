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

struct robot
{
    int px, py, vx, vy;
};

void doIteration(std::vector<robot> &robots, const int width, const int height)
{
    for (int r_it = 0; r_it < robots.size(); r_it++)
    {
        robot r = robots.at(r_it);
        int tempX = r.px + r.vx;
        while (tempX < 0)
            tempX += width;
        while (tempX > width - 1)
            tempX -= width;
        r.px = tempX;

        int tempY = r.py + r.vy;
        while (tempY < 0)
            tempY += height;
        while (tempY > height - 1)
            tempY -= height;
        r.py = tempY;

        robots.at(r_it) = r;
    }
}

int main()
{
    std::cout << "AoC 2024 Day 14" << std::endl;
    std::string fileName = "Day_14/input.txt";
    // std::string fileName = "Day_14/example.txt";

    int height;
    int width;
    if (strSplit(fileName, '/')[1] == "example.txt")
    {
        height = 7;
        width = 11;
    }
    else if (strSplit(fileName, '/')[1] == "input.txt")
    {
        height = 103;
        width = 101;
    }
    else
    {
        std::cout << "Unrecognized file!" << std::endl;
        return 1;
    }

    std::vector<robot> robots;

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ' ');
        std::vector<std::string> split;

        robot r;
        split = strSplit(splitUp.at(0), ',');
        r.py = stoi(split.at(1));
        split = strSplit(split.at(0), '=');
        r.px = stoi(split.at(1));
        split = strSplit(splitUp.at(1), ',');
        r.vy = stoi(split.at(1));
        split = strSplit(split.at(0), '=');
        r.vx = stoi(split.at(1));
        robots.push_back(r);
    }
    file.close();

    // Part 1
    int numSeconds = 100;
    for (int i = 0; i < numSeconds; i++)
        doIteration(robots, width, height);

    int quad1 = 0;
    int quad2 = 0;
    int quad3 = 0;
    int quad4 = 0;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int numRobots = 0;
            for (robot r : robots)
                if (r.px == x && r.py == y)
                    numRobots++;
            if (y < (height / 2) && x < (width / 2))
                quad1 += numRobots;
            if (y < (height / 2) && x > (width / 2))
                quad2 += numRobots;
            if (y > (height / 2) && x < (width / 2))
                quad3 += numRobots;
            if (y > (height / 2) && x > (width / 2))
                quad4 += numRobots;
        }

    int safetyFactor = quad1 * quad2 * quad3 * quad4;
    std::cout << "Part 1: " << safetyFactor << std::endl;

    // Part 2
    bool overlap = true;
    while (overlap)
    {
        overlap = false;
        doIteration(robots, width, height);

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                int numRobots = 0;
                for (robot r : robots)
                    if (r.px == x && r.py == y)
                        numRobots++;

                if (numRobots > 1)
                    overlap = true;
            }

        numSeconds++;
    }

    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         int numRobots = 0;
    //         for (robot r : robots)
    //             if (r.px == x && r.py == y)
    //                 numRobots++;

    //         if (numRobots == 0)
    //             std::cout << '.';
    //         else
    //             std::cout << numRobots;
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    std::cout << "Part 2: " << numSeconds << std::endl;
    return 0;
}