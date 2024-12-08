#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::cout << "AoC 2024 Day 8" << std::endl;
    std::string fileName = "Day_8/input.txt";
    // std::string fileName = "Day_8/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    struct antenna
    {
        int x;
        int y;
        char freq;

        void print()
        {
            std::cout << "x = " << x << ", y = " << y << ", f = " << freq << std::endl;
        }
    };
    
    std::vector<antenna> antennae;
    int lineNum = 0;
    int width = 0;
    int height = 0;
    while (std::getline(file, line))
    {
        width = line.length();
        antenna ant;
        for (int x = 0; x < width; x++)
            if (line.at(x) != '.')
            {
                ant.x = x;
                ant.y = height;
                ant.freq = line.at(x);
                // ant.print();
                antennae.push_back(ant);
            }
        height++;
    }
    file.close();

    // Part 1
    int numAnts = antennae.size();
    std::vector<antenna> antinodes;
    for (int i = 0; i < numAnts - 1; i++)
        for (int j = i + 1; j < numAnts; j++)
        {
            if (antennae.at(i).freq == antennae.at(j).freq)
            {
                int dx = antennae.at(i).x - antennae.at(j).x;
                int dy = antennae.at(i).y - antennae.at(j).y;
                antenna antinode;
                antinode.x = antennae.at(i).x + dx;
                antinode.y = antennae.at(i).y + dy;
                if (antinode.x >= 0 && antinode.x < width && antinode.y >= 0 && antinode.y < height)
                    antinodes.push_back(antinode);

                antinode.x = antennae.at(i).x - (2 * dx);
                antinode.y = antennae.at(i).y - (2 * dy);
                if (antinode.x >= 0 && antinode.x < width && antinode.y >= 0 && antinode.y < height)
                    antinodes.push_back(antinode);
            }
        }

    // count the antinodes
    int numUniqueAntinodes = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char c = '.';

            for (antenna antinode : antinodes)
                if (antinode.x == x && antinode.y == y)
                    c = '#';

            if (c == '#')
                numUniqueAntinodes++;
        }
    }

    std::cout << "Part 1: " << numUniqueAntinodes << std::endl;

    // Part 2
    antinodes.clear();
    for (int i = 0; i < numAnts - 1; i++)
        for (int j = i + 1; j < numAnts; j++)
        {
            if (antennae.at(i).freq == antennae.at(j).freq)
            {

                int dx = antennae.at(i).x - antennae.at(j).x;
                int dy = antennae.at(i).y - antennae.at(j).y;

                antenna antinode;
                antinode.x = antennae.at(i).x;
                antinode.y = antennae.at(i).y;
                while (antinode.x >= 0 && antinode.x < width && antinode.y >= 0 && antinode.y < height)
                {
                    antinodes.push_back(antinode);
                    antinode.x += dx;
                    antinode.y += dy;
                }

                antinode.x = antennae.at(i).x - dx;
                antinode.y = antennae.at(i).y - dy;
                while (antinode.x >= 0 && antinode.x < width && antinode.y >= 0 && antinode.y < height)
                {
                    antinodes.push_back(antinode);
                    antinode.x -= dx;
                    antinode.y -= dy;
                }
            }
        }

    // count the antinodes and print the map if you uncomment the comments
    numUniqueAntinodes = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char c = '.';

            for (antenna antinode : antinodes)
                if (antinode.x == x && antinode.y == y)
                    c = '#';

            if (c == '#')
                numUniqueAntinodes++;

            for (antenna ant : antennae)
                if (ant.x == x && ant.y == y)
                    c = ant.freq;

            // std::cout << c;
        }
        // std::cout << std::endl;
    }
    std::cout << "Part 2: " << numUniqueAntinodes << std::endl;
    return 0;
}