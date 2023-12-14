#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct cycleInfo
{
    int start;
    int period;
};

cycleInfo findCycle(const std::vector<int> &nums)
{
    cycleInfo info;
    int target = nums.back();
    bool foundCycle = false;
    int start = nums.size() - 2;
    int period = 0;
    while (!foundCycle)
    {
        while (nums[start] != target)
            start--;

        period = nums.size() - start;
        foundCycle = true;
        for (int i = 0; i < period; i++)
        {
            if (nums[start - period + i + 1] != nums[start + i])
            {
                foundCycle = false;
                start--;
                break;
            }
        }
    }
    info.start = start;
    info.period = period;
    return info;
}

int main()
{
    std::cout << "AoC 2023 Day 14" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
        lines.push_back(line);
    file.close();
    const int height = lines.size();
    const int width = lines[0].length();

    bool settled = false;
    while (!settled)
    {
        settled = true;
        for (int y = height - 1; y > 0; y--)
            for (int x = 0; x < width; x++)
                if (lines[y][x] == 'O' && lines[y - 1][x] == '.')
                {
                    lines[y - 1][x] = 'O';
                    lines[y][x] = '.';
                    settled = false;
                }
    }

    int load = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            if (lines[y][x] == 'O')
                load += height - y;
    }
    std::cout << "Part 1: " << load << std::endl;

    // Part 2
    std::vector<int> loads;
    for (int cycle = 0; cycle < 200; cycle++) // adjust to run for enough cycles for a pattern to form
    {
        //   roll north
        if (cycle != 0)
        {
            settled = false;
            while (!settled)
            {
                settled = true;
                for (int y = height - 1; y > 0; y--)
                    for (int x = 0; x < width; x++)
                        if (lines[y][x] == 'O' && lines[y - 1][x] == '.')
                        {
                            lines[y - 1][x] = 'O';
                            lines[y][x] = '.';
                            settled = false;
                        }
            }
        }

        // roll west
        settled = false;
        while (!settled)
        {
            settled = true;
            for (int x = 1; x < width; x++)
                for (int y = 0; y < height; y++)
                    if (lines[y][x] == 'O' && lines[y][x - 1] == '.')
                    {
                        lines[y][x - 1] = 'O';
                        lines[y][x] = '.';
                        settled = false;
                    }
        }

        // roll south
        settled = false;
        while (!settled)
        {
            settled = true;
            for (int y = 0; y < height - 1; y++)
                for (int x = 0; x < width; x++)
                    if (lines[y][x] == 'O' && lines[y + 1][x] == '.')
                    {
                        lines[y + 1][x] = 'O';
                        lines[y][x] = '.';
                        settled = false;
                    }
        }

        // roll east
        settled = false;
        while (!settled)
        {
            settled = true;
            for (int x = width - 1; x >= 0; x--)
                for (int y = 0; y < height; y++)
                    if (lines[y][x] == 'O' && lines[y][x + 1] == '.')
                    {
                        lines[y][x + 1] = 'O';
                        lines[y][x] = '.';
                        settled = false;
                    }
        }

        load = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
                if (lines[y][x] == 'O')
                    load += height - y;
        }
        loads.push_back(load);
    }
    cycleInfo info = findCycle(loads);
    int numCycles = (1000000000 - info.start) % info.period;
    std::cout << "Part 2: " << loads[info.start + numCycles] << std::endl;
    return 0;
}
